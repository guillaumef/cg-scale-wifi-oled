// vim: set ft=c:
/*
 * CG Scale
 * Author: Guillaume F.
 * https://github.com/guillaumef/cg-scale-wifi-oled
 *
 * CG Scale w/ Oled w/ Wifi
 *
 * You can tune the SSID, IP, GPIO, ...
 *
 */

#include <Wire.h>

#include <HX711_ADC.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <SSD1306.h>
#include <OLEDDisplayUi.h>

#include <EEPROM.h>


#include "html.h"

/* Uncomment to enable console */
// #define SERIAL_DEBUG

/*
 * Delay loading steps - time to see - set to 0 for fast
 * loading
 */
#define DELAY_STEPS     50

/*
 * Refresh every 1/10th of FPS
 */
#define SCALE_GATHER_FREQ 10

/* LoadCell GPIO */
#define D_LC_FRONT_DOUT	21
#define D_LC_FRONT_SCK	22
#define D_LC_REAR_DOUT	19
#define D_LC_REAR_SCK	  23
#define LC_STABILISING_TIME  4000

/* Wifi SSID */
#define WIFI_SSID       "CG-B"

/* Welcome plane (FPS->seconds) */
#define WELCOME_PLANE   90

/* Do not display negative values */
#define NO_NEGATIVE
/* Max weight tolerate */
#define WEIGHT_MAX      9999.99
/* Min weight on each cell to compute CG */
#define WEIGHT_MIN_CG   30.0

/*
 * Console
 */
#ifdef SERIAL_DEBUG
  void
c_init()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}
  void
c_print( String s )
{
  Serial.println( s );
}
#else
#define c_init()
#define c_print(s)
#endif


/*
 *
 * Conf w/r
 *
 */
#define CONF_MAGIC    ((uint16_t)0xef10)
#define CONF_VERS     ((uint8_t)1)

struct config_s
{
  uint16_t  magic;
  uint8_t   vers;
  uint8_t   lang;
  long		  supports_dist;
  long		  support_le_dist;
  float		  lc_front_calfactor;
  float		  lc_rear_calfactor;
} configuration;

/* EEProm write config at X... if the eeprom is messy */
#define EEPROM_START    0
/* EEProm bytes : EEPROM_START+sizeof(configuration) */
#define EEPROM_SCOPE    (sizeof(configuration) + EEPROM_START)

  int
conf_write( void )
{
  const byte* p = (const byte*)(const void*)&configuration;
  unsigned int i; int addr = 0, modified = 0;
  configuration.magic = CONF_MAGIC;
  configuration.vers  = CONF_VERS;
  for (i = 0; i < sizeof(configuration); i++, addr++, p++) {
    if (*p!=EEPROM.read( EEPROM_START+addr )){
      EEPROM.write( EEPROM_START+addr, *p );
      modified ++;
    }
  }
  EEPROM.commit();
  c_print( "conf_write: wrote "+String(i)+" bytes" );
  return i;
}

  int
conf_reset( void )
{
  memset( &configuration, 0x0, sizeof(configuration) );
  configuration.lc_front_calfactor =
    configuration.lc_rear_calfactor = 1.0;
}

  bool
conf_is_defined( void )
{
  return (configuration.magic == CONF_MAGIC  &&
          configuration.vers == CONF_VERS)
    ? 1 : 0;
}

  bool
conf_is_valid( void )
{
  return (conf_is_defined()                     &&
          configuration.supports_dist>1         &&
          configuration.support_le_dist>1       &&
          configuration.lc_front_calfactor>1.0  &&
          configuration.lc_rear_calfactor>1.0)
    ? 1 : 0;
}

  void
setup_conf( void )
{
  byte* p = (byte*)(void*)&configuration;
  unsigned int i; int addr = 0;

  EEPROM.begin( EEPROM_SCOPE );

  for (i = 0; i < sizeof(configuration); i++, addr++, p++)
    *p = EEPROM.read( EEPROM_START + addr );

  c_print( "conf_readed: " );
  c_print( " version: "+String(configuration.vers) );
  c_print( " supports_dist: "+String(configuration.supports_dist) );
  c_print( " support_le_dist: "+String(configuration.support_le_dist) );
  c_print( " lc_front_calfactor: "+String(configuration.lc_front_calfactor) );
  c_print( " lc_rear_calfactor: "+String(configuration.lc_rear_calfactor) );

  if (! conf_is_defined()) {
    conf_reset();
  }
}

/*
 * Language
 */
#define LANG_NB         2

const char *_msg[] = {
#define MSG_SETUP_WIFI      0
  "Wifi", "Wifi",
#define MSG_SETUP_LC        1
  "LoadCell tare", "Tare cellule charge",
#define MSG_SETUP_CHECK     2
  "Checks", "Verifications",
#define MSG_SETUP_UI        3
  "UserInterface", "Interface utilisateur",
#define MSG_LE_CG_SMALL     4   /* Leading Edge CG */
  "LE CG", "CG BA",
#define MSG_LE_CG           5
  "LeadingEdge CG", "CG Bord Attaque",
#define MSG_WEIGHT          6
  "Weight", "Poids",
#define MSG_WEIGHT_REAR     7
  "W>", "P>",
#define MSG_WEIGHT_FRONT    8
  ">W", ">P",
#define MSG_WIFI            9
  "Wifi", "Wifi",
#define MSG_CONFIG_REQUIRED 10
  "Configuration required", "Configuration necessaire",
#define MSG_CONFIG_STEP1    11
  "1) You need to connect to:"
    "\n SSID: " WIFI_SSID
    "\n http://172.16.19.1/",
  "1) Connectez-vous au:"
    "\n Wifi: " WIFI_SSID
    "\n http://172.16.19.1/",
#define MSG_CONFIG_STEP2    12
  "2) setup the loading cells",
  "2) config les cellules",
#define MSG_CONFIG_STEP3    13
  "3) setup the support size",
  "3) configurer les\ndimensions du support"
};
  const char *
msgc( int i )
{
  return _msg[ i*LANG_NB + configuration.lang ];
}
  String
msg( int i )
{
  return String(msgc(i));
}

/*
 * LoadCell
 */

#define LC_NB		2
HX711_ADC *lc_front = NULL;
HX711_ADC *lc_rear = NULL;
HX711_ADC *a_lc[ LC_NB ] = { NULL, NULL };
/* Lazy lock ... mono thread... happy arduino */
uint8_t lc_available = 0;

struct lc_data_s
{
  float wf, wr, w, cg;
  String swf, swr, sw, scg;
} lc_data;

  void
setup_loadcell_calfactor( void )
{
  if (lc_available) {
    lc_front->setCalFactor( configuration.lc_front_calfactor );
    lc_rear->setCalFactor( configuration.lc_rear_calfactor );
  }
}

  void
setup_loadcell_tare( )
{
  int8_t	i, rdy = 0;

  c_print(msg(MSG_SETUP_LC));

  if (lc_front && lc_available) {
    lc_available = 0;
    for (i=0; i<LC_NB; i++) {
      a_lc[ i ]->powerDown();
      delete(a_lc[i]);
    }

    delay( 1000 );
  }

  a_lc[0] = lc_front = new HX711_ADC( D_LC_FRONT_DOUT, D_LC_FRONT_SCK );
  a_lc[1] = lc_rear  = new HX711_ADC( D_LC_REAR_DOUT, D_LC_REAR_SCK );

  for (i=0; i<LC_NB; i++)
    a_lc[ i ]->begin( 128 );

  /* No startMultiple - incompatible with new objects */
  /* No start - using millis() to countdown the time without referential */
  uint32_t ms = millis() + LC_STABILISING_TIME;
  do {
    for (i=0; i<LC_NB; i++) {
      a_lc[i]->update();
      a_lc[i]->getData();
      yield();
    }
  } while (millis() < ms);

  for (i=0; i<LC_NB; i++)
    a_lc[i]->tare();

  lc_available = 1;

  setup_loadcell_calfactor();

  delay( DELAY_STEPS );
}

  void
loadcell_gather( void )
{
  float wf, wr, w, cg;

  if (! lc_available) {
    lc_data.wf = lc_data.wr = lc_data.w = lc_data.cg = 0.0;
    lc_data.swf = lc_data.swr = lc_data.sw = lc_data.scg = "?";
    return;
  }

  lc_front->update();
  lc_rear->update();

  wf    = lc_front->getData();
  wr    = lc_rear->getData();
#ifdef NO_NEGATIVE
  if (wf<0.0)   wf = 0.0;
  if (wr<0.0)   wr = 0.0;
#endif
#ifdef WEIGHT_MAX
  if (wf>WEIGHT_MAX)  wf = WEIGHT_MAX;
  if (wr>WEIGHT_MAX)  wr = WEIGHT_MAX;
#endif

  w     = wf + wr;

  if (conf_is_valid()
#ifdef WEIGHT_MIN_CG
      && wf > WEIGHT_MIN_CG && wr > WEIGHT_MIN_CG
#endif
      ) {
    double supports_dist, supports_dist_err, compute;
    supports_dist = configuration.supports_dist;
    compute = (supports_dist * wr) / w;
    /* basic check to remove absurd situations:
     * Over the supports_dist ... the plane should fall from the scale */
    if (compute > supports_dist + configuration.support_le_dist)
      cg = -1.0;
    else
      cg = compute + configuration.support_le_dist;
  }
  else
    cg    = 0.0;

  lc_data.wf  = wf;
  lc_data.wr  = wr;
  lc_data.w   = w;
  lc_data.cg  = cg;

  lc_data.swf = float_string( wf, 2, 7 );
  lc_data.swr = float_string( wr, 2, 7 );
  lc_data.sw  = float_string( w,  2, 7 );
  lc_data.scg = float_string( cg, 2, 7 );
}

/*
 * Wifi
 */
WiFiServer server(80);
IPAddress local_IP(172,16,9,1);
IPAddress gateway(172,16,9,1);
IPAddress subnet(255,255,255,0);

  void
setup_wifi( void )
{
  c_print(msg(MSG_SETUP_WIFI));
  /* Wifi */
  WiFi.softAPConfig( local_IP, gateway, subnet );
  WiFi.softAP( WIFI_SSID );
  server.begin();
  delay( DELAY_STEPS );
}


/*
 * UI
 */
SSD1306  display(0x3c, 4, 15);
OLEDDisplayUi ui     ( &display );

/* Loading last checks */
  void
setup_check( void )
{
  c_print( msg(MSG_SETUP_CHECK) );
  if ( conf_is_valid() ) {
    c_print( "valid" );
  }
  delay( DELAY_STEPS );
}

/* UI : Final */
FrameCallback frames[] = {
#ifdef WELCOME_PLANE
  draw_frame_welcome,
#endif
  draw_frame_scale,
  draw_frame_config1,
  draw_frame_config2,
  draw_frame_config3,
};
#ifdef WELCOME_PLANE
FrameCallback   *frames_welcome = frames;
const int       frames_welcome_nb = 1;
FrameCallback   *frames_live = frames_welcome+frames_welcome_nb;
#else
FrameCallback   *frames_live = frames;
#endif
const int       frames_live_nb = 1;
FrameCallback   *frames_conf = frames_live+frames_live_nb;
const int       frames_conf_nb = 3;
OverlayCallback overlays[] = { ms_overlay };

  void
ui_overlay( int overlay )
{
  if (overlay)
    ui.setOverlays( overlays, sizeof(overlays)/sizeof(OverlayCallback) );
  else
    ui.setOverlays( NULL, 0 );
}

  void
ui_to_conf( )
{
  ui_overlay( 0 );
  ui.disableAutoTransition();
  ui.setTargetFPS( 30 );
  ui.setFrameAnimation( SLIDE_LEFT );
  ui.setFrames( frames_conf, frames_conf_nb );
  ui.enableAutoTransition();
}
  void
ui_to_live( void )
{
  ui_overlay( 1 );
  ui.disableAutoTransition();
  ui.setTargetFPS( String(30 / SCALE_GATHER_FREQ).toInt() );
  ui.setFrames( frames_live, frames_live_nb );
  ui.switchToFrame( 0 );
}
#ifdef WELCOME_PLANE
  void
ui_to_welcome( void )
{
  ui.disableAutoTransition();
  ui.setTargetFPS( 30 );
  ui.setFrames( frames_welcome, frames_welcome_nb );
}
#endif

  void
refresh_ui( void )
{
  if (conf_is_valid()) {
    setup_loadcell_calfactor();
    ui_to_live();
  }
  else
    ui_to_conf();
}

  void
setup_ui( void )
{
  c_print( msg(MSG_SETUP_UI) );
  ui.disableAutoTransition();
  delay( DELAY_STEPS );
  ui.init();
#ifdef WELCOME_PLANE
  ui_to_welcome();
#else
  refresh_ui();
#endif
}

/* Loading */
LoadingStage loading[] = {
  { "-",                      setup_conf          },
  { msgc(MSG_SETUP_WIFI),     setup_wifi          },
  { msgc(MSG_SETUP_LC),       setup_loadcell_tare },
  { msgc(MSG_SETUP_CHECK),    setup_check         },
  { msgc(MSG_SETUP_UI),       setup_ui            }
};

  void
setup_ui_loading( void )
{
  c_init();

  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);  // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.flipScreenVertically();

  delay(3000);

  /* OLEDDisplayUi stuff */
  ui.setTimePerFrame(3000);

  ui.disableAllIndicators();

  ui.init();

  ui.runLoadingProcess( loading, sizeof(loading)/sizeof(LoadingStage) );
}

  String
two_digits( int x )
{
  return ((x<10) ? "0":"")+String(x);
}
  String
float_string( float f, int precision, int l )
{
  String s = String( f, precision );
  String b;
  int missing = l - s.length();
  while (missing-- >0) { b.concat(" "); }
  b.concat(s);
  return b;
}

#ifdef WELCOME_PLANE
static uint16_t welcome_cnt = 0;
#include "plane.h"
  void
draw_frame_welcome( OLEDDisplay *display, OLEDDisplayUiState* state,
                    int16_t x, int16_t y)
{
  if (++welcome_cnt == WELCOME_PLANE)
    refresh_ui();
  else
    display->drawXbm(x+5, y, plane_width, plane_height, plane_bits);
  return;
}
#endif

  void
draw_frame_scale( OLEDDisplay *display, OLEDDisplayUiState* state,
                  int16_t x, int16_t y)
{
  loadcell_gather();

  String swf, swr, sw, scg;
  swf   = lc_data.swf;
  swr   = lc_data.swr;
  sw    = lc_data.sw;
  scg   = lc_data.scg;

  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString( 0 + x, 12 + y, msg(MSG_WEIGHT_REAR) + ": "+ swr );
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString( 128, 12 + y, msg(MSG_WEIGHT_FRONT)+ ": "+ swf );

  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString( 5 + x, 24 + y, msg(MSG_LE_CG_SMALL) );
  display->drawString( 5 + x, 41 + y, msg(MSG_WEIGHT) );
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString( 128-5, 24 + y, scg );
  display->drawString( 128-5, 41 + y, sw );

  c_print( msg(MSG_WEIGHT_REAR) +": "+swr+" / "+
           msg(MSG_WEIGHT_FRONT)+": "+swf );
  c_print( " "+msg(MSG_LE_CG)   +": "+scg );
  c_print( " "+msg(MSG_WEIGHT)  +": "+sw  );
}

  void
draw_frame_config( OLEDDisplay *display, OLEDDisplayUiState* state,
                   int16_t x, int16_t y, int16_t msgid )
{
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString( 0 + x, 5 + y, msg( msgid ) );
}
  void
draw_frame_config1( OLEDDisplay *display, OLEDDisplayUiState* state,
                    int16_t x, int16_t y )
{
  draw_frame_config( display, state, x, y, MSG_CONFIG_STEP1 );
}
  void
draw_frame_config2( OLEDDisplay *display, OLEDDisplayUiState* state,
                    int16_t x, int16_t y )
{
  draw_frame_config( display, state, x, y, MSG_CONFIG_STEP2 );
}
  void
draw_frame_config3( OLEDDisplay *display, OLEDDisplayUiState* state,
                    int16_t x, int16_t y )
{
  draw_frame_config( display, state, x, y, MSG_CONFIG_STEP3 );
}



  void
ms_overlay( OLEDDisplay *display, OLEDDisplayUiState* state )
{
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(
    128, 0,
    msg(MSG_WIFI)+": "+local_IP.toString() + " @ " + String( WIFI_SSID ) );
}

  int
uri_get( String r, String p, char *b )
{
  int pos, end, end2;
  pos = r.indexOf( "&"+p+"=" );
  if (pos<0) {
    pos = r.indexOf( "?"+p+"=" );
    if (pos<0)
      return 0;
  }
  pos   += p.length()+2;
  end   = r.indexOf("&", pos);
  end2  = r.indexOf(" ", pos);
  if (end<0 || (end2>0 && end2<end))
    end = end2;
  r = ((end<0) ?
          r.substring(pos)
          :
          r.substring(pos, end));
  c_print( "CGIP: "+p+" => "+r );
  if (b)
    r.toCharArray( b, 128 );
  return r.length();
}

  void
processWifiClient( )
{
  WiFiClient client = server.available();
  if (! client) { return; }
  String req = "";
  String currentLine = "";                // make a String to hold incoming data from the client
  while (client.connected()) {            // loop while the client's connected
    if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      req += c;
      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          bool isjson = 0;
          String json;
          char p[128];

          if (uri_get(req, "getconfig", NULL)) {
            isjson = 1;
            c_print( "GET_CONFIG" );
            json = "{\"lang\":"+String(configuration.lang)+
              ",\"supportsdist\":"+String(configuration.supports_dist)+
              ",\"supportledist\":"+String(configuration.support_le_dist)+
              ",\"lcfrontcal\":"+String(configuration.lc_front_calfactor)+
              ",\"lcrearcal\":"+String(configuration.lc_rear_calfactor)+
              "}";
          }
          else if (uri_get(req, "setconfig", NULL)) {
            int mod = 0;
            c_print( "SET_CONFIG" );
            if (uri_get(req, "lang", p)) {
              configuration.lang = (uint8_t)String(p).toInt(); mod=1; }
            if (uri_get(req, "supportsdist", p)) {
              configuration.supports_dist = String(p).toInt(); mod=1; }
            if (uri_get(req, "supportledist", p)) {
              configuration.support_le_dist = String(p).toInt(); mod=1; }
            if (uri_get(req, "lcfrontcal", p)) {
              configuration.lc_front_calfactor = String(p).toFloat(); mod=2; }
            if (uri_get(req, "lcrearcal", p)) {
              configuration.lc_rear_calfactor = String(p).toFloat(); mod=2; }
            if (uri_get(req, "save", NULL)) {
              mod += conf_write();
            }
            if (uri_get(req, "reset", NULL)) {
              mod += conf_reset();
            }
            isjson = 1;
            json = "{\"err\":false,\"updated\":"+String(mod)+"}";
            if (mod) {
              if (mod == 2) {
                setup_loadcell_calfactor();
              }
              refresh_ui();
            }
          }
          else if (uri_get(req, "getlive", NULL)) {
            isjson = 1;
            if (uri_get(req, "config", NULL)) {
              loadcell_gather();
              json = "{\"err\":false,\"cfg_weight_rear\":\""+lc_data.swr+
                "\",\"cfg_weight_front\":\""+lc_data.swf+"\"}";
            }
            else if (conf_is_valid()) {
              loadcell_gather();
              json = "{\"err\":false,\"weight_rear\":\""+lc_data.swr+
                "\",\"weight_front\":\""+lc_data.swf+
                "\",\"weight\":\""+lc_data.sw+
                "\",\"cg\":\""+lc_data.scg+"\"}";
            }
            else {
              json = "{\"err\":true,\"desc\":\"config\"}";
            }
          }
          else if (uri_get(req, "tare", NULL)) {
            isjson = 1;
            setup_loadcell_tare();
            json = "{\"err\":false}";
          }

          client.println("HTTP/1.1 200 OK");
          client.println("Connection: Keep-Alive");
          client.println("Content-Length: "+
                         String(((isjson)?json.length():strlen(HTML))));
          client.println("Content-type: "+
                         ((isjson)?String("application/json")
                          :String("text/html")));
          client.println();
          if (isjson) {
            client.print( json );
          }
          else {
            client.print( HTML );
          }
          break;

        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  // close the connection:
  client.stop();
}


/*
 * Main setup
 */
  void
setup()
{
  delay(DELAY_STEPS);
  setup_ui_loading();
}

/*
 * Main loop
 */
  void
loop()
{
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    // Wifi new client
    processWifiClient();
  }
}

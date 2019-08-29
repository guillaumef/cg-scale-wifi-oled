// vim: set ft=html:
const char HTML[] PROGMEM = R"=====(
<!doctype html>
<html>
  <head>
    <title>CG balancer</title>

    <style>
/* W3PRO.CSS 4.12 November 2018 by Jan Egil and Borge Refsnes */
html{box-sizing:border-box}*,*:before,*:after{box-sizing:inherit}
/* Extract from normalize.css by Nicolas Gallagher and Jonathan Neal git.io/normalize */
html{-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}
article,aside,details,figcaption,figure,footer,header,main,menu,nav,section,summary{display:block}
audio,canvas,progress,video{display:inline-block}progress{vertical-align:baseline}
audio:not([controls]){display:none;height:0}[hidden],template{display:none}
a{background-color:transparent;-webkit-text-decoration-skip:objects}
a:active,a:hover{outline-width:0}abbr[title]{border-bottom:none;text-decoration:underline;text-decoration:underline dotted}
dfn{font-style:italic}mark{background:#ff0;color:#000}
small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}
sub{bottom:-0.25em}sup{top:-0.5em}figure{margin:1em 40px}img{border-style:none}svg:not(:root){overflow:hidden}
code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}hr{box-sizing:content-box;height:0;overflow:visible}
button,input,select,textarea{font:inherit;margin:0}optgroup{font-weight:bold}
button,input{overflow:visible}button,select{text-transform:none}
button,html [type=button],[type=reset],[type=submit]{-webkit-appearance:button}
button::-moz-focus-inner, [type=button]::-moz-focus-inner, [type=reset]::-moz-focus-inner, [type=submit]::-moz-focus-inner{border-style:none;padding:0}
button:-moz-focusring, [type=button]:-moz-focusring, [type=reset]:-moz-focusring, [type=submit]:-moz-focusring{outline:1px dotted ButtonText}
fieldset{border:1px solid #c0c0c0;margin:0 2px;padding:.35em .625em .75em}
legend{color:inherit;display:table;max-width:100%;padding:0;white-space:normal}textarea{overflow:auto}
[type=checkbox],[type=radio]{padding:0}
[type=number]::-webkit-inner-spin-button,[type=number]::-webkit-outer-spin-button{height:auto}
[type=search]{-webkit-appearance:textfield;outline-offset:-2px}
[type=search]::-webkit-search-cancel-button,[type=search]::-webkit-search-decoration{-webkit-appearance:none}
::-webkit-input-placeholder{color:inherit;opacity:0.54}
::-webkit-file-upload-button{-webkit-appearance:button;font:inherit}
/* End extract */
html,body{font-family:Verdana,sans-serif;font-size:15px;line-height:1.5}html{overflow-x:hidden}
h1{font-size:36px}h2{font-size:30px}h3{font-size:24px}h4{font-size:20px}h5{font-size:18px}h6{font-size:16px}.w3-serif{font-family:serif}
h1,h2,h3,h4,h5,h6{font-family:"Segoe UI",Arial,sans-serif;font-weight:400;margin:10px 0}.w3-wide{letter-spacing:4px}
hr{border:0;border-top:1px solid #eee;margin:20px 0}
.w3-image{max-width:100%;height:auto}img{vertical-align:middle}a{color:inherit}
.w3-table,.w3-table-all{border-collapse:collapse;border-spacing:0;width:100%;display:table}.w3-table-all{border:1px solid #ccc}
.w3-bordered tr,.w3-table-all tr{border-bottom:1px solid #ddd}.w3-striped tbody tr:nth-child(even){background-color:#f1f1f1}
.w3-table-all tr:nth-child(odd){background-color:#fff}.w3-table-all tr:nth-child(even){background-color:#f1f1f1}
.w3-hoverable tbody tr:hover,.w3-ul.w3-hoverable li:hover{background-color:#ccc}.w3-centered tr th,.w3-centered tr td{text-align:center}
.w3-table td,.w3-table th,.w3-table-all td,.w3-table-all th{padding:8px 8px;display:table-cell;text-align:left;vertical-align:top}
.w3-table th:first-child,.w3-table td:first-child,.w3-table-all th:first-child,.w3-table-all td:first-child{padding-left:16px}
.w3-btn,.w3-button{border:none;display:inline-block;padding:8px 16px;vertical-align:middle;overflow:hidden;text-decoration:none;color:inherit;background-color:inherit;text-align:center;cursor:pointer;white-space:nowrap}
.w3-btn:hover{box-shadow:0 8px 16px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19)}
.w3-btn,.w3-button{-webkit-touch-callout:none;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}
.w3-disabled,.w3-btn:disabled,.w3-button:disabled{cursor:not-allowed;opacity:0.3}.w3-disabled *,:disabled *{pointer-events:none}
.w3-btn.w3-disabled:hover,.w3-btn:disabled:hover{box-shadow:none}
.w3-badge,.w3-tag{background-color:#000;color:#fff;display:inline-block;padding-left:8px;padding-right:8px;text-align:center}.w3-badge{border-radius:50%}
.w3-ul{list-style-type:none;padding:0;margin:0}.w3-ul li{padding:8px 16px;border-bottom:1px solid #ddd}.w3-ul li:last-child{border-bottom:none}
.w3-tooltip,.w3-display-container{position:relative}.w3-tooltip .w3-text{display:none}.w3-tooltip:hover .w3-text{display:inline-block}
.w3-ripple:active{opacity:0.5}.w3-ripple{transition:opacity 0s}
.w3-input{padding:8px;display:block;border:none;border-bottom:1px solid #ccc;width:100%}
.w3-select{padding:9px 0;width:100%;border:none;border-bottom:1px solid #ccc}
.w3-dropdown-click,.w3-dropdown-hover{position:relative;display:inline-block;cursor:pointer}
.w3-dropdown-hover:hover .w3-dropdown-content{display:block}
.w3-dropdown-hover:first-child,.w3-dropdown-click:hover{background-color:#ccc;color:#000}
.w3-dropdown-hover:hover > .w3-button:first-child,.w3-dropdown-click:hover > .w3-button:first-child{background-color:#ccc;color:#000}
.w3-dropdown-content{cursor:auto;color:#000;background-color:#fff;display:none;position:absolute;min-width:160px;margin:0;padding:0;z-index:1}
.w3-check,.w3-radio{width:24px;height:24px;position:relative;top:6px}
.w3-sidebar{height:100%;width:200px;background-color:#fff;position:fixed!important;z-index:1;overflow:auto}
.w3-bar-block .w3-dropdown-hover,.w3-bar-block .w3-dropdown-click{width:100%}
.w3-bar-block .w3-dropdown-hover .w3-dropdown-content,.w3-bar-block .w3-dropdown-click .w3-dropdown-content{min-width:100%}
.w3-bar-block .w3-dropdown-hover .w3-button,.w3-bar-block .w3-dropdown-click .w3-button{width:100%;text-align:left;padding:8px 16px}
.w3-main,#main{transition:margin-left .4s}
.w3-modal{z-index:3;display:none;padding-top:100px;position:fixed;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:rgb(0,0,0);background-color:rgba(0,0,0,0.4)}
.w3-modal-content{margin:auto;background-color:#fff;position:relative;padding:0;outline:0;width:600px}
.w3-bar{width:100%;overflow:hidden}.w3-center .w3-bar{display:inline-block;width:auto}
.w3-bar .w3-bar-item{padding:8px 16px;float:left;width:auto;border:none;display:block;outline:0}
.w3-bar .w3-dropdown-hover,.w3-bar .w3-dropdown-click{position:static;float:left}
.w3-bar .w3-button{white-space:normal}
.w3-bar-block .w3-bar-item{width:100%;display:block;padding:8px 16px;text-align:left;border:none;white-space:normal;float:none;outline:0}
.w3-bar-block.w3-center .w3-bar-item{text-align:center}.w3-block{display:block;width:100%}
.w3-responsive{display:block;overflow-x:auto}
.w3-container:after,.w3-container:before,.w3-panel:after,.w3-panel:before,.w3-row:after,.w3-row:before,.w3-row-padding:after,.w3-row-padding:before,
.w3-cell-row:before,.w3-cell-row:after,.w3-clear:after,.w3-clear:before,.w3-bar:before,.w3-bar:after{content:"";display:table;clear:both}
.w3-col,.w3-half,.w3-third,.w3-twothird,.w3-threequarter,.w3-quarter{float:left;width:100%}
.w3-col.s1{width:8.33333%}.w3-col.s2{width:16.66666%}.w3-col.s3{width:24.99999%}.w3-col.s4{width:33.33333%}
.w3-col.s5{width:41.66666%}.w3-col.s6{width:49.99999%}.w3-col.s7{width:58.33333%}.w3-col.s8{width:66.66666%}
.w3-col.s9{width:74.99999%}.w3-col.s10{width:83.33333%}.w3-col.s11{width:91.66666%}.w3-col.s12{width:99.99999%}
@media (min-width:601px){.w3-col.m1{width:8.33333%}.w3-col.m2{width:16.66666%}.w3-col.m3,.w3-quarter{width:24.99999%}.w3-col.m4,.w3-third{width:33.33333%}
.w3-col.m5{width:41.66666%}.w3-col.m6,.w3-half{width:49.99999%}.w3-col.m7{width:58.33333%}.w3-col.m8,.w3-twothird{width:66.66666%}
.w3-col.m9,.w3-threequarter{width:74.99999%}.w3-col.m10{width:83.33333%}.w3-col.m11{width:91.66666%}.w3-col.m12{width:99.99999%}}
@media (min-width:993px){.w3-col.l1{width:8.33333%}.w3-col.l2{width:16.66666%}.w3-col.l3{width:24.99999%}.w3-col.l4{width:33.33333%}
.w3-col.l5{width:41.66666%}.w3-col.l6{width:49.99999%}.w3-col.l7{width:58.33333%}.w3-col.l8{width:66.66666%}
.w3-col.l9{width:74.99999%}.w3-col.l10{width:83.33333%}.w3-col.l11{width:91.66666%}.w3-col.l12{width:99.99999%}}
.w3-rest{overflow:hidden}.w3-stretch{margin-left:-16px;margin-right:-16px}
.w3-content,.w3-auto{margin-left:auto;margin-right:auto}.w3-content{max-width:980px}.w3-auto{max-width:1140px}
.w3-cell-row{display:table;width:100%}.w3-cell{display:table-cell}
.w3-cell-top{vertical-align:top}.w3-cell-middle{vertical-align:middle}.w3-cell-bottom{vertical-align:bottom}
.w3-hide{display:none!important}.w3-show-block,.w3-show{display:block!important}.w3-show-inline-block{display:inline-block!important}
@media (max-width:1205px){.w3-auto{max-width:95%}}
@media (max-width:600px){.w3-modal-content{margin:0 10px;width:auto!important}.w3-modal{padding-top:30px}
.w3-dropdown-hover.w3-mobile .w3-dropdown-content,.w3-dropdown-click.w3-mobile .w3-dropdown-content{position:relative}	
.w3-hide-small{display:none!important}.w3-mobile{display:block;width:100%!important}.w3-bar-item.w3-mobile,.w3-dropdown-hover.w3-mobile,.w3-dropdown-click.w3-mobile{text-align:center}
.w3-dropdown-hover.w3-mobile,.w3-dropdown-hover.w3-mobile .w3-btn,.w3-dropdown-hover.w3-mobile .w3-button,.w3-dropdown-click.w3-mobile,.w3-dropdown-click.w3-mobile .w3-btn,.w3-dropdown-click.w3-mobile .w3-button{width:100%}}
@media (max-width:768px){.w3-modal-content{width:500px}.w3-modal{padding-top:50px}}
@media (min-width:993px){.w3-modal-content{width:900px}.w3-hide-large{display:none!important}.w3-sidebar.w3-collapse{display:block!important}}
@media (max-width:992px) and (min-width:601px){.w3-hide-medium{display:none!important}}
@media (max-width:992px){.w3-sidebar.w3-collapse{display:none}.w3-main{margin-left:0!important;margin-right:0!important}.w3-auto{max-width:100%}}
.w3-top,.w3-bottom{position:fixed;width:100%;z-index:1}.w3-top{top:0}.w3-bottom{bottom:0}
.w3-overlay{position:fixed;display:none;width:100%;height:100%;top:0;left:0;right:0;bottom:0;background-color:rgba(0,0,0,0.5);z-index:2}
.w3-display-topleft{position:absolute;left:0;top:0}.w3-display-topright{position:absolute;right:0;top:0}
.w3-display-bottomleft{position:absolute;left:0;bottom:0}.w3-display-bottomright{position:absolute;right:0;bottom:0}
.w3-display-middle{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%)}
.w3-display-left{position:absolute;top:50%;left:0%;transform:translate(0%,-50%);-ms-transform:translate(-0%,-50%)}
.w3-display-right{position:absolute;top:50%;right:0%;transform:translate(0%,-50%);-ms-transform:translate(0%,-50%)}
.w3-display-topmiddle{position:absolute;left:50%;top:0;transform:translate(-50%,0%);-ms-transform:translate(-50%,0%)}
.w3-display-bottommiddle{position:absolute;left:50%;bottom:0;transform:translate(-50%,0%);-ms-transform:translate(-50%,0%)}
.w3-display-container:hover .w3-display-hover{display:block}.w3-display-container:hover span.w3-display-hover{display:inline-block}.w3-display-hover{display:none}
.w3-display-position{position:absolute}
.w3-circle{border-radius:50%}
.w3-round-small{border-radius:2px}.w3-round,.w3-round-medium{border-radius:4px}.w3-round-large{border-radius:8px}.w3-round-xlarge{border-radius:16px}.w3-round-xxlarge{border-radius:32px}
.w3-row-padding,.w3-row-padding>.w3-half,.w3-row-padding>.w3-third,.w3-row-padding>.w3-twothird,.w3-row-padding>.w3-threequarter,.w3-row-padding>.w3-quarter,.w3-row-padding>.w3-col{padding:0 8px}
.w3-container,.w3-panel{padding:0.01em 16px}.w3-panel{margin-top:16px;margin-bottom:16px}
.w3-code,.w3-codespan{font-family:Consolas,"courier new";font-size:16px}
.w3-code{width:auto;background-color:#fff;padding:8px 12px;border-left:4px solid #4CAF50;word-wrap:break-word}
.w3-codespan{color:crimson;background-color:#f1f1f1;padding-left:4px;padding-right:4px;font-size:110%}
.w3-card,.w3-card-2{box-shadow:0 2px 5px 0 rgba(0,0,0,0.16),0 2px 10px 0 rgba(0,0,0,0.12)}
.w3-card-4,.w3-hover-shadow:hover{box-shadow:0 4px 10px 0 rgba(0,0,0,0.2),0 4px 20px 0 rgba(0,0,0,0.19)}
.w3-spin{animation:w3-spin 2s infinite linear}@keyframes w3-spin{0%{transform:rotate(0deg)}100%{transform:rotate(359deg)}}
.w3-animate-fading{animation:fading 10s infinite}@keyframes fading{0%{opacity:0}50%{opacity:1}100%{opacity:0}}
.w3-animate-opacity{animation:opac 0.8s}@keyframes opac{from{opacity:0} to{opacity:1}}
.w3-animate-top{position:relative;animation:animatetop 0.4s}@keyframes animatetop{from{top:-300px;opacity:0} to{top:0;opacity:1}}
.w3-animate-left{position:relative;animation:animateleft 0.4s}@keyframes animateleft{from{left:-300px;opacity:0} to{left:0;opacity:1}}
.w3-animate-right{position:relative;animation:animateright 0.4s}@keyframes animateright{from{right:-300px;opacity:0} to{right:0;opacity:1}}
.w3-animate-bottom{position:relative;animation:animatebottom 0.4s}@keyframes animatebottom{from{bottom:-300px;opacity:0} to{bottom:0;opacity:1}}
.w3-animate-zoom {animation:animatezoom 0.6s}@keyframes animatezoom{from{transform:scale(0)} to{transform:scale(1)}}
.w3-animate-input{transition:width 0.4s ease-in-out}.w3-animate-input:focus{width:100%!important}
.w3-opacity,.w3-hover-opacity:hover{opacity:0.60}.w3-opacity-off,.w3-hover-opacity-off:hover{opacity:1}
.w3-opacity-max{opacity:0.25}.w3-opacity-min{opacity:0.75}
.w3-greyscale-max,.w3-grayscale-max,.w3-hover-greyscale:hover,.w3-hover-grayscale:hover{filter:grayscale(100%)}
.w3-greyscale,.w3-grayscale{filter:grayscale(75%)}.w3-greyscale-min,.w3-grayscale-min{filter:grayscale(50%)}
.w3-sepia{filter:sepia(75%)}.w3-sepia-max,.w3-hover-sepia:hover{filter:sepia(100%)}.w3-sepia-min{filter:sepia(50%)}
.w3-tiny{font-size:10px!important}.w3-small{font-size:12px!important}.w3-medium{font-size:15px!important}.w3-large{font-size:18px!important}
.w3-xlarge{font-size:24px!important}.w3-xxlarge{font-size:36px!important}.w3-xxxlarge{font-size:48px!important}.w3-jumbo{font-size:64px!important}
.w3-left-align{text-align:left!important}.w3-right-align{text-align:right!important}.w3-justify{text-align:justify!important}.w3-center{text-align:center!important}
.w3-border-0{border:0!important}.w3-border{border:1px solid #ccc!important}
.w3-border-top{border-top:1px solid #ccc!important}.w3-border-bottom{border-bottom:1px solid #ccc!important}
.w3-border-left{border-left:1px solid #ccc!important}.w3-border-right{border-right:1px solid #ccc!important}
.w3-topbar{border-top:6px solid #ccc!important}.w3-bottombar{border-bottom:6px solid #ccc!important}
.w3-leftbar{border-left:6px solid #ccc!important}.w3-rightbar{border-right:6px solid #ccc!important}
.w3-section,.w3-code{margin-top:16px!important;margin-bottom:16px!important}
.w3-margin{margin:16px!important}.w3-margin-top{margin-top:16px!important}.w3-margin-bottom{margin-bottom:16px!important}
.w3-margin-left{margin-left:16px!important}.w3-margin-right{margin-right:16px!important}
.w3-padding-small{padding:4px 8px!important}.w3-padding{padding:8px 16px!important}.w3-padding-large{padding:12px 24px!important}
.w3-padding-16{padding-top:16px!important;padding-bottom:16px!important}.w3-padding-24{padding-top:24px!important;padding-bottom:24px!important}
.w3-padding-32{padding-top:32px!important;padding-bottom:32px!important}.w3-padding-48{padding-top:48px!important;padding-bottom:48px!important}
.w3-padding-64{padding-top:64px!important;padding-bottom:64px!important}
.w3-left{float:left!important}.w3-right{float:right!important}
.w3-button:hover{color:#000!important;background-color:#ccc!important}
.w3-transparent,.w3-hover-none:hover{background-color:transparent!important}
.w3-hover-none:hover{box-shadow:none!important}

.w3-theme-l5 {color:#000 !important; background-color:#f6f6f6 !important}
.w3-theme-l4 {color:#000 !important; background-color:#dfdfdf !important}
.w3-theme-l3 {color:#000 !important; background-color:#c0c0c0 !important}
.w3-theme-l2 {color:#fff !important; background-color:#a0a0a0 !important}
.w3-theme-l1 {color:#fff !important; background-color:#818181 !important}
.w3-theme-d1 {color:#fff !important; background-color:#575757 !important}
.w3-theme-d2 {color:#fff !important; background-color:#4e4e4e !important}
.w3-theme-d3 {color:#fff !important; background-color:#444444 !important}
.w3-theme-d4 {color:#fff !important; background-color:#3a3a3a !important}
.w3-theme-d5 {color:#fff !important; background-color:#303030 !important}
.w3-theme-light {color:#000 !important; background-color:#f6f6f6 !important}
.w3-theme-dark {color:#fff !important; background-color:#303030 !important}
.w3-theme-action {color:#fff !important; background-color:#303030 !important}
.w3-theme {color:#fff !important; background-color:#616161 !important}
.w3-text-theme {color:#616161 !important}
.w3-border-theme {border-color:#616161 !important}
.w3-hover-theme:hover {color:#fff !important; background-color:#616161 !important}
.w3-hover-text-theme:hover {color:#616161 !important}
.w3-hover-border-theme:hover {border-color:#616161 !important}

.blink-blue {color:#98bdf0 !important;animation:fading 1s infinite}@keyframes fading{0%{opacity:0}50%{opacity:1}100%{opacity:0}}
    </style>

    <script>
var hconf = { lang: 0 };
var alang = {
  lang : [ "Language", "Langue" ],
  supportsdist  : [ "Distance between front/rear support",
  "Distance entre le support avant et arriere" ],
  supportsdist_type  : [ "(Natural number, millimeters)", "(Entier naturel, millimetres)" ],
  supportledist : [ "Distance between front support and leading edge",
  "Distance entre le support avant et le bord d'attaque" ],
  supportledist_type  : [ "(Natural number, millimeters)", "(Entier naturel, millimetres)" ],
  lcfrontcal    : [ "Load Cell front divider",
  "Cellule de charge Avant diviseur" ],
  lcfrontcal_type  : [ "(Decimal number >1.0)", "(Nombre decimal > 1.0)" ],
  lcrearcal    : [ "Load Cell rear divider",
  "Cellule de charge Arriere diviseur" ],
  lcrearcal_type  : [ "(Decimal number >1.0)", "(Nombre decimal > 1.0)" ],
  configuration : [ "Configuration", "Configuration" ],
  tare : [ "Tare empty", "Tare a vide" ],
  saveconf	: [ "Save config", "Sauvegarder config" ],
  resetconf : [ "Reset config", "Reinitialiser config" ],
  live          : [ "Live scale", "Mesure en direct" ],
  weight_rear   : [ "Rear weight", "Poids arriere" ],
  weight_front  : [ "Front weight", "Poids avant" ],
  weight        : [ "Weight", "Poids" ],
  cg            : [ "CG from Leading Edge", "CG du Bord d'Attaque" ],
  status_confsaved  : [ "Configuration saved: $1", "Configuration sauvegardee: $1" ],
  status_confreset  : [ "Configuration reset: $1", "Configuration reinitialisee: $1" ],
  status_error_live : [ "Error live: $1", "Erreur live: $1" ],
  status_error      : [ "Network error", "Erreur reseau" ],
  status_tare_countdown: [ "Tare at empty charge in $1 sec(s) - clear the scale!",
    "Tare a charge vide dans $1 sec(s) - enlever les elements de la balance" ],
  status_tare_start: [ "Tare is launched - don't touch the scale",
    "Tare lancee - ne toucher par la balance" ],
  status_tare_done: [ "Tare complete - load cell should return 0", "Tare finie - les cellules de charge doivent retourner 0" ]
};
var screens = [ 'configuration', 'live' ];

function req( x, cb ) {
	var xhr = new XMLHttpRequest();
	xhr.open('GET', '/xhr?'+x);
  xhr.onerror = function() {
    show_status( "error" );
  };
	xhr.onload = function() {
		if (xhr.status != 200) { // analyze HTTP status of the response
			console.log("Error "+xhr.status+": "+xhr.statusText);
		} else { // show the result
			if (cb)
				cb( JSON.parse(xhr.responseText) );
		}
	};
	xhr.send();
}

var conf_to_save_current = 0;
function conf_to_save( tosave ) {
  if (conf_to_save_current == tosave) return;
  var e = gElt('lang_saveconf');
  var btn = gElt('menu_button');
  e.className   = e.className.replace(/ blink-blue/,"");
  btn.className = btn.className.replace(/ blink-blue/,"");
  if (tosave) {
    e.className += ' blink-blue';
    btn.className += ' blink-blue';
  }
  conf_to_save_current = tosave;
}

function conf_save() {
  conf_to_save( 0 );
  close_sidebar();
	req( "setconfig=1&save=1",
			function( hrep ) {
				var ok = ((hrep.updated)?"Ok":"Nok");
				show_status( "confsaved", ok );
			}
		 );
	return false;
}
function conf_reset() {
  conf_to_save( 1 );
  close_sidebar();
  req( "setconfig=1&reset=1",
			function( hrep ) {
				var ok = ((hrep.updated)?"Ok":"Nok");
				show_status( "confreset", ok );
        init_config();
			}
		 );
	return false;
}

function gElt( n ) {
  return document.getElementById( n );
}
function lang_refresh() {
  for (var k in alang) {
    var e = gElt( "lang_"+k );
    if (e) {
			e.innerHTML = alang[k][ hconf.lang ];
		}
  }
}
function iamhere( here ) {
  var e = gElt( "whereami" );
  var esrc = gElt( "lang_"+here );
  e.innerHTML = "CG-B: "+esrc.innerHTML;
  for (var i=0; i<screens.length; i++) {
	  hide_this( screens[i] );
  }
  if (here === "live")
    live_on();
  if (here === "configuration")
    live_on("config");
  show_this( here );
  close_sidebar();
}
function change( tg ) {
  var e;
  var modified = 0;
  if (tg === "lang") {
	  e = gElt("sel_lang");
    if (hconf.lang != e.selectedIndex) {
      modified ++;
      hconf.lang = e.selectedIndex;
      lang_refresh();
    }
  }
  else {
	  e = gElt("in_"+tg);
    if (hconf[ tg ] != e.value) {
      modified ++;
      hconf[ tg ] = e.value;
    }
  }
  if (modified) {
    console.log( "Conf changed for "+tg+" = "+hconf[tg] );
    req( "setconfig=1&"+tg+"="+hconf[ tg ] );
    conf_to_save( 1 );
  }
}


var live_to = 0;
var live_config = 0;
function live_refresh( h ) {
  if (h.err) {
    live_off();
    show_status("error_live", h.desc);
    iamhere("configuration");
    return;
  }
  var k, v, e, elt = ["weight_rear","weight_front","weight","cg",
  "cfg_weight_rear","cfg_weight_front"];
  for (i=0; i<elt.length; i++) {
    k = elt[i];
    e = gElt("live_"+k);
    if (e) {
      if (! (v = h[k])) v = "?";
      e.innerHTML = v;
    }
  }
  if (live_to)
    live_on(live_config);
}
function live_on( config ) {
  live_off();
  live_config = config;
  live_to = setTimeout(
      function(){
        req( "getlive=1"+((config)?"&config=1":""), live_refresh ); }
      , 500);
}
function live_off() {
  if (live_to) {
    clearTimeout( live_to );
    live_to = 0;
  }
}


function tare(i) {
  live_off();
  if (! i) {
    close_sidebar();
    i = 0;
  }
  if (i<5) {
    show_status( "tare_countdown", 5 - i );
    live_to = setTimeout(
        function(){ tare( i+1 ); }, 1000);
    return;
  }

  show_status( "tare_start" );
  req( "tare=1", function(h){
    show_status( "tare_done" );
    iamhere("configuration");
  } );
}

var incdec_to = 0;
var incpower  = 0;
var incdec_k  = 0;
function incdec( k, st ) {
  if (incdec_to)
    clearInterval( incdec_to );
  incdec_to = 0;
  if (k === "stop") {
    if (incdec_k)
      change( incdec_k );
    incdec_k = 0;
    return;
  }
  var e = gElt( "in_"+k );
  incdec_k = k;
  incpower = 0;
  var is_float = (st < 1.0 && st>-1.0)?1:0;
  (function( e, st, is_float ){
    var f = function(){
      if (incpower<20)
        incpower ++;
      var i = e.value;
      if (is_float) { i = 0.00+parseFloat( i ); if (isNaN(i)) i = 0.0; }
      else { i = parseInt( i ); if (isNaN(i)) i = 0; }
      i += ((incpower>10)?2*(incpower-10):1)*st;
      if (is_float) { if (i < 0.0) i = 0.00; i = i.toFixed(2); }
      else { if (i<0) i = 0; }
      e.value = i;
    };
    f();
    incdec_to = setInterval(f, 200);
  }(e,st,is_float));
}

function init_config() {
  req( "getconfig=1", function( h ) {
    hconf = h;
		lang_refresh();
    var e = gElt("sel_lang");
    e.options[ h.lang ].selected = 'selected';
    e = gElt("in_supportsdist");
    e.value = h.supportsdist;
    e = gElt("in_supportledist");
    e.value = h.supportledist;
    e = gElt("in_lcfrontcal");
    e.value = h.lcfrontcal;
    e = gElt("in_lcrearcal");
    e.value = h.lcrearcal;
    iamhere( "live" );
	} );
}

var status_to = 0;
function show_status( key, p1, p2 ) {
  var langk = "status_"+key;
  var econtain = gElt("statusblock");
  var etxt = gElt("status");
  var txt = alang[ langk ][ hconf.lang ];
  if (! p1) p1 = "";
  txt = txt.replace(/[$]1/, p1);
  if (p2) p2 = "";
  txt = txt.replace(/[$]2/, p2);
  etxt.innerHTML = txt;
  show_this( "statusblock" );
  if (status_to) { clearTimeout(status_to); }
  status_to = setTimeout( function() { hide_this("statusblock"); }, 2000 );
}

function show_this(k)	{
  var e = gElt(k);
  if (! e) { console.log( "show_this missing elt "+k ); }
  else { e.style.display="block"; }
}
function hide_this(k)	{
  var e = gElt(k);
  if (! e) { console.log( "hide_this missing elt "+k ); }
  else { e.style.display="none"; }
}
function close_sidebar() {hide_this("sidebar");}
function init() {
  close_sidebar();
  init_config();
}
    </script>

  </head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
  <body onload="init();">
    <nav class="w3-sidebar w3-bar-block w3-card" id="sidebar">
      <div class="w3-container w3-theme-d2">
				<span onclick="close_sidebar()" class="w3-button w3-display-topright w3-large">X</span><br>
        <br/>
			<a class="w3-bar-item w3-button" href="#" id="lang_live" onclick="iamhere('live')"></a>
			<a class="w3-bar-item w3-button" href="#" id="lang_configuration" onclick="iamhere('configuration')"></a>
			<hr/>
			<a class="w3-bar-item w3-button" href="#" id="lang_tare" onclick="tare()"></a>
			<hr/>
			<a class="w3-bar-item w3-button" href="#" id="lang_saveconf" onclick="conf_save();"></a>
			<hr/>
			<a class="w3-bar-item w3-button" href="#" id="lang_resetconf" onclick="conf_reset();"></a>
      </div>
		</nav>
		<header class="w3-bar w3-card w3-theme">
			<button class="w3-bar-item w3-button w3-xxxlarge w3-hover-theme"
           id="menu_button" onclick="show_this('sidebar')">&#9776;</button>
      <span class="w3-bar-item">
<svg xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://creativecommons.org/ns#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" width="27.622141mm" height="17.267614mm" viewBox="0 0 27.622141 17.267614" version="1.1" id="svg8" inkscape:version="0.92.1 r15371" sodipodi:docname="plane.svg"> <defs id="defs2" /> <sodipodi:namedview id="base" pagecolor="#ffffff" bordercolor="#666666" borderopacity="1.0" inkscape:pageopacity="0.0" inkscape:pageshadow="2" inkscape:zoom="5.6" inkscape:cx="89.341779" inkscape:cy="48.892676" inkscape:document-units="mm" inkscape:current-layer="layer1" showgrid="false" inkscape:window-width="1920" inkscape:window-height="1059" inkscape:window-x="0" inkscape:window-y="0" inkscape:window-maximized="1" /> <metadata id="metadata5"> <rdf:RDF> <cc:Work rdf:about=""> <dc:format>image/svg+xml</dc:format> <dc:type rdf:resource="http://purl.org/dc/dcmitype/StillImage" /> <dc:title /> </cc:Work> </rdf:RDF> </metadata> <g inkscape:label="Layer 1" inkscape:groupmode="layer" id="layer1" transform="translate(-64.828799,-123.03309)"> <path style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:0.66335529;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1" d="m 71.496329,128.02562 0.494863,-0.65742 c 0,0 0.24623,-0.43322 0.165526,-0.63528 -0.08295,-0.20769 -0.358628,-0.24362 -0.557471,-0.31686 -0.349833,-0.12884 -0.762735,-0.12269 -1.092644,-0.20617 m 0.291097,3.19318 c -1.377544,1.07168 -2.919188,1.9579 -4.599314,2.31662 -0.569731,-0.19356 -1.673127,-0.51157 -0.56928,-1.01216 1.057567,-0.70088 2.01356,-2.15486 3.385633,-1.57839 0.594321,0.0913 1.188641,0.18262 1.782961,0.27393 z m 10.479592,0.78356 c 2.345099,-1.81775 3.117133,-3.19958 5.324567,-5.20847 1.59117,-0.75751 1.2185,2.6918 0.383529,3.50439 l -1.557617,2.35281 m -15.193793,-0.90004 c 1.66037,0.31326 2.841236,0.58472 4.018423,0.87572 0.588593,0.1455 2.146092,0.30954 3.181016,0.63592 0.281589,0.0888 0.682171,0.0758 0.815336,0.35705 0.18712,0.39517 -0.01542,1.03455 -0.296516,1.29157 l -1.097687,1.00369 c -1.731217,1.88243 -3.606759,3.60038 -5.43859,5.36641 1.248928,1.31816 2.890001,-0.32359 4.217044,-0.72948 1.474244,-0.67004 2.438013,-1.43434 3.459618,-2.08591 1.021606,-0.65159 1.854044,-1.27901 3.065627,-2.3837 1.140202,-1.10146 3.00859,-0.99721 4.446649,-0.77534 1.869914,0.39861 4.793382,0.89295 4.895208,0.80233 0.101826,-0.0906 0.509108,-0.45308 0.610934,-0.5437 0.101825,-0.0906 -0.738657,-0.92508 -1.215597,-1.23565 -0.746993,-0.48643 -1.638228,-0.65605 -2.476972,-0.91745 -0.983969,-0.30666 -1.86712,-0.58989 -2.9907,-0.76142 -4.720999,-0.9821 -7.645206,-0.99946 -12.367138,-1.96002 -1.742323,-0.1238 -2.584257,-2.0987 -2.819492,-3.72688 -0.07442,-1.49183 -1.925288,-2.18213 -2.780574,-1.53693 -0.05924,1.93768 -0.146469,3.87751 -0.218018,5.81617" id="path3692" inkscape:connector-curvature="0" sodipodi:nodetypes="ccaacccccccccccsaascccscczzaaccccc" /> </g> </svg>
      </span>
			<h2 class="w3-bar-item" id="whereami"></h2></header>

    <div id="statusblock" class="w3-modal w3-animate-opacity">
      <div class="w3-modal-content w3-card-4">
        <header class="w3-container w3-theme-d2">
          <h5 id="status"></h5>
        </header>
      </div>
    </div>

    <div class="w3-container w3-content">
      <div id="configuration" class="w3-panel w3-white w3-card w3-display-container">
      <table class="w3-table">
        <tr><td id="lang_lang"></td>
          <td><select id="sel_lang" class="w3-select" onchange="change('lang');">
              <option value="0">English</option>
              <option value="1">Francais</option>
            </select>
          </td></tr>
          <tr><td><span id="lang_supportsdist"></span><br/><span
                        id="lang_supportsdist_type"/></span></td>
          <td>
            <input class="w3-input" type="text" id="in_supportsdist" onchange="change('supportsdist');"></input>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('supportsdist',-1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('supportsdist',-1)" ontouchend="incdec('stop')">-</button>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('supportsdist',1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('supportsdist',1)" ontouchend="incdec('stop')">+</button>
          </td></tr>
          <tr><td><span id="lang_supportledist"></span><br/><span
                        id="lang_supportledist_type"></span></td>
          <td><input class="w3-input" type="text" id="in_supportledist"
                                                  onchange="change('supportledist');"></input>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('supportledist',-1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('supportledist',-1)" ontouchend="incdec('stop')">-</button>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('supportledist',1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('supportledist',1)" ontouchend="incdec('stop')">+</button>
          </td>
          </tr>
          <tr><td><span id="lang_lcfrontcal"></span><br/><span
                        id="lang_lcfrontcal_type"></span></td>
          <td><input class="w3-input" type="text" id="in_lcfrontcal" onchange="change('lcfrontcal');"></input>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('lcfrontcal',-0.1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('lcfrontcal',-0.1)" ontouchend="incdec('stop')">-</button>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('lcfrontcal',0.2)" onmouseup="incdec('stop')"
              ontouchstart="incdec('lcfrontcal',0.2)" ontouchend="incdec('stop')">+</button>
          </td></tr>
          <tr><td></td><td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align" id="live_cfg_weight_front"></span></td></tr>
          <tr><td><span id="lang_lcrearcal"></span><br/><span
                        id="lang_lcrearcal_type"></span></td>
          <td><input class="w3-input" type="text" id="in_lcrearcal" onchange="change('lcrearcal');"></input>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('lcrearcal',-0.1)" onmouseup="incdec('stop')"
              ontouchstart="incdec('lcrearcal',-0.1)" ontouchend="incdec('stop')">-</button>
            <button class="w3-button w3-circle w3-black"
              onmousedown="incdec('lcrearcal',0.2)" onmouseup="incdec('stop')"
              ontouchstart="incdec('lcrearcal',0.2)" ontouchend="incdec('stop')">+</button>
          </td></tr>
          <tr><td></td><td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align"
                                 id="live_cfg_weight_rear"></span></td></tr>
      </table>
      </div>
      <div id="calibration" class="w3-panel w3-white w3-card w3-display-container">
      </div>
      <div id="live" class="w3-panel w3-white w3-card w3-display-container">
        <table class="w3-table">
          <tr><td id="lang_weight_rear"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align"
                      id="live_weight_rear"></span></td></tr>
          <tr><td id="lang_weight_front"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align" id="live_weight_front"></span></td></tr>
          <tr><td id="lang_cg"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align" id="live_cg"></span></td></tr>
          <tr><td id="lang_weight"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xxlarge w3-theme-dark w3-right-align" id="live_weight"></span></td></tr>
        </table>
      </div>
    </div>
  </body>
</html>
)=====";

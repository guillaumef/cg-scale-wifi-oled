/*
 * CG Scale
 * Author: Guillaume F. ( g@w0.yt )
 * https://github.com/guillaumef/cg-scale-wifi-oled
 *
 * Work on:
 *    1 - base
 *    2 - support			( x2 )
 *    3 - rod support			( x2 )
 *    4 - leadingEdge rod		( x2 )
 *    5 - case top
 *    6 - case bottom
 *    7 - base scale module cover	( x2 )
 *
 *    9 - display all
 */
WORK_ON = 9;

/* Scale sensor */
ss_wh		= 12.7;	/* x/z */
ss_l		= 80;	/* y */
ss_hole_int_dia	= 5.4;	/* diameter + 0.4 to fit */
ss_hole_ext_dia	= 4.4;	/* diameter + 0.4 to fit */
ss_hole_1 	= 5;
ss_hole_2 	= 20;

/* Scale sensor module */
ssm_w	= 20;
ssm_l	= 32;
ssm_h	= 8;

/* Board */
board_w = 50;
board_l	= 26;
board_h	= 5;
board_oled_w = 30;
board_oled_l = 18;
board_oled_w_pos = 4;
board_clearance = 1;
board_case_thickness = 1; /* with 1 more of the minkowski sphere */
board_case_screw_dia = 2.2;

/* base */
base_w	= 150;	/* width: x */
base_l	= 150;	/* len: depth: y, should be > 2 x ss_l/2 */
base_root_h		= 15;
base_ss_clearance_h	= 4; /* include more with minkowski sphere */
base_ss_clearance_l_space = 3;
base_ss_clearance_l	= (ss_hole_2+ss_hole_1)*2 + base_ss_clearance_l_space;

/* plane support : you can tune */
ps_l_ext	= 39;
ps_l_pos	= 5;
ps_l		= ss_l/2 + ps_l_ext;
ps_lip_h	= 5;

ps_st_l		= 155;
ps_st_h		= 13;
ps_st_hole_depth= 10;
ps_st_hole_dia	= 3.2;	/* 0.2 added to ease the fit - fast drilling in 3mm is mandatory anyway */

$fn=100;


/*
 *
 * SCALE BASE
 *
 */

module base_root() {
	union() {
		difference() {
			minkowski()
			{
				linear_extrude( height = base_root_h )
					polygon( points = [[0, 0],[base_w, 0],[base_w/2,base_l]], convexity = 1 );
				sphere(2);
			}
			/* cut straight the bottom */
			translate([0,0,-base_root_h/2])
					cube([base_w*3,base_l*3,base_root_h], center=true);
		}
		/* ss clearance */
		minkowski()
		{
			translate([base_w/2,base_l/2,base_root_h+base_ss_clearance_h/2])
				cube([ ss_wh+ss_wh/2, base_ss_clearance_l, base_ss_clearance_h ], center=true);
			sphere(1);
		}
	}
}

module base_ss_hole() {
	union() {
		translate([0,0,base_root_h]) {
			cylinder(r=ss_hole_int_dia/2, h=base_root_h*2, center=true);
		}
		cylinder(r=ss_hole_int_dia+2, h=5, center=true);
	}
}
module base_holes() {
	tx = base_w/2;
	ty = base_l/2;
	tz = base_root_h+base_ss_clearance_h/2;
	spacer = base_ss_clearance_l_space/2;
	translate([tx, ty - spacer - ss_hole_1, 0]) base_ss_hole();
	translate([tx, ty - spacer - ss_hole_2, 0]) base_ss_hole();
	translate([tx, ty + spacer + ss_hole_1, 0]) base_ss_hole();
	translate([tx, ty + spacer + ss_hole_2, 0]) base_ss_hole();
}

module base_ssm_hole_mask_hole() {
	translate([0, ssm_l/2 + 5, 0])
		cylinder(r=1,h=1000,center=true,$fn=10);
	translate([0, -(ssm_l/2 + 5), 0])
		cylinder(r=1,h=1000,center=true,$fn=10);
}

module base_ssm_hole_mask_one() {
	minkowski() {
		cube( [ssm_w, ssm_l, ssm_h*2], center=true );
		sphere(1);
	}
}

module ssm_hole_cover() {
	union() {
		difference() {
			translate([0,0,ssm_h+1])
				minkowski() {
					cube( [ ssm_w, ssm_l+20, ssm_h*2], center=true );
					sphere(1);
				}
			translate([0,0,500+2])
				cube([1000,1000,1000],center=true);
			base_ssm_hole_mask_hole();
		}
		difference() {
			translate([0,0,0])
				difference() {
					scale([.99,.99,1])
						translate([0,0,ssm_h+1])
						base_ssm_hole_mask_one();
					scale([.90,.94,1])
						translate([0,0,ssm_h+1])
						base_ssm_hole_mask_one();
				}
			translate([0,0,500+4])
				cube([1000,1000,1000],center=true);
		}
	}
}

module base_ssm_hole_mask() {
	translate([base_w/2 - ssm_w - 2, base_l/2 - ssm_l, base_root_h]) {
		base_ssm_hole_mask_one();
		base_ssm_hole_mask_hole();
	}
	translate([base_w/2 + ssm_w + 2, base_l/2 - ssm_l, base_root_h]) {
		base_ssm_hole_mask_one();
		base_ssm_hole_mask_hole();
	}
}
module base_cablesshole() {
	/* to tune... no complex geometry here - define our vertical hole position */
	ref=37;
	/* ssm hole to under the ss support */
		translate([0,ref/2,2])
		rotate([-90,0,0])
		union() {
			cylinder(r=2.5, h=ref, center=true);
			translate([0,-ref/2+2.5,ref/2])
				rotate([90,0,0])
				cylinder(r=2.5, h=ref, center=true);
		}
}
module base_cablessholes() {
	translate([base_w/2 - ssm_w - 2, base_l/2 - ssm_l, base_root_h-4])
		rotate([0,0,-30])
		base_cablesshole();
	translate([base_w/2 + ssm_w + 2, base_l/2 - ssm_l, base_root_h-4])
		rotate([0,0,30])
		base_cablesshole();
}
module base_cablessmhole() {
	/* to tune... no complex geometry here - define our vertical hole position */
	ref=80;
	/* ssm hole to under the ss support */
		translate([0,0,2.5])
		rotate([-90,0,0])
		union() {
			cylinder(r=2.5, h=ref, center=true);
		}
}
module base_cablessmholes() {
	translate([base_w/2, -2, base_root_h-4])
		rotate([0,0,30])
		base_cablessmhole();
	translate([base_w/2, -2, base_root_h-4])
		rotate([0,0,-30])
		base_cablessmhole();
}
module base() {
	difference() {
		base_root();
		base_holes();
		base_ssm_hole_mask();
		base_cablessholes();
		base_cablessmholes();
	}
}

/*
 *
 * Scale hands
 *
 */
module ps_ss_hole() {
	union() {
		translate([0,0,base_root_h]) {
			cylinder(r=ss_hole_ext_dia/2, h=base_root_h*2, center=true);
		}
		translate([0,0,ss_hole_ext_dia/2])
			cylinder(h=ss_hole_ext_dia+0.1, r1=ss_hole_ext_dia+0.1, r2=0, center=true);
	}
}

module _support_block( w, l, h ) {
	minkowski() {
		translate([-w/2,0,-h/2])
			rotate([90,0,0])
			linear_extrude(height=l,center=true)
			polygon(points = [[0,0],[w/4,h],[w*3/4,h],[w,0]]);
		sphere(1);
	}
}

module _support_block_all() {
	translate([0, -ps_l_pos, ps_lip_h/3]) {
		_support_block( ss_wh+10, ps_l, ps_lip_h );
	}
	translate([ 0, 0, (ss_wh/2 + ps_lip_h)/2 ]) {
		cube([ ss_wh, ss_hole_2+ss_hole_1, ss_wh/2], center=true);
	}
}

module plane_support() {
	difference() {
		translate( [0, (ss_hole_2+ss_hole_1)/2, 0 ] ) {
			_support_block_all();
		}
		translate([0,ss_hole_1,-ps_lip_h/2+0.7])
			ps_ss_hole();
		translate([0,ss_hole_2,-ps_lip_h/2+0.7])
			ps_ss_hole();
	}
}

module rod_support() {
	hole_dia = ps_st_hole_dia;
	difference() {
		rotate([0,0,90]) {
			_support_block( ss_wh, ps_st_l, ps_st_h );
			_support_block( ss_wh*1.8, ss_wh+20, ps_st_h );
		}
		translate([0,0,-2])
		rotate([0,180,0])
			scale([1.03,1.03,1.03])
			_support_block_all();
		cylinder(r=2.1/2,h=100,center=true,$fn=20);
		cylinder(r=4.5/2,h=4,center=true,$fn=6);
		for(x = [ ss_wh+10 : 10 : ps_st_l/2 ]) {
			translate([x,0,ps_st_h - ps_st_hole_depth])
				cylinder(r=hole_dia/2, h=ps_st_h, center=true);
			translate([-x,0,ps_st_h - ps_st_hole_depth])
				cylinder(r=hole_dia/2, h=ps_st_h, center=true);
		}
	}
}

module le_rod_support() {
	hole_dia = ps_st_hole_dia;
	difference() {
		minkowski() {
			cube([ 80, ss_wh*2/3, ps_st_h ], center=true);
			sphere(1);
		}
		/* full hole : thight */
		translate([-35,0,0])
			cylinder(r=hole_dia/2, h=1000, center=true);
		/* rod LE */
		for(x = [ -25 : 10 : 80 ]) {
			translate([x,0, ps_st_h - ps_st_hole_depth])
				cylinder(r=hole_dia/2, h=ps_st_h, center=true);
		}
	}
}

module _case_hole() {
	h = board_h + board_clearance*4 + board_case_thickness*2 + 2; /* +2 for the minkowski sphere */
	translate([0,0,board_case_thickness - 1])
		translate([0,0,h/2 + board_case_thickness*2])
		cylinder(r=board_case_screw_dia/2 + 0.2, h=h + 1, center=true);
}
module _case_screw() {
	h = board_h + board_clearance*4 + board_case_thickness*2 + 2; /* +2 for the minkowski sphere */
	translate([0,0,board_case_thickness - 1])
		difference() {
			cylinder(r=board_case_screw_dia,
					h=h - board_case_thickness, center=true);
			cylinder(r=board_case_screw_dia/2,
					h=h + 1, center=true);
		}
}
module _case() {
	difference() {
		union() {
			difference() {
				minkowski() {
					cube([ board_w + board_clearance*2 + board_case_screw_dia*6 + board_case_thickness*2,
							board_l + board_clearance*2 + board_case_thickness*2,
							board_h + board_clearance*4 + board_case_thickness*2],
							center=true);
					sphere(1);
				}
				cube([ board_w + board_clearance*2 + board_case_screw_dia*6,
						board_l + board_clearance*2,
						board_h + board_clearance*4 ],
						center=true);
				translate([ (board_w - board_oled_w)/2 - board_oled_w_pos, 0, board_h + board_clearance*4 - board_case_thickness*2 ])
					cube([ board_oled_w, board_oled_l, board_case_thickness*6 ], center=true);
			}
			translate([ -board_w/2 - board_case_screw_dia*3, board_l/2, 0 ]) { _case_screw(); }
			translate([ board_w/2 + board_case_screw_dia*3, board_l/2, 0 ]) { _case_screw(); }
			translate([ board_w/2 + board_case_screw_dia*3, -board_l/2, 0 ]) { _case_screw(); }
			translate([ -board_w/2 - board_case_screw_dia*3, -board_l/2, 0 ]) { _case_screw(); }
		}
		translate([ -board_w/2 - board_case_screw_dia*3, board_l/2, 0 ]) { _case_hole(); }
		translate([ board_w/2 + board_case_screw_dia*3, board_l/2, 0 ]) { _case_hole(); }
		translate([ board_w/2 + board_case_screw_dia*3, -board_l/2, 0 ]) { _case_hole(); }
		translate([ -board_w/2 - board_case_screw_dia*3, -board_l/2, 0 ]) { _case_hole(); }
	}
}

module case_bottom() {
	difference() {
		_case();
		translate([0,0,100 + (board_h + board_clearance*4)/2 - 0.02])
			cube([board_w*2,board_w*2,200], center=true);
		/* air */
		air_hole = 3;
		for(x = [ -board_w/2 + air_hole  : (board_w - air_hole*2 - 0.01)/7 : board_w/2 - air_hole ])
			for(y = [ -board_l/2 + air_hole: (board_l - air_hole*2 - 0.01)/4: board_l/2 - air_hole ])
				translate([x,y,0])
					cube([air_hole,air_hole,board_h*20], center=true); 
		/* cabling */
		cable_dia = 5;
		translate([0,board_l/4,board_h/2])
		rotate([0,90,0]) {
			union() {
				cylinder(r=cable_dia/2, h=board_w*2, center=true);
				translate([-cable_dia/2,0,0])
					cube([cable_dia,cable_dia,board_w*2],center=true);
			}
		}
	}
}
module case_top() {
	difference() {
		_case();
		translate([0,0, -100 + (board_h + board_clearance*4)/2])
			cube([board_w*2,board_w*2,200], center=true);
	}
}



/*
 * BASE
 */
if (WORK_ON == 1) {
	base();
}

/*
 * SUPPORT
 */
if (WORK_ON == 2) {
	plane_support();
}

if (WORK_ON == 3) {
	rotate([180,0,0]) /* for printing */
		rod_support();
}

/*
 * LE Support
 */
if (WORK_ON == 4) {
	le_rod_support();
}

/*
 * BOARD CASE (not mandatory)
 */
if (WORK_ON == 5) {
	/* TOP */
	case_top();
}
if (WORK_ON == 6) {
	/* BOTTOM */
	case_bottom();
}

/*
 * Base scale module cover
 */
if (WORK_ON == 7) {
	ssm_hole_cover();
}

/*
 * Display All
 */
if (WORK_ON == 9) {
	color("SteelBlue") {
		base();
	}
	color("Yellow") {
		translate([base_w/2 - ssm_w - 2, base_l/2 - ssm_l, base_root_h+4]) {
			rotate([180,0,0])
				ssm_hole_cover();
		}
		translate([base_w/2 + ssm_w + 2, base_l/2 - ssm_l, base_root_h+4]) {
			rotate([180,0,0])
				ssm_hole_cover();
		}
	}
	color("Silver") {
		translate([ base_w/2, 10, base_root_h + base_ss_clearance_h + ss_wh ])
			rotate([0,180,0])
			plane_support();
		translate([ base_w/2, 10 + ss_l*3/2, base_root_h + base_ss_clearance_h + ss_wh ])
			rotate([0,180,180])
			plane_support();
	}
	color("Red") {
		translate([ base_w/2, 10, base_root_h + base_ss_clearance_h + ss_wh ])
			rod_support();
		translate([ base_w/2, 10 + ss_l*3/2, base_root_h + base_ss_clearance_h + ss_wh ])
			rod_support();
		translate([ base_w/2 - 30, 10 + ss_l*3/2 + 35, base_root_h + base_ss_clearance_h + ss_wh + 50 ])
			rotate([0,0,90]) le_rod_support();
		translate([ base_w/2 + 30, 10 + ss_l*3/2 + 35, base_root_h + base_ss_clearance_h + ss_wh + 50 ])
			rotate([0,0,90]) le_rod_support();

	}
	color("Green") {
		translate([ base_w/2, -base_l/2, 0 ]) {
			case_bottom();
			case_top();
		}
	}
}

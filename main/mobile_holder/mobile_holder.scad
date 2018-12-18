module LegPartv3(){
difference(){
hull(){
translate([0,5,5])
rotate([0,90,0])
cylinder(3,5,5, $fn = 20);
translate([0,10,0])
cube([3,19,10]);
}

translate([-1,5,5])
 rotate([0,90,0])
cylinder(7,2.5,2.5, $fn = 20);

translate([-1,12,5])
 rotate([0,90,0])
cylinder(7,.5,.5, $fn = 20);

translate([-1,18.5,5])
 rotate([0,90,0])
cylinder(7,.5,.5, $fn = 20);
}

difference(){
translate([-36,26,0])
cube([37,3,10]);
    
translate([-17,33,5])
 rotate([90,0,0])
cylinder(10,2.5,2.5, $fn = 20);
translate([-8,33,5])
 rotate([90,0,0])
cylinder(10,.5,.5, $fn = 20);
translate([-26,33,5])
 rotate([90,0,0])
cylinder(10,.5,.5, $fn = 20);
}

translate([-37,0,0])
hull(){
translate([0,5,5])
rotate([0,90,0])
cylinder(3,5,5, $fn = 20);
translate([0,10,0])
cube([3,19,10]);
}
translate([-37,5,5])
rotate([0,90,0])
cylinder(7,2.5,2.5, $fn = 20);
}

module phoneHolder(){
    
translate([0,-20,55])
cube([70,3,110], center = true);

translate([35,-33,0])
cube([3,14.5,41]);

mirror(){
translate([35,-33,0])
cube([3,14.5,41]);
}

translate([-35,-33,0])
cube([70,3,20]);

translate([0,-26,1.5])
cube([70,14,3],center=true);

translate([0,-17,45])
cube([50,3,27.5], center=true);

rotate([15,0,0])
translate([0,-2,33])
cube([50,14.5,3], center=true);


translate([22,-20,60])
rotate([0,90,0])
linear_extrude(4)
 polygon(points=[[0,0],[3,12],[28,17],[33,0]]);

mirror(){
translate([22,-20,60])
rotate([0,90,0])
linear_extrude(4)
 polygon(points=[[0,0],[3,12],[28,17],[33,0]]);
}
}

module servoBrace(){
z = 24;
width = 2.5;

difference(){
translate([-33,0,z/2])
cube([10,width,z], center=true);

 translate([-33,0,z/2])
rotate([90,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);
}

translate([-28.5,9.25,z/2])
cube([width,21,z], center=true);

translate([-14,9.25,z/2])
cube([width,21,z], center=true);

translate([-21,18.5,z/2])
cube([14,width,z], center=true);


mirror(){
    difference(){
translate([-33,0,z/2])
cube([10,width,z], center=true);

 translate([-33,0,z/2])
rotate([90,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);
}

translate([-28.5,9.25,z/2])
cube([width,21,z], center=true);

translate([-14,9.25,z/2])
cube([width,21,z], center=true);

translate([-21,18.5,z/2])
cube([14,width,z], center=true);
}
difference(){
translate([-15.25,-width/2,0])
 cube([30.5,width,z]);
 translate([0,0,z/2])    
rotate([90,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);
}
}

module battRack () {
union(){
translate([12,0.5,-12])
cube([3,40,20]);
translate([15,0.5,-12])
cube([14,11.5,4]);
}

mirror(){
union(){
translate([12,0.5,-12])
cube([3,40,20]);
translate([15,0.5,-12])
cube([14,11.5,4]);
}
}


translate([0,40,-2.5])
rotate(90)
cube([3,30,18],center=true);
}

module foot(){
scale([20,23,5])
hull(){
translate([-1,1,0])
cylinder (h = 1, d = 1,$fn = 20, center = true);
translate([-1,-1,0])
cylinder (h = 1, d = 1, $fn = 20,center = true);
translate([1,1,0])
cylinder (h = 1, d = 1, $fn = 20,center = true);
translate([1,-1,0])
cylinder (h = 1, d = 1, $fn = 20,center = true);
}
translate([-25.5,-2.5,0])
cube([5,5,16]);

translate([3,-2.5,0])
cube([5,10,16]);    
}

module hip (){
    difference(){
difference(){

union(){
translate([0,0,2.5])
scale([29,14,10])
hull(){
translate([-1,1,0])
sphere (h = 1, d = 1,$fn = 20, center = true);
translate([-1,-1,0])
sphere (h = 1, d = 1, $fn = 20,center = true);
translate([1,1,0])
sphere (h = 1, d = 1, $fn = 20,center = true);
translate([1,-1,0])
sphere (h = 1, d = 1, $fn = 20,center = true);
}


translate([0,0,10])
cube([90,50,10],center=true);
}

cylinder(100, 1.5, 1.5, center = true, $fn =20);

union(){

union(){

translate([-33,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);

translate([-21,-14,0])
cylinder(100, .5, .5, center = true, $fn =20);

translate([-21,14,0])
cylinder(100, .5, .5, center = true, $fn =20);

translate([-21,0,0])
cube([13,23,100], center = true);

}

mirror()
union(){

translate([-33,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);

translate([-21,-14,0])
cylinder(100, .5, .5, center = true, $fn =20);

translate([-21,14,0])
cylinder(100, .5, .5, center = true, $fn =20);

translate([-21,0,0])
cube([13,23,100], center = true);
}
}
}
}


module mobile_holder(){
translate([30,-2.5,0])
union(){
foot();
translate([-15,20,5])
rotate([90,0,90])
LegPartv3();
}
mirror(){
translate([30,-2.5,0])
union(){
foot();
translate([-15,20,5])
rotate([90,0,90])
LegPartv3();
}
}



translate([0,0,37])
union(){
hip();

translate([0,10,7])
rotate([90,0,0])
servoBrace();
phoneHolder();
}

}

mobile_holder();















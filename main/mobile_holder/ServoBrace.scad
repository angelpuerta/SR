#import("C:/Users/einye/Desktop/isthisuni/robots/SR/main/example_mobile_holder/ServoBrace.stl");

z = 24;
width = 2.5;

difference(){
translate([-33,0,z/2])
cube([10,width,z], center=true);

#translate([-33,0,z/2])
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

#translate([-33,0,z/2])
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
#translate([0,0,z/2])    
rotate([90,0,0])
cylinder(100, 1.5, 1.5, center = true, $fn =20);
}
#import("C:/Users/einye/Desktop/isthisuni/robots/SR/main/example_mobile_holder/LegPart-v3.stl");
difference(){
hull(){
translate([0,5,5])
rotate([0,90,0])
cylinder(3,5,5, $fn = 20);
translate([0,10,0])
cube([3,19,10]);
}

translate([-1,5,5])
#rotate([0,90,0])
cylinder(7,2.5,2.5, $fn = 20);

translate([-1,12,5])
#rotate([0,90,0])
cylinder(7,.5,.5, $fn = 20);

translate([-1,18.5,5])
#rotate([0,90,0])
cylinder(7,.5,.5, $fn = 20);
}

difference(){
translate([-36,26,0])
cube([37,3,10]);
    
translate([-17,33,5])
#rotate([90,0,0])
cylinder(10,2.5,2.5, $fn = 20);
translate([-8,33,5])
#rotate([90,0,0])
cylinder(10,.5,.5, $fn = 20);
translate([-26,33,5])
#rotate([90,0,0])
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

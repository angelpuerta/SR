#import("C:/Users/einye/Desktop/isthisuni/robots/SR/main/example_mobile_holder/Hip.stl");

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
};

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

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
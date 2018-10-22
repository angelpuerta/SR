#translate([0,0,-40])
import("C:/Users/einye/Desktop/isthisuni/robots/SR/main/example_mobile_holder/BattRack.stl");

union(){
translate([12,0.5,-12])
cube([3,40,20]);
translate([15,0.5,-12])
cube([14,11.5,4]);
}

translate([0,40,0])
rotate(180)
union(){
translate([12,0.5,-12])
cube([3,40,20]);
translate([15,28,-12])
cube([14,11.5,4]);
}

translate([0,40,-2.5])
rotate(90)
cube([3,30,20],center=true);


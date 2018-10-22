#import("C:/Users/einye/Desktop/isthisuni/robots/SR/main/example_mobile_holder/Foot-Left.stl");
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
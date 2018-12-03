9g_motor();

module 9g_motor(){
    width = 11.8;
    height_til = 16;
    height_total = 31;
    depth_til = 22.2;
    depth_total = 32.2;
    

    difference(){
    cube([depth_til,width,height_til],center=true);
    translate([0,0,height_til/2])
    union(){
    cube([depth_total,width,2],center = true);        
   	cube([depth_til, width, height_total-height_til],center = true);
    translate([6,0,0])
    union(){
	cylinder(r=4, h = height_til+4, $fn = 20, center = true);		
    cylinder(r=2, h = height_til+8, $fn = 20, center = true);	
        }   
    } 
}
}

module arm(height=1, large=10, max_width=2){
    hull(){
        cylinder(r=1, h=height, $fn=20);
    translate([large,0,0])
        cylinder(r=1, h=height, $fn=20);
        translate([large/2,0,0])
        cylinder(r=max_width, h=height, $fn=20);
    }
        
}


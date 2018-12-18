
module 9g_motor(){
    width = 11.8;
    height_til = 16;
    height_total = 31;
    depth_til = 22.2;
    depth_total = 32.2;
    

    difference(){
    union(){
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
    }}
    
    translate([-depth_total/2.0,0,0])
    cylinder(h = height_total/2,r = 2,
    $fn = 20);
    mirror()
    { translate([-depth_total/2.0,0,0])
    cylinder(h = height_total/2,r = 2,
    $fn = 20);
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

module armed_9g_motor(){
    9g_motor();
    translate([1.5,0,31/2+4])
    arm();
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
};

translate([0,0,10])
cube([90,50,10],center=true);
}

union(){

union(){

translate([-21,0,0])
cube([13,23,100], center = true);

}

mirror()
union(){

translate([-21,0,0])
cube([13,23,100], center = true);
        }
       }
    }
}

module brace_support_9g(){
triangle_points =[[-32.2/2,0],[32.2/2,0],[0,50],[(-32.2+10)/2,5],[(32.2-10)/2,5],[0,30]];
 triangle_paths =[[0,1,2],[3,4,5]];
minor_triangle_points =[[-6.5,30],[6.5,30],[0,50]];   

difference(){
scale(1.2)
difference(){
union(){
translate([0,0,5.5])
cube([32.2,16 ,2],center=true);
translate([0,0,10.5])
cube([32.2,16 ,2],center=true);
translate([0,0,9.5])
 linear_extrude(height=2)   
 polygon(triangle_points,triangle_paths,10);    
    ;   
translate([0,0,4.5])
 linear_extrude(height=2)   
 polygon(triangle_points,triangle_paths,10);    
    ;
translate([0,0,6])
 linear_extrude(height=5)   
 polygon(minor_triangle_points,triangle_paths,10);    
}
9g_motor();
}
translate([-32.2/2.0,0,0])
cylinder(h = 31/2,r = 2,
    $fn = 20);
translate([32.2/2.0,0,0])
cylinder(h = 31/2,r = 2,
    $fn = 20);
}
}

module lapiz(){
    cylinder(h = 31/2,r = 2,
    $fn = 6);
}


module scara(){
hip();
difference(){
union(){
translate([-12.5,-32.2/2-4,0])
cube([25,5,20]);
translate([-12.5,32.2/2-1,0])
cube([25,5,20]);
translate([0,0,21])
cube([25,40, 3],center=true);
}
translate([0,0,40])
rotate([0,180,0])
#armed_9g_motor();
}
difference(){
translate([0,0,22])
brace_support_9g();
translate([7,43,53])
rotate([0,180,0])
#armed_9g_motor();
}

difference(){
translate([7,43,22+(32.2/2)-4.0])
brace_support_9g();
translate([7,43+40,22+(32.2/2)-4.0])
lapiz();
}
}

scara();

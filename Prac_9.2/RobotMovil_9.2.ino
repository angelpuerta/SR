#include <Servo.h>

Servo servoIzq;
Servo servoDer;

int NO_LINEA = LOW; 
int LINEA = HIGH;

int pinServoIzq = 8;
int pinServoDer = 9;

int pinInfraRojoIzq = 2;
int pinInfraRojoDer = 3;

int der = 0;
int iz = 0;

int numLoop = 1;


void setup(){
 //Serial.begin(9600); // Descomentar si queréis debuguear 

 pinMode(pinInfraRojoDer, INPUT);
 pinMode(pinInfraRojoIzq, INPUT);

 servoIzq.attach(pinServoIzq);
 servoDer.attach(pinServoDer);
}
void loop(){
   //No detecta linea, se para
  if(digitalRead(pinInfraRojoIzq) == NO_LINEA && digitalRead(pinInfraRojoDer) == NO_LINEA){
    entrarEnPista();
  } 
  //Linea recta
  else  if(digitalRead(pinInfraRojoIzq) == LINEA && digitalRead(pinInfraRojoDer) == LINEA){
        avanzar();
  }
   //Curva detectada 
  else if(digitalRead(pinInfraRojoIzq) == LINEA || digitalRead(pinInfraRojoDer) == LINEA){
         corregirTrayectoria();
  }
 }

  void  entrarEnPista(){
    if(digitalRead(pinInfraRojoIzq) == LINEA || digitalRead(pinInfraRojoDer) == LINEA){
        numLoop = 1;
        servoIzq.write(90);
        servoDer.write(90);
    }
    else{
      servoIzq.write(90-numLoop*5);
      servoDer.write(90+numLoop*5);
      numLoop = numLoop+1;
    }
    delay(100);
  }

 
  void corregirTrayectoria(){
    //linea detectada  a la derecha  
    if(digitalRead(pinInfraRojoIzq) == NO_LINEA && digitalRead(pinInfraRojoDer) == LINEA){
      servoIzq.write(0);
      servoDer.write(90);
      der = 1;
      iz = 0;
    }
    //linea detectada  a la izquierda  
    else  if(digitalRead(pinInfraRojoIzq) == LINEA && digitalRead(pinInfraRojoDer) == NO_LINEA){
      servoIzq.write(90);
      servoDer.write(180);
      iz = 1;
      der = 0;
    }
    delay(175); // Media vuelta
 }
 
 void avanzar(){
    servoIzq.write(0);
    servoDer.write(180);
    der = 0;
    iz = 0;
    delay(175); // Media vuelta
   }




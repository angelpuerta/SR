#include <Servo.h>

Servo servoIzq;
Servo servoDer;

int NO_LINEA = LOW; 
int LINEA = HIGH;

int pinServoIzq = 8;
int pinServoDer = 9;

int pinInfraRojoIzq = 2;
int pinInfraRojoDer = 3;

int numLoop = 0;
int time = 0;

void setup(){
 //Serial.begin(9600); // Descomentar si queréis debuguear 
 numLoop = 0;
 pinMode(pinInfraRojoDer, INPUT);
 pinMode(pinInfraRojoIzq, INPUT);

 servoIzq.attach(pinServoIzq);
 servoDer.attach(pinServoDer);
}
void loop(){
   //No detecta linea, busca
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
      servoIzq.write(90-numLoop);
      servoDer.write(180);
      incLoop();
    delay(800);
  }

 
  void corregirTrayectoria(){
      
    //linea detectada  a la derecha  
    if(digitalRead(pinInfraRojoIzq) == NO_LINEA && digitalRead(pinInfraRojoDer) == LINEA){
      servoIzq.write(0);
      servoDer.write(90);
    }
    //linea detectada  a la izquierda  
    else  if(digitalRead(pinInfraRojoIzq) == LINEA && digitalRead(pinInfraRojoDer) == NO_LINEA){
      servoIzq.write(90);
      servoDer.write(180);
    }
    numLoop = 0;
    delay(175); // Media vuelta
 }
 
 void avanzar(){
    
    servoIzq.write(0);
    servoDer.write(180);
    numLoop = 0;
    delay(175); // Media vuelta
   }
   void incLoop(){
    if(numLoop<60){
      numLoop++;
    }
   }



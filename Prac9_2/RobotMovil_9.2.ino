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
int timeNow = 0;

long xTiempo = 1000;

int iz = 1;
int der = 0;

void setup(){
 Serial.begin(9600); // Descomentar si queréis debuguear 
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
    if(numLoop>0){
      servoIzq.write(90+numLoop);
      servoDer.write(0);
      delay(50);
        }   
         corregirTrayectoria();
  }
 }

  void  entrarEnPista(){

    if(iz == 1){
      espiralIzquierda();
    }else{
      espiralDerecha();
    }      
  }

 
  void corregirTrayectoria(){
    //pasitoParaAtras();
     numLoop = 0;
    //linea detectada  a la derecha  
    if(digitalRead(pinInfraRojoIzq) == NO_LINEA && digitalRead(pinInfraRojoDer) == LINEA){
      servoIzq.write(0);
      servoDer.write(90);
      iz= 0;
      der = 1;
    }
    //linea detectada  a la izquierda  
    else  if(digitalRead(pinInfraRojoIzq) == LINEA && digitalRead(pinInfraRojoDer) == NO_LINEA){
      servoIzq.write(90);
      servoDer.write(180);
       iz= 0;
       der = 1;
    }
    numLoop = 0;
    delay(150); // Media vuelta
 }
 
 void avanzar(){
    //pasitoParaAtras();
    numLoop = 0;
    servoIzq.write(0);
    servoDer.write(180);
    numLoop = 0;
     iz= 1;
     der = 0;
    delay(150); // Media vuelta
   }
   void incLoop(){
    if(millis()-timeNow > xTiempo){
      Serial.println(millis()-timeNow);
      
      if(numLoop<60 ){
        numLoop++;
    }
    timeNow = millis();
   }
   }
   void espiralIzquierda(){
    incLoop();
      servoIzq.write(90-numLoop);
      servoDer.write(180);
      delay(100);
      Serial.println(90-numLoop);
   }

   void espiralDerecha(){
    incLoop();
      servoIzq.write(0);
      servoDer.write(90+numLoop);
      delay(100);
      Serial.println(90+numLoop);

   }
   void pasitoParaAtras(){
    if(numLoop>0){
      servoIzq.write(180);
      servoDer.write(0);
      delay(50);
    }
   }

#include <Servo.h>

Servo servoIzq;
Servo servoDer;

int NO_LINEA = LOW; 
int LINEA = HIGH;

int pinServoIzq = 8;
int pinServoDer = 9;

int pinInfraRojoIzq = 2;
int pinInfraRojoDer = 3;


void setup(){
 //Serial.begin(9600); // Descomentar si queréis debuguear 

 pinMode(pinInfraRojoDer, INPUT);
 pinMode(pinInfraRojoIzq, INPUT);

 servoIzq.attach(pinServoIzq);
 servoDer.attach(pinServoDer);
}
void loop(){
  if(digitalRead(pinInfraRojoIzq) == NO_LINEA || digitalRead(pinInfraRojoDer) == NO_LINEA){
 servoIzq.write(0);
 servoDer.write(0);
 }else if(){
 servoIzq.write(180);
 servoDer.write(180);
 delay(1500); // Media vuelta
 }

}

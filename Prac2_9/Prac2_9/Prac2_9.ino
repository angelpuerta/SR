#include <TM1637.h>

const int pinTrig = 9;
const int pinEcho = 6;
const int SENSOR = 8;
const int pinClk = 3;
const int pinDio = 4;
const int RED_LED = 10;

int RGB_LEDS[] = {RED_LED, 11, 12};
int RGB_length = sizeof(RGB_LEDS)/sizeof(int);

const int DISTANCE_TRESHOLD = 0.1;
const long MIN_DISTANCE = 5.0;

const int MIN_COUNT = 3;
const float MIN_VELOCITY = 1.0;

TM1637 screen(pinClk,pinDio);

void setup() {
  Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, OUTPUT);

  for(int i; i < RGB_length; i++){
    pinMode(RGB_LEDS[i], OUTPUT);
  }

  randomSeed(analogRead(0));
  
   screen.init();
   screen.set(BRIGHT_TYPICAL);
  delay(1500);
}


boolean isSomethingMoving(){
  long previous_distance = detectedDistance();
  delay(100);
  long actual_distance = detectedDistance();
  return fabs(actual_distance - previous_distance) > DISTANCE_TRESHOLD;  
}

/*
 * Detected distance in cm
 */
long detectedDistance (){
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);

  long responseTime = pulseIn(pinEcho, HIGH);
  return long(0.01716*responseTime);
}

void updateScreen(int time){
  screen.clearDisplay();
  screen.display(0, time);
  delay(500);
}

/*
 * Time in s
 */
int getTime (){
    return random(MIN_COUNT)+ 2;
}

/*
 * Velocity for that iteration
 */
 float getVelocity(){
  return ((random(100)+100)/100.0)*MIN_VELOCITY;
}

boolean play(){
  long startTime = millis();
  long wait = getTime()*1000;
  float velocity = getVelocity();

  long difference = wait - (millis()-startTime)*velocity;
  updateScreen(wait%1000);

  while(difference > 0){
    if(isSomethingMoving())
      return false;     
    difference = wait - (millis()-startTime)*velocity;
    updateScreen(difference%1000); 
  }
  return true;
}

void win(){
   for(int i; i < 15; i++){
    digitalWrite(RGB_LEDS[i+1%3], HIGH);
    digitalWrite(RGB_LEDS[i%3],LOW);
    delay(100);
   }
}

void lose(){
  screen.clearDisplay();
  for(int i; i < 10; i++){
    digitalWrite(RED_LED, HIGH);
    delay(50);
    digitalWrite(RED_LED,LOW);
  }
}

 

void loop() {
  if(detectedDistance() <= MIN_DISTANCE)
    win();
  if(!play())
    lose();
    
}

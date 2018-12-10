#include <TM1637.h>

const int PIN_TRIG = 9;
const int PIN_ECHO = 11;
const int pinClk = 3;
const int pinDio = 4;
const int RED_LED = 10;

int RGB_LEDS[] = {RED_LED, 13, 12};
int RGB_length = sizeof(RGB_LEDS)/sizeof(int);

const int DISTANCE_TRESHOLD = 20;
const long MIN_DISTANCE = 25.0;

const int MIN_COUNT = 3;
const float MIN_VELOCITY = 1.0;

TM1637 screen(pinClk,pinDio);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);  

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
  //Medir distancia
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);

  digitalWrite(PIN_TRIG, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);

  long responseTime = pulseIn(PIN_ECHO, HIGH);

  return long(0.01716*responseTime);
}

void updateScreen(int time){
  Serial.println("DISPLAY");
  if(time < 0)
    time = 0;
  Serial.println(time);
  screen.clearDisplay();
  screen.display(0, time);
  delay(250);
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
  return 0.5;//((random(100)+100)/100.0)*MIN_VELOCITY;
}

boolean play(){
  long startTime = millis();
  long wait = getTime()*1000;
  float velocity = getVelocity();

  long difference = wait - (millis()-startTime)*velocity;
  updateScreen(wait/1000);
  Serial.println("PLAY");
  Serial.println(difference);

  
  while(difference > 0){
    if(isSomethingMoving())
      return false;     
    difference = wait - (millis()-startTime)*velocity;
    Serial.println(difference);
    updateScreen(difference/1000); 
  }
  screen.clearDisplay();
  return true;
}

void win(){ 
   for(int i = 0; i < 15; i++){
    digitalWrite(RGB_LEDS[(i+1)%3], HIGH);
    delay(200);
    digitalWrite(RGB_LEDS[(i%3)],LOW);
    delay(200);
   }
    Serial.println("YOU WIN");
}

void lose(){
  screen.clearDisplay();
  for(int i=0; i < 10; i++){
    digitalWrite(RED_LED, HIGH);
    delay(100);
    digitalWrite(RED_LED,LOW);
    delay(100);
  }
  Serial.println("YOU LOOSE");
  delay(1000);
}

 

void loop() {
  if(detectedDistance() <= MIN_DISTANCE){
    Serial.println(detectedDistance());
    win();
  }
  else if(!play())
    lose();
  delay(1000);
    
}

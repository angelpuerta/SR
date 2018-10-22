#include <Servo.h>

#define PIN_X A0
#define PIN_SERVO 9

Servo s;

void setup() {
  pinMode(PIN_X, INPUT);
  s.attach(PIN_SERVO);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(PIN_X);
  //Serial.println(String(val));
  if (val < 100) {
    s.write(0);
  } else if (val < 400) {
    s.write(75);
  } else if (val < 600) {
    s.write(90);  
  } else if (val < 900) {
    s.write(105);
  } else {
    s.write(180);
  }
  delay(15);
}

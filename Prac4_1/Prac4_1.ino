#include <Servo.h>

#define PIN_X A0
#define PIN_SERVO 9

Servo s;

void setup() {
  pinMode(PIN_X, INPUT);
  s.attach(PIN_SERVO);
}

void loop() {
  int val = analogRead(PIN_X);
  if (val < 400) {
    s.write(45);
  } else if (val > 600) {
    s.write(135);
  } else {
    s.write(90);  
  }
  delay(15);
}

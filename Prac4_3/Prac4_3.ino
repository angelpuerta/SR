#include <Servo.h>

#define AUTO 0
#define MANUAL 1

#define FORWARDS 0  //Se aleja del servo  (45)
#define BACKWARDS 1

#define PIN_X A0
#define PIN_BTN 5

#define PIN_SERVO 9

#define PIN_STOP_1 3 //El del servo
#define PIN_STOP_2 4

int modo = MANUAL;
int dir = FORWARDS;
Servo s;

void manual() {
  int val = analogRead(PIN_X);
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

void automatico() {
  //Serial.println("S1: " + String(digitalRead(PIN_STOP_1)) + " S2: " + String(digitalRead(PIN_STOP_2)));
  if (dir == FORWARDS && digitalRead(PIN_STOP_2) == LOW) {
    s.write(45);
    dir = BACKWARDS;
    Serial.println("Backwards");
  } else if (dir == BACKWARDS && digitalRead(PIN_STOP_1) == LOW) {
    s.write(135);
    dir = FORWARDS;
    Serial.println("Forwards");
  }
  delay(5);
}

void setup() {
  pinMode(PIN_X, INPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_STOP_1, INPUT);
  pinMode(PIN_STOP_2, INPUT);
  s.attach(PIN_SERVO);
  Serial.begin(9600);
}

void loop() {
  //Cambiar modo
  if (digitalRead(PIN_BTN) == LOW) {
    modo = modo == MANUAL ? AUTO : MANUAL;
    if (modo == AUTO) {
      dir = FORWARDS;
      s.write(135);
    }
    Serial.println(modo == MANUAL ? "Manual" : "Automatico");
    delay(150);
  }
  //Modo
  if (modo == MANUAL)
    manual();
  else if (modo == AUTO)
    automatico();
}

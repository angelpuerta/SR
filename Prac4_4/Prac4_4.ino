#include <Servo.h>

#define MAX_POS 50

#define FORWARDS 45   //Se aleja del servo (Al S2)
#define BACKWARDS 135 //Se acerca al servo (Al S1)

#define PIN_SERVO 9

#define PIN_STOP_1 3  //El del servo
#define PIN_STOP_2 4  //El del extremo

Servo s;

int pos = 0;
long millisStep = 0;

void calibrar() {
  Serial.println("Calibrando...");
  //Si no esta en un fin
  if (digitalRead(PIN_STOP_1) != LOW && digitalRead(PIN_STOP_2) != LOW) { 
      Serial.println("Moviendo hasta extremo...");
      s.write(FORWARDS);
      while (digitalRead(PIN_STOP_2) != LOW) {
        delay(5);
      }
      s.write(90);
      Serial.println("Movido hasta el extremo");
  }
  //Ir a la posición opuesta
  long t = millis();
  s.write(BACKWARDS);
  while (digitalRead(PIN_STOP_1) != LOW)
     delay(1);
  millisStep = millis() - t;
  s.write(90);
  Serial.println("Calibrado, ms: " + String(millisStep));
}

void irAPos(int p) {
  int dir = pos - p > 0 ? BACKWARDS : FORWARDS;
  int delta = abs(pos - p);
  long m = (millisStep / MAX_POS) * delta;
  //Mover
  long t = millis();
  s.write(dir);
  while (millis() - t <= m)
    delay(1);
  s.write(90);
  pos = p;
}

void setup() {
  pinMode(PIN_STOP_1, INPUT);
  pinMode(PIN_STOP_2, INPUT);
  s.attach(PIN_SERVO);
  Serial.begin(9600);
  calibrar();
}

void loop() {
  if (Serial.available() > 0) {
    int pos = Serial.parseInt();
    pos = constrain(pos, 0, MAX_POS);
    irAPos(pos);
  }
}

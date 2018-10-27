#include <Servo.h>

#define PIN_SERVO_X 9
#define PIN_SERVO_Y 11
#define PIN_SERVO_P 7

#define PIN_X A0
#define PIN_Y A1
#define PIN_P A2

#define GMAX 110
#define GMIN 10
#define STEP_PINZA 5

Servo servoX;
Servo servoY;
Servo servoP;

int posP = 120;

void moverPinza(int val) {
  if (val < 300)
    posP = max(GMIN, pos - STEP_PINZA);
  else if (val > 700)
    posP = min(GMAX, pos + STEP_PINZA);
  //Mover
  servoP.write(posP);
}

void moverEje(Servo s, int val) {
  if (val < 400 && val > 600)
    s.write(map(val,0,1023,0,180));
}

void setup() {
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_P, INPUT);
  servoX.attach(PIN_SERVO_X);
  servoY.attach(PIN_SERVO_Y);
  servoP.attach(PIN_SERVO_P);
  Serial.begin(9600);
}

void loop()
{
  //Control de pinza
  moverPinza(analogRead(PIN_P));
  //Control de brazo
  moverEje(servoX, analogRead(PIN_X));
  moverEje(servoY, analogRead(PIN_Y));
  delay(50);
}

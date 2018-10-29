#include <Servo.h>

#define COMMAND_SEP ";"
#define PARAMETER_SEP ','

#define INPUT_SIZE 30

#define MAX_POS 24

#define FORWARDS 135   //Se aleja del servo (Al S2)
#define BACKWARDS 45 //Se acerca al servo (Al S1)

#define PIN_SERVO 7

#define PIN_STOP_1 12  //El del servo
#define PIN_STOP_2 11  //El del extremo

Servo s;
//0,500;20,500;10,2000;0,0;
int pos = 0;
long millisStep = 0;

void calibrar() {
  
  Serial.println("Calibrando...");
  //Si no esta en un fin
  if (digitalRead(PIN_STOP_2) != LOW) { 
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

String serialResponse = "";

void loop()
{
  if ( Serial.available()) {
    serialResponse = Serial.readStringUntil('\r\n');
    char buf[INPUT_SIZE];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *command;
    while ((command = strtok_r(p, COMMAND_SEP, &p)) != NULL) {
      char* separator = strchr(command, PARAMETER_SEP);
      if (separator != NULL)
      {
        *separator = 0;
        int p = atoi(command);
        ++separator;
        int d = atoi(separator);
        Serial.println("Pos: " + String(p) + " Delay: " + String(d));
        irAPos(p);
        delay(d);
      }
    }
  }
}

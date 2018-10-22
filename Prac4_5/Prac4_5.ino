#include <Servo.h>

#define INPUT_SIZE 30
#define COMMAND_SEP ';'
#define PARAMETER_SEP ','

#define INPUT_SIZE 30

#define MAX_POS 24

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
  //calibrar();
}

//String bfr;
//void loop() {
//  bfr = Serial.readStringUntil(COMMAND_SEP);
//  if (bfr.length() > 0) {
//    int pos = bfr.indexOf(COMMAND_SEP);
//    String com = bfr.substring(0, pos);
//    if (com.length() > 0) {
//        int posSep = com.indexOf(PARAMETER_SEP);
//        int p = atoi(com.substring(0,posSep));
//        int d = atoi(com.substring(posSep + 1,com.length() - 1));
//        Serial.println("Pos: " + String(p) + " Delay: " + String(d));
//        //irAPos(p);
//        //delay(d);
//    }
//  }
//}


char input[INPUT_SIZE + 1];
void loop() {
  // Get next command from Serial (add 1 for final 0)
  byte sz = Serial.readBytes(input, INPUT_SIZE);
  // Add the final 0 to end the C string
  input[sz] = 0;
  // Read each command pair 
  char* command = strtok(input, COMMAND_SEP);
  while (command != NULL) {
    // Split the command in two values
    char* separator = strchr(command, PARAMETER_SEP);
    if (separator != NULL)
    {
        *separator = 0;
        int p = atoi(command);
        ++separator;
        int d = atoi(separator);
        Serial.println("Pos: " + String(p) + " Delay: " + String(d));
        //irAPos(p);
        delay(d);
    }
    // Find the next command in input string
    command = strtok(NULL, COMMAND_SEP);
  }
}

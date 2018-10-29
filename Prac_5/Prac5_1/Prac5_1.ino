#include <Servo.h>

#define INPUT_SIZE 30
#define COMMAND_SEP ";"
#define PARAMETER_SEP ','

#define INPUT_SIZE 30
#define DT 1000

#define MAX_POS 24

#define FORWARDS 45   //Se aleja del servo (Al S2)
#define SLOW_FORWARDS 75
#define SLOW_BACKWARDS 105
#define BACKWARDS 135 //Se acerca al servo (Al S1)

#define PIN_SERVO 9

#define PIN_STOP_1 3  //El del servo
#define PIN_STOP_2 4  //El del extremo

#define PIN_X A0

#define RECORD 0
#define REPRODUCE 1

long last_t = 0;

int forwards[] = {SLOW_FORWARDS, FORWARDS};
int backwards[] = {SLOW_BACKWARDS, BACKWARDS};

Servo s;

int posX = 0;
int posY = 0;
int posP = 0;
int mode = 0;
long millisStep[] = {0,0};

void calibrar(int mode) {
  Serial.println("Calibrando...");
  //Si no esta en un fin
  if (digitalRead(PIN_STOP_1) != LOW && digitalRead(PIN_STOP_2) != LOW) { 
      Serial.println("Moviendo hasta extremo...");
      s.write(forwards[mode]);
      while (digitalRead(PIN_STOP_2) != LOW) {
        delay(5);
      }
      s.write(90);
      Serial.println("Movido hasta el extremo");
  }
  //Ir a la posición opuesta
  long t = millis();
  s.write(backwards[mode]);
  while (digitalRead(PIN_STOP_1) != LOW)
     delay(1);
  millisStep[mode] = millis() - t;
  s.write(90);
  Serial.println("Calibrado, ms: " + String(millisStep[mode])+ " MODO" + mode);
}

void irAPos(int &pos, int p) {
  int dir = pos - p > 0 ? forwards[mode] : backwards[mode];
  int delta = abs(pos - p);
  long m = (millisStep[mode] / MAX_POS) * delta;
  //Mover
  long t = millis();
  s.write(dir);
  while (millis() - t <= m)
    delay(1);
  s.write(90);
  pos = p;
}

String serialResponse = "";
void readBuffer(){
  if ( Serial.available()) 
    serialResponse = Serial.readStringUntil('\r\n');
}

void control(){
 int val = analogRead(PIN_X);
 if (val < 400)
    irAPos(pos-1);
 else if (val < 900) 
    irAPos(pos+1);  
  delay(15);
}

void freeMode(){
  mode = REPRODUCE;
  control();
}

void sendData() {
  String data = "%d,%d,%d;";
  sprintf(data, posX, posY, posP);
  Serial.print(data);
}

void recordMode(){
 mode = RECORD;
 control();
 if (millis() - last_t > DT) {
    sendData();
    last_t = millis();
 }
}

void reproduceMode(){
    mode = REPRODUCE;
    readBuffer();
    char buf[INPUT_SIZE];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *command;
    while ((command = strtok_r(p, COMMAND_SEP, &p)) != NULL) {
      char* separator = strchr(command, PARAMETER_SEP);
      if (separator != NULL)
      {
        *separator = 0;
        int px = atoi(command);
        ++separator;
        int py = atoi(separator);
        irAPos(px);
      }
    }
}

void setup() {
  pinMode(PIN_X, INPUT);
  pinMode(PIN_STOP_1, INPUT);
  pinMode(PIN_STOP_2, INPUT);
  s.attach(PIN_SERVO);
  Serial.begin(9600);
  calibrar(RECORD);
  calibrar(REPRODUCE);
  last_t = millis();
}

int movement_type = 0;

void loop()
{
  readBuffer();
  
    if(serialResponse[0] == 'L'){
      movement_type = 0;
    } else if(serialResponse[0] == 'G'){
      movement_type = 1;
    } else if(serialResponse[0] == 'R'){
      movement_type = 2;
    }
     
    switch(movement_type){
      case 0:
        freeMode();
        break;
      case 1:
        recordMode();
        break;
      case 2:
        reproduceMode();
        break;  
      default:
        Serial.println("Modo desconocido");
        break;
    }
}


 
     

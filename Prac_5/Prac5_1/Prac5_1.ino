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

#define FREE_MODE 0
#define RECORDING 1
#define PLAYING   2

long last_t = 0;

int forwards[] =  {SLOW_FORWARDS,  FORWARDS};
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
      s.write(FORWARDS);
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
  Serial.println("Calibrado, ms: " + String(millisStep[mode])+ " MODO: " + String(mode));
}

void moveArm(Servo srv,int pos, int p) {
  int dir = pos - p > 0 ? forwards[mode] : backwards[mode];
  int delta = abs(pos - p);
  long m = (millisStep[mode] / MAX_POS) * delta;
  //Mover
  long t = millis();
  srv.write(dir);
  while (millis() - t <= m)
    delay(1);
  srv.write(90);
}

void irAPos(int px, int py,int pp) {
  px = constrain(px, 0, MAX_POS);
  moveArm(s,posX,px);
  posX = px;
}

String serialResponse = "";
void readBuffer(){
  if ( Serial.available()) 
    serialResponse = Serial.readStringUntil('\r\n');
}

void control(){
  int val = analogRead(PIN_X);
  if (val < 400) {
    irAPos(posX + 1,posY,posP);
  } else if (val < 900)  {
    irAPos(posX - 1,posY,posP); 
  } 
  delay(15);
}

void freeMode(){
  mode = REPRODUCE;
  control();
}

void sendData() {
  char* data = "%d,%d,%d;";
  sprintf(data, posX, posY, posP);
  Serial.print(data);
}

void recordMode(){

 control();
 if (millis() - last_t > DT) {
    sendData();
    last_t = millis();
 }
}

void reproduceMode(){
    char buf[INPUT_SIZE];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *command;
    while ((command = strtok_r(p, COMMAND_SEP, &p)) != NULL) {
      int pos = atoi(command);
      irAPos(pos,0,0);
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

int state = FREE_MODE;

void loop()
{
  readBuffer();
  
    if(serialResponse[0] == 'L'){
      state = FREE_MODE;
    } else if(serialResponse[0] == 'G'){
      mode = RECORD;
      state = RECORDING;
    } else if(serialResponse[0] == 'R'){
      mode = REPRODUCE;
      state = PLAYING;
    }
     
    switch(state){
      case FREE_MODE:
        freeMode();
        break;
      case RECORDING:
        recordMode();
        break;
      case PLAYING:
        reproduceMode();
        break;  
      default:
        Serial.println("Modo desconocido");
        break;
    }
}


 
     

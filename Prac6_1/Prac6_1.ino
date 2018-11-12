#include <Ultrasonic.h>
#include <Servo.h>

#define MAX_POS 24

#define FORWARDS 45   //Se aleja del servo (Al S2)
#define BACKWARDS 135 //Se acerca al servo (Al S1)

#define START_X 0
#define END_X  20

#define VASO_X 23
#define VASO_Y 10
#define DISTANCIA_VASO 50.0 //En centimentros

#define PIN_SERVO_X 5
#define PIN_SERVO_Y 9
#define PIN_SERVO_P 6

#define PIN_STOP_1_X 11  //El del servo
#define PIN_STOP_2_X 12  //El del extremo

#define PIN_STOP_1_Y 3  //El de servo
#define PIN_STOP_2_Y 7   //El del extremo

#define PIN_TRIGGER 5
#define PIN_ECHO    10

class Arm {
  private:
    int stop1;
    int stop2;
    Servo srv;
    long milliseconds; //Milisegundos
    int pos = 0;
  public:
    void configArm(int s1, int s2, int ps) {
      stop1 = s1;
      stop2 = s2;
      pinMode(stop1, INPUT);
      pinMode(stop2, INPUT);
      srv.attach(ps);
    };
    void calibrar() {
      Serial.println("Calibrando...");
      //Si no esta en un fin
      if (digitalRead(stop2) != LOW) { 
          Serial.println("Moviendo hasta extremo...");
          srv.write(FORWARDS);
          while (digitalRead(stop2) != LOW) {
            delay(5);
          }
          srv.write(90);
          Serial.println("Movido hasta el extremo");
      }
      //Ir a la posición opuesta
      long t = millis();
      srv.write(BACKWARDS);
      while (digitalRead(stop1) != LOW)
         delay(1);
      milliseconds = millis() - t;
      srv.write(90);
      Serial.println("Calibrado, ms: " + String(milliseconds));
    };
  
    void irAPos(int p) {
      p = constrain(p, 0, MAX_POS);
      int dir = pos - p < 0 ? FORWARDS : BACKWARDS;
      int delta = abs(pos - p);
      long m = (milliseconds / MAX_POS) * delta;
      //Mover
      long t = millis();
      srv.write(dir);
      while (millis() - t <= m)
        delay(1);
      srv.write(90);
      pos = p;
    };

    int getPos() {
      return pos;
    };
};

Arm* ejeX = new Arm();
Arm* ejeY = new Arm();
Servo pinza;
Ultrasonic ultrasonic(PIN_TRIGGER,PIN_ECHO);

void cerrar() {
  pinza.write(145);
}

void abrir() {
  pinza.write(20);
}

void dejar() {
  Serial.println("Cogiendo cubo...");
  int pos = ejeX->getPos();
  ejeY->irAPos(MAX_POS);
  cerrar();
  Serial.println("Moviendo cubo...");
  ejeY->irAPos(VASO_Y);
  ejeX->irAPos(VASO_X);  
  Serial.println("Soltando cubo...");
  abrir();
  Serial.println("Cubo dejado");
  ejeY->irAPos(12);
  ejeX->irAPos(pos);
}

bool vasoDetectado() {
  double distance = ultrasonic.read(CM);
  Serial.println("Distancia: " + String(distance));
  return distance < DISTANCIA_VASO;
}

void setup() {
  Serial.begin(9600);
  //Configurar brazos
  ejeX->configArm(PIN_STOP_1_X, PIN_STOP_2_X, PIN_SERVO_X);
  ejeY->configArm(PIN_STOP_1_Y, PIN_STOP_2_Y, PIN_SERVO_Y);
  pinza.attach(PIN_SERVO_P);
  //Calibrar
  ejeX->calibrar();
  ejeY->calibrar();
  Serial.println("Todos los brazos calibrados");
  //Mover a la posicion inicial
  abrir();
  ejeX->irAPos(20);
  ejeY->irAPos(12);
}

void loop()
{
  for (int x = START_X;x <= END_X;x++) {
    ejeX->irAPos(x);
    if (vasoDetectado())
      dejar();
  }
  for (int x = END_X;x >= START_X;x--) {
    ejeX->irAPos(x);
    if (vasoDetectado())
      dejar();
  }
}


 
     

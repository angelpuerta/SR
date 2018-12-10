#include <Keypad.h>

#define GREEN_LED 7
#define RED_LED 8

#define PIN_TRIG 9
#define PIN_ECHO 11

#define PASSWORD "9876"

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte pfilas[nfilas] = {2, 3, 4, 5}; // Filas
byte pcolumnas[ncolumnas] = {A0, A1, A2, A3}; //Columnas

Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas,
nfilas, ncolumnas);

String bufferLectura = "";

int contador = 0;

void abrir() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}

void cerrar() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void parpadear() {
  for(int i = 0; i<3; i++){
    digitalWrite(GREEN_LED, LOW);
    delay(100);
    digitalWrite(GREEN_LED, HIGH);
    delay(100);
  }
}

void updateBuffer() {
  char c = teclado.getKey();
  if (c != '\0' && isDigit(c)) {
    bufferLectura += c;
  }
}

bool hayAlgo() {
  //Medir distancia
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);

  digitalWrite(PIN_TRIG, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);

  long responseTime = pulseIn(PIN_ECHO, HIGH);
  long distance = int(0.01716*responseTime);
  Serial.println(distance);
  //Comprobar
  return distance <= 10;
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT); 
  pinMode(PIN_ECHO, INPUT); 
  cerrar();
  Serial.begin(9600);
}

void loop() {
  hayAlgo();
  
}

#include <TM1637.h>
#include <Keypad.h>

#define GREEN_LED 7
#define RED_LED 8

#define PIN_CLK 10
#define PIN_DIO 12

#define PIN_TRIG 9
#define PIN_ECHO 11

#define PIN_SLUZ A5
#define THRESHOLD 150

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

Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas);
TM1637 screen(PIN_CLK, PIN_DIO);

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

bool hayAlgoExterior() {
  //Medir distancia
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);

  digitalWrite(PIN_TRIG, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);

  long responseTime = pulseIn(PIN_ECHO, HIGH);
  long distance = int(0.01716*responseTime);
  //Comprobar
  return distance <= 10;
}

bool hayAlgoInterior() {
  int val = analogRead(PIN_SLUZ);
  return val < THRESHOLD;
}

void updateContador() {
 int digit0 =  contador/1000;
 int digit1 = (contador - digit0*1000)/100;
 int digit2 = (contador - (digit0*1000 + digit1*100))/10;
 int digit3 =  contador - (digit0*1000 + digit1*100 + digit2*10);

 screen.display(0, digit0);
 screen.display(1, digit1);
 screen.display(2, digit2);
 screen.display(3, digit3);
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT); 
  pinMode(PIN_ECHO, INPUT); 
  pinMode(PIN_SLUZ, INPUT);
  cerrar();
  screen.init();
  screen.set(BRIGHT_TYPICAL);
  delay(1500);// Esperamos a que se inicie la pantalla
  Serial.begin(9600);
}

void loop() {
  updateBuffer();
  Serial.println(bufferLectura);
  if (hayAlgoInterior()) {
    abrir();
    while(hayAlgoExterior() || hayAlgoInterior())
      delay(5);
    cerrar();
  } else if (bufferLectura.length() >= 4) {
    if (bufferLectura.equals(PASSWORD)) { //Es correcta
      digitalWrite(GREEN_LED, LOW);
      delay(1000);
      puerta_abierta:
      abrir();
      if(!hayAlgoInterior()) {
        double inicioCuentaTiempo = millis();
        while(millis() - inicioCuentaTiempo < 5000) {
        if (hayAlgoExterior())
          inicioCuentaTiempo = millis();
        else if (teclado.getKey() == 'C')
          break;
        }
        contador++;
        cerrar();
        bufferLectura = "";
     } else if (hayAlgoInterior() && hayAlgoExterior()){
       goto puerta_abierta; 
     } else if (hayAlgoInterior() && !hayAlgoExterior()){
        cerrar(); 
        contador++;
        bufferLectura = ""; 
     }
    } else { //Contraseña incorrecta
      parpadear();
      cerrar();
      bufferLectura = "";
    }
    delay(1000);
  }
  updateContador();
  delay(150);
}

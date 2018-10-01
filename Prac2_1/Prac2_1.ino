#include <Keypad.h>

#define GREEN_LED 7
#define RED_LED 8

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

void abrir() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}

void cerrar() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  cerrar();
}

void loop() {
  if (teclado.getKey() == 'A') {
    abrir();
    delay(5000);
    cerrar();
  }
}

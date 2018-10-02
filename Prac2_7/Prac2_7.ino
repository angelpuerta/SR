#include <TM1637.h>
#include <Keypad.h>

#define PIN_CLK 11
#define PIN_DIO 12

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte pf1[nfilas] = {2, 3, 4, 5}; 
byte pc1[ncolumnas] = {A0, A1, A2, A3}; 

byte pf2[nfilas] = {6, 7, 8, 9}; 
byte pc2[ncolumnas] = {A4, A5, 10, 13}; 

Keypad t1 = Keypad(makeKeymap(teclas), pf1, pc1, nfilas, ncolumnas);
Keypad t2 = Keypad(makeKeymap(teclas), pf2, pc2, nfilas, ncolumnas);
TM1637 screen(PIN_CLK, PIN_DIO);

//Puntuación
int c1 = 0;
int c2 = 0;

void displayScores() {
  displayScore(c1, 0);
  displayScore(c2, 2);
}

void displayScore(int n, int displayNumber) {
  int first = n / 10;
  int second = n - first * 10;
  screen.display(displayNumber,      first);
  screen.display(displayNumber + 1, second);
}

void setup() {
  screen.init();
  screen.set(BRIGHT_TYPICAL);
}

void loop() {
  // put your main code here, to run repeatedly:

}

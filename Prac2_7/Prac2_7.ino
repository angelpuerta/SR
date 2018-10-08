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

int rondas = 3;
int dificultad = 2; //Del 1 al 3

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

//Menu

int preguntarOp() {
  Serial.print("Introduzca la opción: ");
  while (Serial.available() <= 0)
    delay(5);
  return Serial.parseInt();
}

void cambiarDificultad() {
  Serial.println("Dificultad actual: " + dificultad);
  int op = preguntarOp();
  while (op < 1 || op > 3) 
    op = preguntarOp(); 
  dificultad = op;
  Serial.println("Dificultad cambiada a: " + dificultad);
}

void cambiarRondas() {
  Serial.println("Rondas actuales: " + rondas);
  int op = preguntarOp();
  while (op < 1 || op > 3) 
    op = preguntarOp(); 
  rondas = op;
  Serial.println("Rondas cambiadas a: " + rondas);
}

void configurar() {
  //Imprimir menu
  Serial.println("---Menu del juego---");
  Serial.println("  1 - Cambiar dificultad");
  Serial.println("  2 - Cambiar rondas");
  Serial.println("  3 - Comenzar juego");
  bool configurando = true;
  while (configurando) {
    //Preguntar opcion
    int op = preguntarOp();
    while (op < 1 || op > 3) 
      op = preguntarOp();
    //Ejecutar
    switch (op) {
      case 1:
      cambiarDificultad();
      break;
      case 2:
      cambiarRondas();
      break;
      case 3:
      configurando = false;
      break;
    }
  }
}

//Juego

void juego() {
  while (int ronda = 1;ronda <= rondas;ronda++) {
    Serial.println("Ronda: " + ronda);
    //Generar problema
    
    //Preguntar
    
  }
  //Decir ganador
  if (c1 == c2)
    Serial.println("Empate");
  else if (c1 > c2)
    Serial.println("Ha ganado el jugador 1");
  else
    Serial.println("Ha ganado el jugador 2");
  //Reiniciar contadores
  c1 = 0;
  c2 = 0;
}

void setup() {
  screen.init();
  screen.set(BRIGHT_TYPICAL);
  Serial.begin(9600);
  Serial.println("Juego matemático V1.0");
}

void loop() {
  configurar();
  Serial.println("Juego comenzado!!!");
  juego();
}

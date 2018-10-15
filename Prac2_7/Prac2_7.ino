#include <TM1637.h>
#include <Keypad.h>

#define PIN_CLK 10
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

Keypad teclado = Keypad(makeKeymap(teclas), pf1, pc1, nfilas, ncolumnas);
TM1637 screen(PIN_CLK, PIN_DIO);

//Puntuación
int c1 = 0;
int c2 = 0;
//Configuracion
int rondas = 3;
int dificultad = 2; //Del 1 al 3
//Problema
int sol;

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

String toStr(int n) {  
  char cadena[8];
  sprintf(cadena, "%d", n);
  return cadena;
}

int preguntarNumero(String msg) {
  Serial.print(msg);
  while (Serial.available() <= 0)
    delay(5);
  int n = Serial.parseInt();
  Serial.println();
  return n;
}

void cambiarDificultad() {
  Serial.println("Dificultad actual: " + toStr(dificultad));
  int op = preguntarNumero("Dificultad: ");
  while (op < 1 || op > 3) 
    op = preguntarNumero("Dificultad (entre 1 y 3): "); 
  dificultad = op;
  Serial.println("Dificultad cambiada a: " + toStr(dificultad));
}

void cambiarRondas() {
  Serial.println("Rondas actuales: " + toStr(rondas));
  int op = preguntarNumero("Rondas: ");
  while (op < 1 || op > 10) 
    op = preguntarNumero("Rondas (entre 1 y 10): "); 
  rondas = op;
  Serial.println("Rondas cambiadas a: " + toStr(rondas));
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
    int op = preguntarNumero("Opcion: ");
    while (op < 1 || op > 3) 
      op = preguntarNumero("Opcion (entre 1 y 3): ");
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

void generarProblema() {
    int minNum = pow(10, dificultad - 1);
    int maxNum = pow(10, dificultad);
    int n1 = random(minNum,maxNum);
    int n2 = random(minNum,maxNum);
    int aux = 0;
    int op = random(1,4);
    char opC = ' ';
    switch(op) {
      case 1:
        sol = n1 + n2;
        opC = '+';
      break;
      case 2:
        if(n1 - n2 < 0){
          aux  = n1;
          n1 = n2;
          n2 = aux;
        }
        sol = n1 - n2;
        opC = '-';
      break;
      case 3:
        sol = n1 * n2;
        opC = '*';
      break;
    }
    char problema[32];
    sprintf(problema, "Cuanto es %i %c %i?", n1, opC, n2);
    Serial.println(problema);
}

int preguntarTeclado(String msg) {
  Serial.println(msg);
  String bfr = "";
  while(true) {
      char c = teclado.getKey();
      if (c == '*')
        break;
      else if (c != '\0' && isDigit(c)) 
        bfr += c;
      delay(5);
  }
  Serial.println("Has introducido: " + bfr);
  return bfr.toInt();
}

void preguntarJugador(int &score) {
  long t1 = millis();
  while (preguntarTeclado("Respuesta: ") != sol) {
    Serial.println("Respuesta incorrecta!");
    score = max(0, score - 10);
    delay(15);
  }
  long t = millis() - t1;
  score += (dificultad * 50000)/ t;
}

void preguntar() {
  Serial.println("Jugador 1: ");
  preguntarJugador(c1);
  Serial.println("Puntos del jugador 1: " + toStr(c1));
  Serial.println("Jugador 2: ");
  preguntarJugador(c2);
  Serial.println("Puntos del jugador 2: " + toStr(c2));
}

void juego() {
  for (int ronda = 1;ronda <= rondas;ronda++) {
    Serial.println("Ronda: " + toStr(ronda));
    //Generar problema
    generarProblema();
    //Preguntar
    preguntar();
    displayScores();
  }
  //Decir ganador
  if (c1 == c2)
    Serial.println("Empate");
  else if (c1 > c2)
    Serial.println("Ha ganado el jugador 1");
  else
    Serial.println("Ha ganado el jugador 2");
  //Reiniciar contadores
  Serial.println("Jugador 1: " + toStr(c1) + " Jugador 2: " + toStr(c2));
  c1 = 0;
  c2 = 0;
}

void setup() {
  screen.init();
  screen.set(BRIGHT_TYPICAL);
  Serial.begin(9600);
  Serial.println("Juego matematico V1.0");
  randomSeed(analogRead(0));
  displayScores();
}

void loop() {
  configurar();
  Serial.println("Juego comenzado!!!");
  juego();
}

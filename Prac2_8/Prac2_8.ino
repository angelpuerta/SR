
#include <Keypad.h>

#define PIN_CLK 11
#define PIN_DIO 12

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
{'1','2','3','+'},
{'4','5','6','-'},
{'7','8','9','/'},
{'*','0','#','='}
};

byte pf1[nfilas] = {2, 3, 4, 5}; 
byte pc1[ncolumnas] = {A0, A1, A2, A3}; 

byte pf2[nfilas] = {6, 7, 8, 9}; 
byte pc2[ncolumnas] = {A4, A5, 10, 13}; 

Keypad t1 = Keypad(makeKeymap(teclas), pf1, pc1, nfilas, ncolumnas);
//TM1637 screen(PIN_CLK, PIN_DIO);

//Puntuación
int number1 = 0;
int number2 = 0;
char operation = '+';//por defecto sera suma

bool isNumber(char number){
  if(number == '0'|| number == '1'||number == '2'||
    number == '3'||number == '4'||number == '5'||
      number == '6'||number == '7'||number == '8'||
       number == '9'){
        return true;
      }
  else{
    return false;
  }
}
//Metodo para guardar los dos numeros y operar si se pulsa '=' 
void getOperators(){
  char actual = t1.getKey();
  if(isNumber(actual)){
    number1 = number1*10+actual;
     screen.set(number1);
  }else{
    if(actual == '='){
      operateNumber();
    }else{
    operation = actual;
    number2 = number1;
    number1 = 0;
     screen.set(number1);
    }
  }
}

//Metodo para operar como sea necesario
void operateNumbers(){
  if(operation == '+'){
    screen.set(number1+number2);
  }else if(operation == '-'){
    screen.set(number2-number1);
  }else if(operation == '*'){
    screen.set(number1*number2);
  }else if(operation == '/'){
    screen.set(number2/number1);
  }
  resetValues();
}

//Metodo para resetear los valores de serie despues de acabar una operacion
void resetValues(){
  number1 = 0;
  number2 = 0;
  operation = '+'; 
}

void setup() {
  screen.init();
  screen.set(BRIGHT_TYPICAL);
}

void loop() {
  getOperators();
}

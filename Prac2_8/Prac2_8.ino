#include <TM1637.h>
#include <Keypad.h>

#define PIN_CLK 10
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

Keypad t1 = Keypad(makeKeymap(teclas), pf1, pc1, nfilas, ncolumnas);
TM1637 screen(PIN_CLK, PIN_DIO);

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
bool isSymbol(char number){
  if(number == '+'|| number == '-'||number == '/'||
    number == '#'||number == '='){
        return true;
      }
  else{
    return false;
  }
}


//Metodo para operar como sea necesario
void operateNumbers(){
  if(operation == '+'){
   number1=number1+number2;
  }else if(operation == '-'){
    number1=number2-number1;
  }else if(operation == '*'){
    number1=number1*number2;
  }else if(operation == '/'){
    if(number1==0)
      number1 = 0;
    else
      number1=number2/number1;
  }
  screen.set(number1);
}

//Metodo para resetear los valores de serie despues de acabar una operacion
void resetValues(){
  number1 = 0;
  number2 = 0;
  operation = '+'; 
  screen.set(number1);
}

//Metodo para guardar los dos numeros y operar si se pulsa '=' 
void getOperators(){
  char actual = t1.getKey();
  Serial.println(actual);
  if(isNumber(actual)){
    number1 = number1*10+(actual-'0');
     screen.set(number1);
  }
   if(isSymbol(actual)){
    operation = actual;
    number2 = number1;
    number1 = 0;
    screen.set(number1);
    if(actual == '='){
      operateNumbers();
    }else if(actual == '#'){
      if(number1==0){
        resetValues();
      }else{
        number1 = number1/10;
     }
    }
}
}



void setup() {
  Serial.begin(9600);
  screen.init();
  screen.display(0, 0);
  screen.display(1, 0);
  screen.display(2, 0);
  screen.display(3, 0);
  screen.set(BRIGHT_TYPICAL);
  screen.set(0);
}

void loop() {
  Serial.println("Numero_1 :");
  Serial.println(number1);
  getOperators();
  delay(5);
}

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
    number == '#'||number == '=' || number == '*'){
        return true;
      }
  else{
    return false;
  }
}
bool isOperatingSymbol(char symbol){
    if(symbol == '+'|| symbol == '-'||symbol == '/' || symbol=='*'){
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
  
  updateScreen(number1);
  delay(250);
}

//Metodo para resetear los valores de serie despues de acabar una operacion
void resetValues(){
  number1 = 0;
  number2 = 0;
  operation = '+'; 
  screen.set(number1);
  screen.display(0, 0);
  screen.display(1, 0);
  screen.display(2, 0);
  screen.display(3, 0);
}

void updateScreen(int contador) {
 int digit0 =  contador/1000;
 int digit1 = (contador - digit0*1000)/100;
 int digit2 = (contador - (digit0*1000 + digit1*100))/10;
 int digit3 =  contador - (digit0*1000 + digit1*100 + digit2*10);

 screen.display(0, digit0);
 screen.display(1, digit1);
 screen.display(2, digit2);
 screen.display(3, digit3);
}

//Metodo para guardar los dos numeros y operar si se pulsa '=' 
void getOperators(){
  char actual = t1.getKey();
  Serial.println(actual);
  delay(250);
  if(isNumber(actual)){
    number1 = number1*10+(actual-'0');
     updateScreen(number1);
  }
   if(isSymbol(actual)){
    if(isOperatingSymbol(actual)){
    operation = actual;
    number2 = number1;
    number1 = 0;
    }else{
    if(actual == '='){
      operateNumbers();
    }else if(actual == '#'){
      if(number1==0){
        resetValues();
      }else{
        number1 = number1/10;
        updateScreen(number1);
     }
    }
    }
}
}



void setup() {
  Serial.begin(9600);
  screen.init();
  
  screen.set(BRIGHT_TYPICAL);
  delay(1000);
  resetValues();
  
}





void loop() {
  Serial.println(number1);
  getOperators();
  delay(5);
}

#include <Servo.h>

#define BTN_WAIT 2
#define LM 9
#define RM 11

#define UP 'S'
#define BACK 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define END 'E'

#define

String path = "";

Servo leftMotor;
Servo rightMotor;

//Maze analizing functions

char getSection() {
  return '?';
}

//Driving functions

void moveRobot(char nextMove) {
  switch (nextMove) {
      case UP:
      break;
      case BACK:
      break;
      case LEFT:
      break;
      case RIGHT:
      break;
      default:
        Serial.println("Unknown move: " + nextMove);
    }    
}

//Path function

void createPath() {
  bool endReached = false;
  char section;
  while(!endReached) {
    if ((section = getSection()) == END)
      endReached = true;
    else
      path += section;
  }
}

void simplifyPath() {
  Serial.println("Simplifing path");
  while (true) {
    int initialLength = path.length();
    //Replace
    path.replace("LBR","B");
    path.replace("LBS","R");
    path.replace("RBL","B");
    path.replace("SBL","R");
    path.replace("SBS","B");
    path.replace("LBL","S");
    if (initialLength == path.length())
      break;
  }
  Serial.println("Simplified path: " + path);
}

void usePath() {
  for (int i = 0;i < path.length();i++) {
    char nextMove = path[i];
    moveRobot(nextMove);
  }
}

//Auxiliar functions

void wait() {
  while (digitalRead(BTN_WAIT) != HIGH) 
    delay(5);  
}

void setup() {
  //Setup pins
  leftMotor.attach(LM);
  rightMotor.attach(RM);
  
  pinMode(BTN_WAIT , INPUT);
  //Setup serial
  Serial.begin(9600);
}

void loop() {
  //Solve it first to get the path
//  wait();
//  path = "";
//  createPath();
//  //Simplify path
//  simplifyPath();
//  //Solve using simplified path
//  wait();
//  usePath();
}

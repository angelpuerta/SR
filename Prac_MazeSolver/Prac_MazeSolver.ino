
#define BTN_WAIT 2

#define FORWARD 'S'
#define BACK 'B'
#define LEFT 'L'
#define RIGHT 'R'

String path = "";

//Maze analizing functions

char getSection() {
  return '?';
}

//Driving functions

void moveRobot(char nextMove) {
  switch (nextMove) {
      case FORWARD:
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
  
}

void simplifyPath() {
  for (int i = 0;i < path.length() - 3;i++) {
    String segment = path.substring(i, i + 3);

    }
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
  pinMode(BTN_WAIT , INPUT);
  //Setup serial
  Serial.begin(9600);
}

void loop() {
  //Solve it first to get the path
  wait();
  createPath();
  //Simplify path
  simplifyPath();
  //Solve using simplified path
  wait();
  usePath();
}

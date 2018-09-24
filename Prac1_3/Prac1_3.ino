
#define BTN_RED 3
#define BTN_GREEN 2

#define LED_RED 6
#define LED_GREEN 5

#define BZR 9

#define RED_TONE 100
#define GREEN_TONE 200

String sequence = "";

void addRandomSequence() {
  int r = random(1,3);
  sequence += r == 1 ? 'R' : 'V';
}

void resetGame() {
  sequence = ""; 
  for (int i = 0;i < 3;i++)
     addRandomSequence();
  Serial.println("Game reseted");
}

void playSequence() {
  for (int i = 0;i < sequence.length();i++) {
      char led = sequence[i];
      if (led == 'R') {
        digitalWrite(LED_RED, HIGH);
        tone(BZR, RED_TONE);
      } else if (led == 'V') {
        digitalWrite(LED_GREEN, HIGH);
        tone(BZR, GREEN_TONE);
      }
      delay(1000);
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      noTone(BZR);
      delay(100);
  }
}

void waitForInput() {
  while (!(digitalRead(BTN_RED) == HIGH || digitalRead(BTN_GREEN) == HIGH)) {
      delay(5);
    }  
}

char getColor() {
  if (digitalRead(BTN_RED) == HIGH) {
    digitalWrite(LED_RED, HIGH);
    tone(BZR, RED_TONE);
    delay(100);
    digitalWrite(LED_RED, LOW);
    noTone(BZR);
    return 'R'; 
  } else if (digitalRead(BTN_GREEN) == HIGH) {
    digitalWrite(LED_GREEN, HIGH);
    tone(BZR, GREEN_TONE);
    delay(100);
    digitalWrite(LED_GREEN, LOW);
    noTone(BZR);
    return 'V';
  }
  return '?';
}

bool testPlayer() {
  for (int i = 0;i < sequence.length();i++) {
    waitForInput();
    if (sequence[i] != getColor())
      return false;
    delay(200);
  }
  return true;
}

void setup() {
  //Set pins
  pinMode(BTN_RED, INPUT);
  pinMode(BTN_GREEN, INPUT);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  pinMode(BZR, OUTPUT);
  //Random seed
  randomSeed(analogRead(0));

  resetGame();
  Serial.begin(9600);
}

void loop() {
  Serial.println("Sequence: " + sequence);
  playSequence();
  delay(250);
  if (testPlayer())
    addRandomSequence();
  else
    resetGame();
  delay(250);
}


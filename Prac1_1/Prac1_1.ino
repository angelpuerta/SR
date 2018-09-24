#define BUTTON 3
#define LEDS 3
#define LED_INIT 4

void setLeds(int n) {
  for (int i = 0; i < n; i++)
    digitalWrite(LED_INIT + i, HIGH);
  for (int i = n; i < LEDS; i++)
    digitalWrite(LED_INIT + i, LOW);
}

void setup() {
  //Set pins
  pinMode(BUTTON, INPUT);
  for (int i = 0; i < LEDS; i++)
    pinMode(LED_INIT + i, OUTPUT);
  //Random seed
  randomSeed(analogRead(0));

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    int r = random(1, LEDS + 1);
    setLeds(r);
    Serial.println(r);
  }
  delay(250);
}

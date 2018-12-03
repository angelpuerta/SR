#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
#include "HttpClient.h"

#define SERVER "http://api.thingspeak.com"

#define CH_ID 631578
#define APIKEY "DBV1E89SPIA2JH3I"

#define TALKBACK_API "9FRGDZL1QJW750QH"
#define TALKBACK_ID "29332"

#define SENSOR_PIN A0
#define LED_PIN 2

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

IPAddress dnsServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(192, 168, 61, 204);

EthernetClient client;

void checkTalkBack()
{
  String talkBackCommand;
  char charIn;
  
  if (client.connect(SERVER, 80)) {
    Serial.println("connected");
    // Make your API request:
    client.println("GET /talkbacks/29332/commands/execute?api_key=9FRGDZL1QJW750QH");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Comando: "); 
  while (client.available()) {
    charIn = client.read();
    talkBackCommand += charIn;
    Serial.print(charIn);
  }
  Serial.println();
  
  // Turn On/Off the On-board LED
  if (talkBackCommand == "ON")
  {  
    digitalWrite(LED_PIN, HIGH);
  }
  else if (talkBackCommand == "OFF")
  {      
    digitalWrite(LED_PIN, LOW);
  }
  
  Serial.flush(); 
}

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);  //Initialize serial
  Serial.println("Initializing Ethernet...");
  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  Serial.print("IP Local: "); 
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Serial.println("Set up completed!"); 
}

void loop() {
  int val = analogRead(SENSOR_PIN);
  int x = ThingSpeak.writeField(CH_ID, 1, val, APIKEY);
  if(x == 200){
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  checkTalkBack();
  delay(5000); // Wait 10 seconds to update the channel again
}


#include <Time.h>
#include <Ethernet.h> //Importamos librería Ethernet
#include <SPI.h> 
#include <ArduinoJson.h>
#define JSON_BUFFER_SIZE 80


#define PIN_STOP 11
#define tonePin 3

#define OPEN 0
#define CLOSE 1 
#define OPEN_FOR_A_WHILE 2


#define WAITING_TIME 10000

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(192, 168, 56 , 1);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(192, 168, 61, 22);

int leds[] = {3,4,5};
int estado = 0;
boolean muted = false;
long actual = 0;
long wait_time = WAITING_TIME;

void setup() {
  Serial.begin(9600);
  for (int i; i<i++;){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(tonePin,OUTPUT);
  pinMode(PIN_STOP, INPUT);
  
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  servidor.begin();
  Serial.println("Setup...");
     Serial.print("IP Local: "); 
   Serial.println(Ethernet.localIP());
   
  
  Serial.println("Servidor iniciado");

}

void sound(){
  Serial.println("Sound");
  analogWrite(tonePin,442);
  delay(250);     
  analogWrite(tonePin,442);
  delay(250);
  analogWrite(tonePin,0);

}

void doorLoop(){  
 if(digitalRead(PIN_STOP) == LOW){
   Serial.println("Pressed");
  if(estado == CLOSE){
    estado = OPEN;
    actual = millis();
    }
  if(millis()-actual >= wait_time){
      estado = OPEN_FOR_A_WHILE;
      if(!muted)
        sound();
  }
  }
  else{
    estado = CLOSE;
  }
  delay(5);
}

void mandarJSON(EthernetClient cliente) {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  String sensor_status = "";
    switch(estado){
      case OPEN:
        sensor_status = "OPEN";
        break;
      case CLOSE:
        sensor_status = "CLOSE";
        break;  
      case OPEN_FOR_A_WHILE:
        sensor_status = "OPEN_FOR_A_WHILE";
        break;  
    }
    root["sensor_status"] = sensor_status;
    root["muted"] = muted;
    root["wait_time"] = wait_time;
    //Mandar headers y mandar
    cliente.println("HTTP/1.0 200 OK");
    cliente.println("Access-Control-Allow-Origin: *");
    cliente.println("Content-Type: application/json");
    cliente.println();
    root.prettyPrintTo(cliente);
}

void OKConection(EthernetClient cliente){
cliente.println("HTTP/1.1 200 OK");
cliente.println("Connection: close");
cliente.println();
}

int calculateWaitingTime(String waitingTime){
  int indexOfSlash = waitingTime.indexOf('/');
  if(indexOfSlash == -1)
    return -1;
  String petition = waitingTime.substring(indexOfSlash+1);
  int start_petition = petition.indexOf('/');
  int end_petition = petition.indexOf(' ');
  if(start_petition == -1 || end_petition == -1)
    return -1;  
  String digit = petition.substring(start_petition+1, end_petition);
  int future_time = digit.toInt();
  Serial.println("Tiempo cambiado a ");
  Serial.println(future_time);
  return future_time;
}

void serverLoop(){
 EthernetClient cliente = servidor.available();
 doorLoop();
 if (cliente) {
     Serial.println("Nueva peticion");
     String peticion="";
     while (cliente.connected()) {
       if (cliente.available()) {
         char c = cliente.read(); //Leer petición carácter a carácter
         peticion.concat(c); // concatenar en un string
         // Ha acabado la peticion http
         if (c == '\n'){
           Serial.println("Responder");
           // contiene la cadena "sensor"
           Serial.println();
           if(peticion.indexOf("sensor") != -1){
            
              mandarJSON(cliente);
           }
           else if(peticion.indexOf("mute") != -1){
             Serial.println(peticion);
              muted = !muted;
              mandarJSON(cliente);
           }
           else if(peticion.indexOf("changeTime") != -1){
               Serial.println(peticion);
               wait_time = calculateWaitingTime(peticion); 
               mandarJSON(cliente);    
           }
           break;
         }
       }
       }
       // Pequeña pausa para asegurar el envio de datos
       delay(500);
       Serial.println("Estado :");
       Serial.println(estado);
       Serial.println("waiting_time :");
       Serial.println(wait_time);
       Serial.println("Muted :");
       Serial.println(muted);
     cliente.stop();// Cierra la conexión 
}}

void loop() {
  serverLoop();
}
  

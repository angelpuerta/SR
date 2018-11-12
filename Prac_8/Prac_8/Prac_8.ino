#include <Time.h>
#include <Ethernet.h> //Importamos librería Ethernet
#define JSON_BUFFER_SIZE 80


#define PIN_STOP 11
#define tonePin 12

#define OPEN 0
#define CLOSE 1 
#define OPEN_FOR_A_WHILE 2


#define WAITING_TIME 3000

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(192, 168, 61, 204);

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
  Serial.println("IP Local: " + Ethernet.localIP());

  Serial.println("Servidor iniciado");


}

void sound(){
  analogWrite(tonePin,442);
  delay(250);     
  analogWrite(tonePin,442);
  delay(250);
}

void doorLoop(){  
 if(digitalRead(PIN_STOP) == HIGH){
  if(estado == CLOSE){
    estado = OPEN;
    actual = millis();
    }
  if(millis()-actual> wait_time){
      estado = OPEN_FOR_A_WHILE;
      if(!muted)
        sound();
  }
  }
  else{
    estado = CLOSE;
  }
}

void mandarJSON(EthernetClient cliente) {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  String sensor_status = "";
    switch(estado){
      case OPEN:
        estado = "OPEN";
        break;
      case CLOSE:
        estado = "CLOSE";
        break;  
      case OPEN_FOR_A_WHILE:
        estado = "OPEN_FOR_A_WHILE";
        break;  
    }
    root["sensor_status"] = sensor_status;
    //Mandar headers y mandar
    cliente.println("HTTP/1.0 200 OK");
    cliente.println("Content-Type: application/json");
    cliente.println("Connection: close");
    cliente.println();
    root.prettyPrintTo(cliente);
  } else { //Error
    cliente.println("HTTP/1.0 503 OK Service Temporarily Unavailable");
    cliente.println("Connection: close");
    cliente.println();
  }
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
  String digit = waitingTime.substring(indexOfSlash);
  int future_time = atoi(digit);
  Serial.println("Tiempo cambiado a"+future_time);
  return futre_time;
}

void loop() {
 EthernetClient cliente = servidor.available();
 if (cliente) {
     Serial.println("Nueva peticion");
     String peticion="";
     while (cliente.connected()) {
       if (cliente.available()) {
         doorLoop();
         char c = cliente.read(); //Leer petición carácter a carácter
         peticion.concat(c); // concatenar en un string
         // Ha acabado la peticion http
         if (c == '\n'){
           Serial.println("Responder");
           // contiene la cadena "sensor"
           if(peticion.indexOf("sensor") != -1){
              mandarJSON(cliente);
           else if(peticion.indexOf("muted") != -1){
              muted = !muted;
              OKConection(cliente);
           else if(petiticion.indexOf("changeTime") != -1){
               waiting_time = calculateWaitingTime(peticion); 
               OKConection(cliente);    
           }
           break;
         }
       }
       // Pequeña pausa para asegurar el envio de datos
     delay(1000);
     cliente.stop();// Cierra la conexión
 }
  

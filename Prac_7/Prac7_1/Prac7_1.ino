#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>
#include <Ethernet.h> //Importamos librería Ethernet

#define JSON_BUFFER_SIZE 80
#define LED_PIN 9

#define SENSOR_PIN 5

#define DHT_OK 0
#define DHT_ERROR_TEMP 1
#define DHT_ERROR_HUM  2

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(192, 168, 61, 204);

DHT_Unified dht(SENSOR_PIN, DHT11);

//Control del led

bool ledState = false;

void apagar() {
  Serial.println("Apagar led");
  ledState = false;
  digitalWrite(LED_PIN,LOW);
}

void encender() {
  Serial.println("Encender Led");
  ledState = true;
  digitalWrite(LED_PIN,HIGH);
}

int readValsFromDHT(float &hum, float &temp) {
    sensors_event_t event; 
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) 
      return DHT_ERROR_TEMP;
    else
      temp = event.temperature;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) 
      return DHT_ERROR_HUM;
    else
      temp = event.relative_humidity;
    return DHT_OK;
}

void mandarJSON(EthernetClient cliente) {
  Serial.println("Mandando info de los sensores"); 
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  //Conseguir datos
  float temp, hum;
  if (readValsFromDHT(hum, temp) == DHT_OK) { //Todo correcto
    root["temperatura"] = temp;
    root["humedad"] = hum;
    root["led"] = ledState;
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

void setup() {
   Serial.begin(9600);
   Ethernet.begin(mac, ip, dnServer, gateway, subnet);
   servidor.begin();
   Serial.println("Setup...");
   // Imprimir la IP
   Serial.println("IP Local: " + Ethernet.localIP());
   // Inicializar el led
   pinMode(LED_PIN,OUTPUT);
   apagar();
   Serial.println("Servidor iniciado");
}

void loop(){
   EthernetClient cliente = servidor.available();
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
           // contiene la cadena "encender"
           if(peticion.indexOf("sensor") != -1){
              mandarJSON(cliente);
           } else if(peticion.indexOf("ledOn") != -1){
              encender();
              cliente.println("HTTP/1.1 200 OK");
              cliente.println("Connection: close");
              cliente.println();
           } else if(peticion.indexOf("ledOff") != -1){
              apagar();
              cliente.println("HTTP/1.1 200 OK");
              cliente.println("Connection: close");
              cliente.println();
           }
           break;
         }
       }
     }
    
     // Pequeña pausa para asegurar el envio de datos
     delay(1000);
     cliente.stop();// Cierra la conexión
   }
}


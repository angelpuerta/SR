#include <ArduinoJson.h>
#include <Ethernet.h> //Importamos librería Ethernet

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(192, 168, 61, 204);

//Control del led

void apagar() {
  Serial.println("Apagar led");
  digitalWrite(led,LOW);
}

void encender() {
  Serial.println("Encender Led");
  digitalWrite(led,HIGH);
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
   encender();
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
         // Si contiene index responder con una web
         // la petición ha acabado '\n' y contiene la cadena "index"
         if (c == '\n' && peticion.indexOf("index") != -1){
           Serial.println("Responder");
           // Serial.println(peticion);
          
           // contiene la cadena "encender"
           if(peticion.indexOf("encender") != -1){
              encender();
           }else if(peticion.indexOf("apagar") != -1){
              apagar();           
           }
          
           // Enviamos al cliente una respuesta HTTP
           cliente.println("HTTP/1.1 200 OK");
           cliente.println("Content-Type: text/html");
           cliente.println("Access-Control-Allow-Origin: *");
           cliente.println();
           break;
         }
       }
     }
    
     // Pequeña pausa para asegurar el envio de datos
     delay(1000);
     cliente.stop();// Cierra la conexión
   }
}


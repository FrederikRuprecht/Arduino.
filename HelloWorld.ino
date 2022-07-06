#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
ESP8266WebServer server(80);
 
const char* ssid = "PDV Guest"; 
const char* password = "mx'gyr!Yqm"; 
 
const char* dns_name = "123";
 
void eigeneFunktion();
 
void setup()
{
  Serial.begin(9600);
  Serial.println("ESP Gestartet");
 
  WiFi.begin(ssid, password);
 
  Serial.print("Verbindung wird hergestellt ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 
  Serial.print("Verbunden! IP-Adresse: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin(dns_name)) {
    Serial.println("DNS gestartet, erreichbar unter: ");
    Serial.println("http://" + String(dns_name) + ".local/");
  }
 
  server.onNotFound([](){
    server.send(404, "text/plain", "Link wurde nicht gefunden!");  
  });
 
  server.on("/", []() {
    server.send(200, "text/plain", "HEllo World");
  });
 
  server.on("/Beispiel", []() {
    server.send(200, "text/plain", "Nur eine Beispiel");
    eigeneFunktion();
  });
 
  server.begin();
  Serial.println("Webserver gestartet.");
}
 
void loop() {
  server.handleClient();  
  MDNS.update();
}
 
void eigeneFunktion()
  Serial.println("Beispiel Ausgeführt");
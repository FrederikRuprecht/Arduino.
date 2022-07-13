#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define temPin 2

OneWire oneWire(temPin); 

DallasTemperature sensors(&oneWire);

const char* ssid = "PDV Guest";
const char* password = "mx'gyr!Yqm";

ESP8266WebServer server(80);

void indexHTML() {    
  server.send(200, "text/html", 
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"<title>Temperaturmessung</title>\n"
"<meta http-equiv='content-type' content='text/html'; charset='utf-8'>\n"
"<style>\n"
"body { background-color: #444343; font-size: 50px; font-family: Arial, Helvetica, Sans-Serif; color: #e0e0e0;margin-left: 40px; }\n"
"h1 { color: #2db0d7; margin-top: 50px; margin-bottom: 50px; }\n"
"#temp { width: 230px; height: 80px; border: 5px solid #2db0d7; text-align:center; padding: 1px; color: #2a089a; background-color: #000000; font-size: 60px; }\n"
"</style>\n"
"</head>\n"
"<body>\n"
"<h1>Temperaturmessung</h1>\n"
"<table bgcolor=\"#2db0d7\">\n"
"    <tr align=\"center\">\n"
"        <th width=\"350\">Aktuelle Temperatur:&nbsp;</th>\n"
"        <th width=\"350\">Maximale Temperatur:</th>\n"
"        <th width=\"350\">Minimale Temperatur:</th>\n"
"        <th width=\"350\">Durchschnitt</th>\n"
"    </tr>\n"
"    <tr align=\"center\">\n"
"        <td id='temp'><span id='TempWert1'>-</span>°C</td>\n"
"        <td id='temp'><span id='TempWert2'>-</span>°C</td>\n"
"        <td id='temp'><span id='TempWert3'>-</span>°C</td>\n"
"        <td id='temp'><span id='TempWert4'>-</span>°C</td>\n"
"    </tr>\n"
"</table>\n"
"<script>\n"
"  var t = 40\n"
"setInterval(function() {t = t+1\n"
"  getData();\n"
" }, 1);\n"
"function getData() {\n"
"  var value = t % 40 \n"
"  var xhttp = new XMLHttpRequest();\n"
"  xhttp.onreadystatechange = function() {\n"
"    if (this.readyState == 4 && this.status == 200 && value <= 10) {\n"
"      document.getElementById('TempWert1').innerHTML = this.responseText;\n"
"    }\n"
"    else if (this.readyState == 4 && this.status == 200 && value - 10 <=10) {\n"
"      document.getElementById('TempWert2').innerHTML = this.responseText;\n"
"    }\n"
"    else if (this.readyState == 4 && this.status == 200 && value - 20 <= 10) {\n"
"      document.getElementById('TempWert3').innerHTML = this.responseText;\n"
"    }\n"
"    else if (this.readyState == 4 && this.status == 200 && value > 30) {\n"
"      document.getElementById('TempWert4').innerHTML = this.responseText;\n"
"    }\n"
"  };\n"
"  xhttp.open('GET', 'TempWeb', true);\n"
"  xhttp.send();\n"
"}\n"
"</script>\n"
"</body>\n"
"</html>"
  );
}

void TempMessung() {
  sensors.requestTemperatures();
  String TempWert_1 = String(sensors.getTempCByIndex(0),1);
  //String TempWert_2 = String(4.4,1);
 // String TempWert_3 = String(4.6,1);
//  String TempWert_4 = String(4.7,1);
    server.send(200, "text/plane", TempWert_1);
/*  for (int i = 0; i<=3000; i++){
    server.send(200, "text/plane", TempWert_1);
    delay(1);
  }
  for (int i = 0; i<=3000; i++){
    server.send(200, "text/plane", TempWert_1);
    delay(1);
  }
  for (int i = 0; i<=3000; i++){
    server.send(200, "text/plane", TempWert_1);
    delay(1);
  }*/
  

}

void setup(void){
  sensors.begin();
  Serial.begin(9600);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Verbunden mit ");
  Serial.println(ssid);
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", indexHTML);
  server.on("/TempWeb", TempMessung);

  server.begin(); 
  Serial.println("Webserver ist gestartet");
}

void loop(void){
  server.handleClient();
}
#include <OneWire.h>
#include <DallasTemperature.h>


#define temPin 2

OneWire oneWire(temPin); 

DallasTemperature sensors(&oneWire);
 
 class TempMessung
{  
  public: 
float durchschnitt(int AnzMessung)
{
  float sum = 0;
  for (int x = 0; x <AnzMessung; ++x)
  {
  sensors.requestTemperatures();
  sum += sensors.getTempCByIndex(0);
  delay(1);
  }
  float Ave = sum / AnzMessung;
  return Ave;
}

float maxWert (int AnzMessung)
 {
  float y = 0;
  for (int x = 0; x<AnzMessung; ++x)
  {
  sensors.requestTemperatures();
  float z = sensors.getTempCByIndex(0);
  y = max(y,z);
  delay(1);}
  return y;
 }

float minWert (int AnzMessung)
 {
  sensors.requestTemperatures();
  float y = sensors.getTempCByIndex(0);
  for (int x = 0; x<AnzMessung; ++x)
  {
  sensors.requestTemperatures();
  float z = sensors.getTempCByIndex(0);
  y = min(y,z);
  delay(1);}
  return y;
 }
};
TempMessung A1;

void setup()
{
  Serial.begin(9600);
  sensors.begin();
         
}
  
void loop() 
{
int AnzahlMessung = 100;


sensors.requestTemperatures();
Serial.print("Erste Messung: ");
Serial.println(sensors.getTempCByIndex(0));

Serial.print("Gerundete Messung aus ");
Serial.print(AnzahlMessung);
Serial.print(" Messungen: ");
Serial.println(A1.durchschnitt(AnzahlMessung));

Serial.print("Höchste Messung aus ");
Serial.print(AnzahlMessung);
Serial.print(" Messungen: ");
Serial.println(A1.maxWert(AnzahlMessung));

Serial.print("Niedrigste Messung aus ");
Serial.print(AnzahlMessung);
Serial.print(" Messungen: ");
Serial.println(A1.minWert(AnzahlMessung));
}
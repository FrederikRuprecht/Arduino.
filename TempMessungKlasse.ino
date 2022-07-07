#include <OneWire.h>
#include <DallasTemperature.h>

#define temPin 2

OneWire oneWire(temPin); 

DallasTemperature sensors(&oneWire);


 class TempMessung 
{  
  private: 
float Durchschnitt(int AnzMessung)
 {
  sensors.requestTemperatures();
for (int x = 0; x < AnzMessung; x++)
  {
    float Wert1 = sensors.getTempCByIndex(0);
    int Sum = 0;
    Sum += Wert1;
  }
 }

float MaxWert(int AnzMessung)
 {
  sensors.requestTemperatures();
 for (int y = 0; y < AnzMessung; y++)
  {
    float Wert2 = sensors.getTempCByIndex(0);
  int maxWert[AnzMessung];
  maxWert[y] = Wert2;
  }
 }

float MinWert(int AnzMessung)
 {
  sensors.requestTemperatures();
 for (int z = 0; z < AnzMessung; z++)
  {
    float Wert3 = sensors.getTempCByIndex(0);
  int minWert[AnzMessung];
  minWert[z] = Wert3;
  }
 }
public:
  float Ave (float Sum, int AnzMessung){
    return(Sum / AnzMessung);
  }
  float Max (int maxWert){
    return(max(maxWert));
  }
  float Min (int minWert){
  return(min(minWert));
  }
};

void setup()
{
  Serial.begin(9600);
  int AnzMessung = 10;
  sensors.begin();       
  

}
void loop()
{
  return maxWert[];

  Serial.println("Maximaler Wert: " +  Max);
  Serial.println("Maximaler Wert: " +  Min);
  Serial.println("Durchschnittlicher Wert: " + Ave);
  delay(500);
}
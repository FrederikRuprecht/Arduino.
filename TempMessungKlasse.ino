#include <OneWire.h>          
#include <DallasTemperature.h>
#define temPin 2

float x=0;
float c=1000;
float y=0;
int v=0;
float b=0;

OneWire oneWire(temPin); 

DallasTemperature sensors(&oneWire);

class TemperaturMessung
{
 public:
        float Max_Wert(float Messwert)
        { 
          float y=Messwert;
          x=max(x,y);
          return x;
        }

         float Min_Wert(float Messwert)
        { 
          float y=Messwert;
          c=min(c,y);
          return c;
        }

        float Durchschnitt(float Messung, int Anzahl){
          y = Messung;
          float average= y/Anzahl;
          return average;
        }

        void addSample(float Sample){
          y=Sample;
        }

};

TemperaturMessung A1;
void setup()
{
  Serial.begin(9600);
  sensors.begin();
}

void loop() 
{
  v++;
  sensors.requestTemperatures();
  float y = sensors.getTempCByIndex(0);
  b+=y;
  Serial.println("Maximaler Wert");
  Serial.println(A1.Max_Wert(y));
  
  Serial.println("Minimaler Wert");
  Serial.println(A1.Min_Wert(y));
  
  Serial.println("Durchschnittlicher Wert");
  Serial.println(A1.Durchschnitt(b,v));
  Serial.println(" ");

  A1.addSample(35.32);

  if (Serial.available())
  {
    char data = Serial.read();
    if (data == 'o')
    {
      x=0;
      c=1000;
      b=0;
      v=0;
      Serial.println("Resetted");
    }
    else{
      Serial.println("Not Resetted");
    }
  }
}

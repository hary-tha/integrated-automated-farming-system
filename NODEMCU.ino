#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11 D2
#define LDRpin A0
int LDRValue = 0;
char ssid []= "MUHSIN";
char pass[] = "muhsin@92";
char auth[]= "Jr8UYyjaPdPly-Fxkq_aXaFwoGZQuT0G";
String a,temp;
int c;
int x,y,i;
String str;

void setup()
{
 Serial.begin(9600);
 Blynk.begin(auth,ssid,pass, "blynk.cloud", 80);
}

void loop()
{
  int p;
  Blynk.run();
  DHT.read(DHT11);
  Blynk.virtualWrite(V0,DHT.temperature);
  Blynk.virtualWrite(V1,DHT.humidity);
  if (Serial.available() > 0)
    {
      a= Serial.readStringUntil('#');
      if (a[0] == 'Y')
      {
      
      i = 1;
      temp = "";
      while (a[i] != '\0')
      {
      temp = temp + a[i];
      i++;
      }
      Serial.print("Y = ");
      Serial.println(temp);
      c=temp.toInt();
      Blynk.virtualWrite(V6,temp);
      if(c>0&&c<=6)
      {
        Blynk.virtualWrite(V3,"acidic");
      }
      if( c==7)
      {
        Blynk.virtualWrite(V3,"nuetral");
      }
      if(c>7&&c<14)
      {
        Blynk.virtualWrite(V3,"Basic");
      }
    }

     if (a[0] == 'X')
    {
      i = 1;
      temp = "";
      while (a[i] != '\0')
      {
        temp = temp + a[i];
        i++;
      }
      Serial.print("X = ");
      Serial.println(temp);
      Blynk.virtualWrite(V2,temp);
    }
    }
 /////////////////////////////////////////////////////////////////
  LDRValue = analogRead(LDRpin); // reading from LDR sensor
  if(LDRValue>=800)
  {
   Blynk.virtualWrite(V4,"sunny");
  }
  else if(LDRValue>600&&LDRValue<800)
  {
   Blynk.virtualWrite(V4,"normal");
  }
  else
  {
   Blynk.virtualWrite(V4,"too darkk");
  }    
}

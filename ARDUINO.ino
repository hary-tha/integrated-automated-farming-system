#include<SoftwareSerial.h>
SoftwareSerial mySerial(8,9);
#define sensorPin A7
#define pH_value A5
#define LS 8      // left sensor
#define RS 7      // right sensor
#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define relay 6
#include<Servo.h>
Servo pest;
#define soildry 50
uint8_t count=0;
bool flag=false;
String str;
int moisture_percentage;
int p, p1;
void setup()

{
  pest.attach(11);
  pest.write(0);
  pinMode(relay,OUTPUT);
  pinMode(pH_value, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
pinMode(12,INPUT_PULLUP);
pinMode(sensorPin, INPUT);
digitalWrite(relay,HIGH);
  Serial.begin(9600);
  mySerial.begin(9600);
 
}


void loop()
{
  if(!digitalRead(12))
  {
    flag=true;
  }
  if(flag==true)
   {
    digitalWrite(LM1, 1);
    digitalWrite(LM2, 0);
    digitalWrite(RM1, 1);
    digitalWrite(RM2, 0);
    delay(1500);
    do{
    
      if(!digitalRead(LS) && !digitalRead(RS))     // Move Forward
      {
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
      }
      if((digitalRead(LS)) && !(digitalRead(RS)))     // Turn right
      {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
       }
       if(!(digitalRead(LS)) && digitalRead(RS))     // turn left
       {          
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
       }    
      if((digitalRead(LS)) && (digitalRead(RS)))     // stop
       {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        }
        }while(!(digitalRead(LS) == 1 && digitalRead(RS) == 1));
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        
         ////////////////////////////////////
          delay(5000);
    int val = analogRead(sensorPin);  
    moisture_percentage = ( 100 - ( (val/1023.00) * 100 ) );

   if (moisture_percentage < soildry)
    {
  
      delay(1000);
      digitalWrite(relay,LOW);
      delay(2000);
      digitalWrite(relay,HIGH);
    }
    else
   
    {
        delay(1000);
        digitalWrite(relay,HIGH);
    }
 
 /////////////////////////SOIL PH//////////////////////
p = analogRead(A5);
Serial.print("Y");
Serial.print(p);
Serial.print("#");
if (p < 500)
{
  if (p > 120 && p < 140) //acidic
  {
  p1 = map(p, 120, 140, 6, 0);
  }
  if (p > 140 && p < 190) //basic
  {
  p1 = map(p, 140, 190, 14, 8);
  }
  if (p > 190 && p < 200)//normal
  {
  p1 = map(p, 190, 200, 7, 7);
  }
}
else
{
 p= 501;
}
Serial.print("X");
Serial.print(p1);
Serial.print("#");

////////////////////////////////
Serial.println("A");
delay(500);
while(!Serial.available()>0);

str =Serial.readStringUntil('#');
if(str[0]=='B')
{
pest.write(90);
delay(2000);
pest.write(0);
}
count++;
}
if(count>2)
{
flag=false;
}
if(count>0&&flag==false)
{

count--;
digitalWrite(LM1, LOW);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
delay(1500);
do{
  if(!digitalRead(LS) && !digitalRead(RS))     // Move Forward
  {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  }
  if((digitalRead(LS)) && !(digitalRead(RS)))     // Turn right
  {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  }
  if(!(digitalRead(LS)) && digitalRead(RS))     // turn left
  {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  }
  if((digitalRead(LS)) && (digitalRead(RS)))     // stop
  {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  }
  }while(!(digitalRead(LS) == 1 && digitalRead(RS) == 1));
  delay(1000);
  }
}

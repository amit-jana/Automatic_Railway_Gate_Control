#include <EEPROM.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;

int pos = 0;
int Sensor1 = A0;
int Sensor2 = A1;
int Sensor3 = A2;
int Sensor4 = A3;

int RedLED = 7;
int GreenLED = 8;

int Buzzer = 13;

const long interval = 1000;

void setup() {

  myservo1.attach(5);
  myservo2.attach(6);

  pinMode(Sensor1,INPUT);
  pinMode(Sensor2,INPUT);
  pinMode(Sensor3,INPUT);
  pinMode(Sensor4,INPUT);

  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);

  pinMode(Buzzer,OUTPUT);

  EEPROM.write(0, 0);
  EEPROM.write(1, 0);
}

void loop() {

unsigned long currentMillis = millis();
  
  if (EEPROM.read(1)==0 || EEPROM.read(0)==0){

    while (analogRead(Sensor1)>500){
      if (analogRead(Sensor2)>500){
        if (EEPROM.read(1)!=1){ EEPROM.write(1, 1);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);} 
              
        }}

    while (analogRead(Sensor3)>500){
      if (analogRead(Sensor4)>500){
        if (EEPROM.read(1)!=1){ EEPROM.write(1, 1);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);} 

        }}   
  }

  if (EEPROM.read(1)==1 || EEPROM.read(0)==0){

    while (analogRead(Sensor2)>500){
      if (analogRead(Sensor1)>500){
        if (EEPROM.read(1)!=0){ EEPROM.write(1, 0);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);}
        
        }}

    while (analogRead(Sensor4)>500){
      if (analogRead(Sensor3)>500){
        if (EEPROM.read(1)!=0){ EEPROM.write(1, 0);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);}

        }}   
  }

  if (EEPROM.read(1)==1){ //Gate open
    if (pos != 125){
      for (pos = 25; pos < 125; pos += 1){
      myservo1.write(pos);
      myservo2.write(pos);

      digitalWrite(Buzzer,HIGH);
      digitalWrite(GreenLED, HIGH);
      delay(10);
      digitalWrite(Buzzer,LOW);
      digitalWrite(RedLED, LOW);
      
    }}
    
    digitalWrite(Buzzer,LOW);
    if (EEPROM.read(0)!=0)  {EEPROM.write(0, 0);}
  }
   
  if (EEPROM.read(1)==0){ //Gate close 
    if (pos != 25){
     for (pos = 125; pos > 25; pos -= 1){
         myservo1.write(pos);
         myservo2.write(pos);
         digitalWrite(Buzzer,HIGH);
         digitalWrite(RedLED, HIGH);
         delay(10);
         digitalWrite(Buzzer,LOW);
         digitalWrite(GreenLED, LOW);

    }}
    
    //Serial.println("Gate Closed");    
    if (EEPROM.read(0)!=0)  {EEPROM.write(0, 0); Serial.println("OK");}
  }  


}

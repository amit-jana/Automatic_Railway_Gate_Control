#include <EEPROM.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;

int pos = 0;
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;

int RLED = 7;
int GLED = 8;

int buzzer = 13;

const long interval = 1000;

void setup() {
  //Serial.begin(9600);

  myservo1.attach(5);
  myservo2.attach(6);

  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);

  pinMode(buzzer,OUTPUT);

  EEPROM.write(0, 0);
  EEPROM.write(1, 0);
}

void loop() {

unsigned long currentMillis = millis();
  
  if (EEPROM.read(1)==0 || EEPROM.read(0)==0){

    while (analogRead(sensor1)>500){
      if (analogRead(sensor2)>500){
        if (EEPROM.read(1)!=1){ EEPROM.write(1, 1);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);} 
        
       // Serial.println("X");
        //delay(100);       
        }}

    while (analogRead(sensor3)>500){
      if (analogRead(sensor4)>500){
        if (EEPROM.read(1)!=1){ EEPROM.write(1, 1);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);} 
       // Serial.println("Y");
        //delay(100); 
        }}   
  }

  if (EEPROM.read(1)==1 || EEPROM.read(0)==0){

    while (analogRead(sensor2)>500){
      if (analogRead(sensor1)>500){
        if (EEPROM.read(1)!=0){ EEPROM.write(1, 0);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);}
        
        //Serial.println("Z"); 
        //delay(100);
        }}

    while (analogRead(sensor4)>500){
      if (analogRead(sensor3)>500){
        if (EEPROM.read(1)!=0){ EEPROM.write(1, 0);}
        if (EEPROM.read(0)!=1){ EEPROM.write(0, 1);}
        //Serial.println("A"); 
        //delay(100);
        }}   
  }

  if (EEPROM.read(1)==1){     //Gate open
    if (pos != 125){
      for (pos = 25; pos < 125; pos += 1){
      myservo1.write(pos);
      myservo2.write(pos);
     // Serial.println(pos);
      digitalWrite(buzzer,HIGH);
      digitalWrite(GLED, HIGH);
      delay(10);
      digitalWrite(buzzer,LOW);
      digitalWrite(RLED, LOW);
      //delay(10);
    }}
    
    //Serial.println("Gate Opend");
    digitalWrite(buzzer,LOW);
    if (EEPROM.read(0)!=0)  {EEPROM.write(0, 0);  /*Serial.println("OK");*/}
  }
   
  if (EEPROM.read(1)==0){     //Gate close 
    if (pos != 25){
     for (pos = 125; pos > 25; pos -= 1){
         myservo1.write(pos);
         myservo2.write(pos);
         digitalWrite(buzzer,HIGH);
         digitalWrite(RLED, HIGH);
         delay(10);
         digitalWrite(buzzer,LOW);
         digitalWrite(GLED, LOW);
         //delay(10);
    }}
    
    //Serial.println("Gate Closed");    
    if (EEPROM.read(0)!=0)  {EEPROM.write(0, 0); Serial.println("OK");}
  }  


}

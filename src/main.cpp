#include <Arduino.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(10, 11);


#define echoPin1 2
#define trigPin1 3
#define echoPin2 4
#define trigPin2 5
#define echoPin3 6
#define trigPin3 7    


void setup() {

  pinMode(echoPin1,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin3,INPUT);
  pinMode(trigPin3,OUTPUT);

  pinMode(7,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);

  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  nodemcu.begin(9600);

  delay(100);
}

long getDistance(int echo, int trigger){
  
      digitalWrite(trigger, LOW);
      delayMicroseconds(2);
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);
      long duration1 = pulseIn(echo, HIGH);
      return duration1 * 0.034 / 2;

}

void loop() {

    //Starting UNO to MCU
    StaticJsonDocument<128> doc;
    doc[0] = getDistance(echoPin1,trigPin1);
    doc[1] = getDistance(echoPin2,trigPin2);
    doc[2] = getDistance(echoPin3,trigPin3);
     //Send data to NodeMCU
     serializeJson(doc, nodemcu);
     delay(100);


}



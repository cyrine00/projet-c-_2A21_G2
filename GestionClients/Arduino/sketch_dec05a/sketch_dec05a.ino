#include <Servo.h>

#include <Servo.h>

Servo tap_servo;

int sensor_pin = 4;
int tap_servo_pin =5;
int data;
char data1;
const int buzzer = 13;
int led = 12; 

void setup(){
  pinMode(sensor_pin,INPUT);
  tap_servo.attach(tap_servo_pin);
   Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
    pinMode(led, OUTPUT);

}

void loop(){
 //if(Serial.available())
 //{
data1=Serial.read();
  data = digitalRead(sensor_pin);
  if (data==0)
  {tap_servo.write(0);
     digitalWrite(buzzer,HIGH); 
           digitalWrite(led, HIGH);
             delay(1000);                     
           tone(buzzer,1000);
  digitalWrite(led, LOW);   
  delay(1000);   
//tone(buzzer,1000);
//delay(1000);
noTone(buzzer);
delay(2000);
Serial.write("Pluie detectée");
} data1=data;

  if (data==1)
  {tap_servo.write(180);
      digitalWrite(buzzer,LOW);
            digitalWrite(led,LOW);
            noTone(buzzer);
            Serial.write("Pas de Pluie");


}data1=data;

}//}

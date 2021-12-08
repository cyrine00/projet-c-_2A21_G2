#include <Servo.h>

#include <Servo.h>

Servo tap_servo;

int sensor_pin = 4;
int tap_servo_pin =5;
int data;
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

} 
  if (data==1)
  {tap_servo.write(180);
      digitalWrite(buzzer,LOW);
            digitalWrite(led,LOW);
            noTone(buzzer);


}
}

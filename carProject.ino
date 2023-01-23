#include <Servo.h>
Servo myservo;
int motor_right_forward = 5;
int motor_right_backward = 3;
int motor_left_forward = 6;
int motor_left_backward = 11;
int incoming;
int trig = 13;
int echo = 2;
int ir_left = 8;
int ir_right = 12;
unsigned long time1 =0 ;
long duration =0, distance =0, distance_front=0, distance_left=0, distance_right=0;
int flag = 3;



void setup() {
myservo.attach(4);
myservo.write(180);
pinMode(motor_right_forward, OUTPUT);
pinMode(motor_right_backward, OUTPUT);
pinMode(motor_left_forward, OUTPUT);
pinMode(motor_left_backward, OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(ir_left, INPUT);
pinMode(ir_right, INPUT);
time1 = millis();
Serial.begin(9600);
}

void loop() {
  if(flag == 3){       // Race code
    if(Serial.available()){
      incoming = Serial.read();
    }
    if(incoming == 83){
      analogWrite(motor_left_forward, LOW);
      analogWrite(motor_left_backward, LOW);
      analogWrite(motor_right_forward, LOW);
      analogWrite(motor_right_backward, LOW);
    }
    if(incoming == 70){
      digitalWrite(motor_left_forward, HIGH);
      analogWrite(motor_left_backward, LOW);
      digitalWrite(motor_right_forward, HIGH);
      analogWrite(motor_right_backward, LOW);
    }
    if(incoming == 73){
      digitalWrite(motor_left_forward, HIGH);
      analogWrite(motor_left_backward, LOW);
      analogWrite(motor_right_forward, 150);
      analogWrite(motor_right_backward, LOW);
    }
    if(incoming == 71){
      analogWrite(motor_left_forward, 150);
      analogWrite(motor_left_backward, LOW);
      digitalWrite(motor_right_forward, HIGH);
      analogWrite(motor_right_backward, LOW);
    }
    if(incoming == 66){
      analogWrite(motor_left_forward, LOW);
      digitalWrite(motor_left_backward, HIGH);
      analogWrite(motor_right_forward, LOW);
      digitalWrite(motor_right_backward, HIGH);
    }
    if(incoming == 74){
      analogWrite(motor_left_forward, LOW);
      digitalWrite(motor_left_backward, HIGH);
      analogWrite(motor_right_forward, LOW);
      analogWrite(motor_right_backward, 150);
    }
    if(incoming == 72){
      analogWrite(motor_left_forward, LOW);
      analogWrite(motor_left_backward, 150);
      analogWrite(motor_right_forward, LOW);
      digitalWrite(motor_right_backward, HIGH);
    }
  }
  if(flag == 2){        // IR code
     int ir_left_value = digitalRead(ir_left);
     int ir_right_value = digitalRead(ir_right);
     Serial.print("right: ");
     Serial.print(ir_right_value);
     Serial.print("left: ");
     Serial.print(ir_left_value);
     Serial.println();
     if(ir_left_value == 0 && ir_right_value == 0){
      forward();
     }
     if(ir_left_value == 1 && ir_right_value == 0){
      analogWrite(motor_left_forward, 50);
      analogWrite(motor_left_backward, LOW);
      analogWrite(motor_right_forward, LOW);
      analogWrite(motor_right_backward, LOW);
     }
     if(ir_left_value == 0 && ir_right_value == 1){
      analogWrite(motor_left_forward, LOW);
      analogWrite(motor_left_backward, LOW);
      analogWrite(motor_right_forward, 50);
      analogWrite(motor_right_backward, LOW);
     }
  }
  if(flag == 1){        // Maze code
      distance_left = ultra();
      if(distance_left > 40){
        delay(50);
        Serial.print("leffffffffffffffffffffffffffffffffft");
        Serial.println();
        stops();
        left();
        forward();
      }else if(distance_left <= 40){
        forward();
        Serial.print("frrrrrrrrrrrrrrrrrrrrrront");
        Serial.println();
      }
    if((millis()-time1) >= 3000){
      back();
      stops();
      myservo.write(90);
      delay(200);
      distance_front = ultra();
      myservo.write(0);
      delay(200);
      distance_right = ultra();
      if(distance_front > 40){
        Serial.print("continuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuue");
        Serial.println();
        forward();
        myservo.write(180);
        delay(300);
      }
      if(distance_front <= 40){
        back();
        if(distance_right > 40){
          Serial.print("righttttttttttttttttttttttttttttttttttttttttt");
          Serial.println();
          right();
          stops();
          forward();
          myservo.write(180);
          delay(300);
        }
        else if(distance_right <= 40){
          Serial.print("backkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
          Serial.println();
          backward();
          stops();
          myservo.write(180);
          forward();
        }
      }
    }
  }
  if(flag == 4){   // For testing directions
    left();
    stops();
    right();
    stops();
    backward();
    stops();
  }
}

void forward()
{
analogWrite(motor_left_forward, 100);
analogWrite(motor_left_backward, LOW);
analogWrite(motor_right_forward, 100);
analogWrite(motor_right_backward, LOW);
delay(500);
}

void left()
{
analogWrite(motor_left_forward, LOW);
analogWrite(motor_left_backward, 100);
analogWrite(motor_right_forward, 100);
analogWrite(motor_right_backward, LOW);
delay(280);
time1 = millis();
}

void right()
{
analogWrite(motor_left_forward, 100);
analogWrite(motor_left_backward, LOW);
analogWrite(motor_right_forward, LOW);
analogWrite(motor_right_backward, 100);
delay(400);
time1 = millis();
}

void stops()
{
analogWrite(motor_left_forward, LOW);
analogWrite(motor_left_backward, LOW);
analogWrite(motor_right_forward, LOW);
analogWrite(motor_right_backward, LOW);
delay(200);
}

void backward()
{
analogWrite(motor_left_forward, 100);
analogWrite(motor_left_backward, LOW);
analogWrite(motor_right_forward, LOW);
analogWrite(motor_right_backward, 100);
delay(450);
time1 = millis();
}

void back()
{
analogWrite(motor_left_forward, LOW);
analogWrite(motor_left_backward, 100);
analogWrite(motor_right_forward, LOW);
analogWrite(motor_right_backward, 100);
delay(200);
time1 = millis();
}

double ultra(){
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration /29/2;
  delay(100);
  Serial.println(distance);
  return distance ;
}

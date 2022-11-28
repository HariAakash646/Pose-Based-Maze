#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 

AF_DCMotor motor_right(3);
AF_DCMotor motor_left(4);

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

SoftwareSerial MyBlue(2, 3);

char d=0;
int speed = 255;
int turn_speed = 255;
int increase = 100;
int orient = 0;
int distance = 100;
int delay_time = 400;
int tmp = 0;
int stop_dist = 5;
int buzzer_pin = 11;

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void Forward() {
  tmp = ((400 - orient + 0) % 400) / 100;
  orient = 0;
  for(int j = 0; j<tmp; j++) {
    motor_left.setSpeed(turn_speed); 
    motor_right.setSpeed(turn_speed);
    motor_left.run(FORWARD);  
    motor_right.run(BACKWARD);   
    delay(delay_time);
  }
  if(distance <= stop_dist) {
    Stop();
    digitalWrite(buzzer_pin,HIGH);
  }
  else if(MyBlue.read() == 'F') {
    digitalWrite(buzzer_pin,LOW);
    motor_right.setSpeed(speed);
    motor_left.setSpeed(speed);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);  
  }

}

void Backward() {
  tmp = ((400 - orient + 200) % 400) / 100;
  orient = 200;
  for(int j = 0; j<tmp; j++) {
    motor_left.setSpeed(turn_speed); 
    motor_right.setSpeed(turn_speed);
    motor_left.run(FORWARD);  
    motor_right.run(BACKWARD);  
    delay(delay_time);
  }
  if(distance <= stop_dist) {
    Stop();
    digitalWrite(buzzer_pin,HIGH);
  }
  else if(MyBlue.read() == 'B') {
    digitalWrite(buzzer_pin,LOW);
    motor_right.setSpeed(speed);
    motor_left.setSpeed(speed);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);  
  }
}

void Left() {
  tmp = ((400 - orient + 300) % 400) / 100;
  orient = 300;
  for(int j = 0; j<tmp; j++) {
    motor_left.setSpeed(turn_speed); 
    motor_right.setSpeed(turn_speed);
    motor_left.run(FORWARD);  
    motor_right.run(BACKWARD);   
    delay(delay_time);
  }
  if(distance <= stop_dist) {
    Stop();
    digitalWrite(buzzer_pin,HIGH);
  }
  else if(MyBlue.read() == 'L') {
    digitalWrite(buzzer_pin,LOW);
    motor_right.setSpeed(speed);
    motor_left.setSpeed(speed);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);  
  }
}

void Right() {
  tmp = ((400 - orient + 100) % 400) / 100;
  orient = 100;
  for(int j = 0; j<tmp; j++) {
    motor_left.setSpeed(turn_speed); 
    motor_right.setSpeed(turn_speed);
    motor_left.run(FORWARD);  
    motor_right.run(BACKWARD);   
    delay(delay_time);
  }
  if(distance <= stop_dist) {
    Stop();
    digitalWrite(buzzer_pin,HIGH);
  }
  else if(MyBlue.read() == 'R') {
    digitalWrite(buzzer_pin,LOW);
    motor_right.setSpeed(speed);
    motor_left.setSpeed(speed);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);  
  }
}

void Stop() {
  motor_right.run(RELEASE);
  motor_left.run(RELEASE);
}

void setup() {
  Serial.begin(9600);
  MyBlue.begin(9600);            // set up Serial library at 9600 bps

  // turn on motor
  motor_right.setSpeed(speed);
  motor_left.setSpeed(speed);
 
  motor_right.run(RELEASE);
  motor_left.run(RELEASE);

  pinMode(buzzer_pin,OUTPUT);
  digitalWrite(buzzer_pin, LOW);

  distance = readPing();
}

void loop() {
distance = readPing();
if(MyBlue.available()>0)
{
d=MyBlue.read();
if(d=='F')
{
    Forward();        
}
else if(d=='B')
{
  Backward();
}
else if(d=='L')
{
  Left();
}
else if(d=='R')
{
  Right();
}
else if(d=='S')
{
  Stop();
  digitalWrite(buzzer_pin,LOW);
}
}
}

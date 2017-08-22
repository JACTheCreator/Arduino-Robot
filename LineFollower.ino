#include <Servo.h> 

#define WHEEL_SPEED 180
#define LEFT_WHEEL_PIN 6
#define RIGHT_WHEEL_PIN 7

//Line Follower
#define s0 A0
#define s1 A1
#define s2 A2
#define s3 A3
#define s4 A4
#define s5 2
#define s6 3
#define s7 4

int state;
int input;
String string;
bool boolState;
Servo wheelLeft;
Servo wheelRight; 


void setup() 
{
  //Line Follower
  pinMode(s0, INPUT);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT); 
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
    Serial.begin(9600);
}

void loop()
{
    //Line Follower Forward
  Serial.println("Line Follower Forward");
  while(true)
  {  
    if(digitalRead(s4)== LOW  && digitalRead(s5) == LOW && digitalRead(s6) == LOW && digitalRead(s7) == LOW && digitalRead(s3)== LOW  && digitalRead(s2) == LOW && digitalRead(s1) == LOW && digitalRead(s0) == LOW )
      moveStop();
    else if(digitalRead(s3)== LOW && digitalRead(s4) == LOW)
      moveForward();
    else if(digitalRead(s3)== LOW  || digitalRead(s2) == LOW || digitalRead(s1) == LOW || digitalRead(s0) == LOW) 
      moveRight();
    else if(digitalRead(s4)== LOW  || digitalRead(s5) == LOW || digitalRead(s6) == LOW || digitalRead(s7) == LOW) 
      moveLeft();
    else
    {
      moveStop();
  //          break;
    }
  }   
}

void moveForward()
{
  attachWheel();
  
  wheelLeft.write(WHEEL_SPEED); 
  wheelRight.write(-WHEEL_SPEED);
}

void moveReverse()
{
  attachWheel();
  
  wheelLeft.write(-WHEEL_SPEED); 
  wheelRight.write(WHEEL_SPEED);
}

void moveStop()
{
  wheelLeft.detach();
  wheelRight.detach();
}

void moveRight()
{
  attachWheel();

  wheelLeft.write(WHEEL_SPEED);
  wheelRight.write(WHEEL_SPEED);
}

void moveLeft()
{
  attachWheel();

  wheelLeft.write(-WHEEL_SPEED);
  wheelRight.write(-WHEEL_SPEED);   
}

void moveRightReverse()
{
  attachWheel();

  wheelLeft.write(-WHEEL_SPEED);
  wheelRight.write(-WHEEL_SPEED);
}

void moveLeftReverse()
{
  attachWheel();

  wheelLeft.write(WHEEL_SPEED);
  wheelRight.write(WHEEL_SPEED);   
}

void attachWheel()
{
   wheelLeft.attach(LEFT_WHEEL_PIN);
   wheelRight.attach(RIGHT_WHEEL_PIN);
}


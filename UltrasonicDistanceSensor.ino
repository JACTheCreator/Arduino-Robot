#include <Servo.h>                          
 
Servo wheelLeft;                           
Servo wheelRight;


#define WHEEL_SPEED 180
const int trigPin = 9;
const int echoPin = 8;
long duration;
int distanceCm, distanceInch;

void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  attachWheels();
  Serial.begin(9600);
}
void loop() 
{      
  delay(15);
  if(isObstacleClose(2))
  {
    Serial.println("Too Close");
//    delay(1000);
    moveBackwards();
    delay(1000);
    moveRight();
    delay(2000);
  }
  else
  {
      Serial.println("Nothing");
      moveForward();
  }
}
bool isObstacleClose(int distancetoDetected)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distanceInch = duration*0.0133/2;
  if(distanceInch <= distancetoDetected && distancetoDetected != 0){
    return true;
  }
  return false;
}

void moveForward()
{
  attachWheels();
  
  wheelLeft.write(WHEEL_SPEED); 
  wheelRight.write(-WHEEL_SPEED);
}

void moveBackwards()
{
  attachWheels();
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
  attachWheels();
  wheelLeft.write(WHEEL_SPEED);
  wheelRight.write(WHEEL_SPEED);
}

void moveLeft()
{
  attachWheels();
  wheelLeft.write(-WHEEL_SPEED);
  wheelRight.write(-WHEEL_SPEED);   
}

void attachWheels()
{
   wheelLeft.attach(2);
   wheelRight.attach(3);
}


#include <Servo.h> 

#define WHEEL_SPEED 180
#define LEFT_WHEEL_PIN 11
#define RIGHT_WHEEL_PIN 9 
#define BUZZER_PIN 7
#define ULTRASONIC_SENSOR 8

//Line Follower
#define s0 A0
#define s1 A1
#define s2 A2
#define s3 A3
#define s4 A4
#define s5 A5
#define s6 4
#define s7 8

const int frequency = 31; //Range of frequeny is between 31 to 65535 on the  arduino uno
const int duration = 5000; 

int state;
int input;
String string;
bool boolState;
int intState;
long duration1;
long inches;
long cm;

bool isStop = false;

Servo wheelLeft;
Servo wheelRight; 


void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);

  //Line Follower
  pinMode(s0, INPUT);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT); 
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
  
  wheelLeft.attach(LEFT_WHEEL_PIN);
  wheelRight.attach(RIGHT_WHEEL_PIN); 

  Serial.begin(9600);

}

void loop()
{
  if(Serial.available()>0)
  { 
    state = Serial.read();

    //Move Forward
    if(state == '1')
    { 
      moveForward();
      Serial.println("Move Forward");
      state = 0;
    } 

    //Reverse
    if(state == '2')
    { 
      moveReverse();
      Serial.println("Reverse");
      state = 0;
    }

    //Stop Moving
    if(state == '3')
    { 
      moveStop();
      Serial.println("Stop Moving");
      state = 0;
    }

    //Move to the Left
    if(state == '4')
    { 
      moveLeft();
      Serial.println("Move to the Left");
      state = 0;
    }

    //Move to the Right    
    if(state == '5')
    { 
      moveRight();
      Serial.println("Move to the Right");
      state = 0;
    }

    //Line Follower Values
    if(state == '6')
    { 
      boolState = digitalRead(s0);
      string = String(boolState);
      Serial.println("s0: "+ string);

      boolState = digitalRead(s1);
      string = String(boolState);
      Serial.println("s2: "+ string);

      boolState = digitalRead(s2);
      string = String(boolState);
      Serial.println("s2: "+ string);

      boolState = digitalRead(s3);
      string = String(boolState);
      Serial.println("s3: "+ string);

      boolState = digitalRead(s4);
      string = String(boolState);
      Serial.println("s4: "+ string);

      boolState = digitalRead(s5);
      string = String(boolState);
      Serial.println("s5: "+ string);

      boolState = digitalRead(s6);
      string = String(boolState);
      Serial.println("s6: "+ string);

      boolState = digitalRead(s7);
      string = String(boolState);
      Serial.println("s7: "+ string);
      
      state = 0;
    }

    //Line Follower Forward
    if(state == '7')
    { 
      Serial.println("Line Follower Forward");
      while(true)
      {  
        if(digitalRead(s4)== HIGH  && digitalRead(s5) == HIGH && digitalRead(s6) == HIGH && digitalRead(s7) == HIGH && digitalRead(s3)== HIGH  && digitalRead(s2) == HIGH && digitalRead(s1) == HIGH && digitalRead(s0) == HIGH )
          moveStop();
        else if(digitalRead(s3)== HIGH && digitalRead(s4) == HIGH)
          moveForward();
        else if(digitalRead(s3)== HIGH  || digitalRead(s2) == HIGH || digitalRead(s1) == HIGH || digitalRead(s0) == HIGH) 
          moveRight();
        else if(digitalRead(s4)== HIGH  || digitalRead(s5) == HIGH || digitalRead(s6) == HIGH || digitalRead(s7) == HIGH) 
          moveLeft();
        else
        {
          moveStop();
//          break;
        }
      } 
       state = 0;
    }

     //Line Follower Reverse
    if(state == '8')
    { 
      Serial.println("Line Follower Reverse");
      while(true)
      {  
        if(digitalRead(s4)== HIGH  && digitalRead(s5) == HIGH && digitalRead(s6) == HIGH && digitalRead(s7) == HIGH && digitalRead(s3)== HIGH  && digitalRead(s2) == HIGH && digitalRead(s1) == HIGH && digitalRead(s0) == HIGH )
          moveStop();
        else if(digitalRead(s3)== HIGH && digitalRead(s4) == HIGH)
          moveReverse();
        else if(digitalRead(s3)== HIGH  || digitalRead(s2) == HIGH || digitalRead(s1) == HIGH || digitalRead(s0) == HIGH) 
          moveLeftReverse();
        else if(digitalRead(s4)== HIGH  || digitalRead(s5) == HIGH || digitalRead(s6) == HIGH || digitalRead(s7) == HIGH) 
          moveRightReverse();
        else
        {
          moveStop();
//          break;
        }
      } 
       state = 0;
    }

    if(state =='9')
    {
      while(true)
      {
        ultraSonicSetUp();
      }
    }
    
    //Piezo Buzzer 
    if(state == '0')
    { 
      tone(BUZZER_PIN, frequency, duration);
      Serial.println("Piezo Buzzer");
      state = 0;
    }
  }
}

void moveForward()
{
  if(isStop)
    attachWheel();
  
  wheelLeft.write(WHEEL_SPEED); 
  wheelRight.write(-WHEEL_SPEED);
}

void moveReverse()
{
  if(isStop)
    attachWheel();
  
  wheelLeft.write(-WHEEL_SPEED); 
  wheelRight.write(WHEEL_SPEED);
}

void moveStop()
{
  wheelLeft.detach();
  wheelRight.detach();

  isStop = true;
}

void moveRight()
{
  if(isStop)
    attachWheel();

  wheelLeft.write(WHEEL_SPEED);
  wheelRight.write(WHEEL_SPEED);
}

void moveLeft()
{
  if(isStop)
    attachWheel();

  wheelLeft.write(-WHEEL_SPEED);
  wheelRight.write(-WHEEL_SPEED);   
}

void moveRightReverse()
{
  if(isStop)
    attachWheel();

  wheelLeft.write(-WHEEL_SPEED);
  wheelRight.write(-WHEEL_SPEED);
}

void moveLeftReverse()
{
  if(isStop)
    attachWheel();

  wheelLeft.write(WHEEL_SPEED);
  wheelRight.write(WHEEL_SPEED);   
}

void attachWheel()
{
   wheelLeft.attach(LEFT_WHEEL_PIN);
   wheelRight.attach(RIGHT_WHEEL_PIN);
}

void ultraSonicSetUp()
{
  pinMode(ULTRASONIC_SENSOR, OUTPUT);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_SENSOR, LOW);

  pinMode(ULTRASONIC_SENSOR, INPUT);
  pinMode(ULTRASONIC_SENSOR, INPUT);

  inches = microsecondsToInches(duration1);
  cm = microsecondsToCentimeters(duration1);


  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) 
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) 
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


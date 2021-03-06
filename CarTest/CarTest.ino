/* Elegoo robot car object avoidance */

#include <Wheels.h>
Wheels car;

//#include <Proximity.h>
//Proximity eyes(myservo);

// variables //
//int forwardDistance = 0;
//int rightDistance = 0;
//int leftDistance = 0;
int tooClose = 40;

#include <Servo.h> //servo library

Proximity::Proximity(Servo s)
{
  myservo = s;
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  myservo.attach(3);  // attach servo on pin 3
  Serial.begin(9600);
}

void Proximity::forward() {
  direction = 90;
  myservo.write(direction);
}

void Proximity::left() {
  direction = 20;
  myservo.write(direction);
}

void Proximity::right() {
  direction = 180;
  myservo.write(direction);
}

/* Ultrasonic distance measurement */
int Proximity::getDistance()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance / 58;

  #ifdef send
    Serial.print("distance at ");
    Serial.print(direction);
    Serial.print(" deg: ");
    Serial.println(Fdistance);
  #endif

  return (int)Fdistance;
}

Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;

 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}  

void setup() 
{ 
  Serial.println("*** setup");
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  car.stop();  
} 
//void setup() 
//{ 
//  car.stop();
//  car.setSpeed(car.medium);
//  eyes.forward();
//} 

void loop() 
{
  Serial.println("*** loop");
    myservo.write(90);//setservo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif

//  forwardDistance = eyes.getDistance();
//  if (forwardDistance > tooClose)
  if (middleDistance <= tooClose)
  {
    car.forward();
  }
  else
  {     
    car.stop();
    delay(500);

      delay(500);                         
      myservo.write(20);          
      delay(1000);      
      rightDistance = Distance_test();
      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif

      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
      #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif
    
//    eyes.left();
//    delay(1000);
//    leftDistance = eyes.getDistance();
//    eyes.right();
//    delay(1000);
//    rightDistance = eyes.getDistance();
    
//    eyes.forward();
    
    if ((leftDistance < tooClose) || (rightDistance < tooClose))
    {
      // back up and turn around
      car.back();
      delay(200);
      // turn around by turning left twice
      car.left();
      car.left();
    }
    else if (leftDistance > rightDistance)
    {
      car.left();
      delay(500);
    }
    else if (rightDistance > leftDistance)
    {
      car.right();
      delay(500);
    }
  }
}


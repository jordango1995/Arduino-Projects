//Ultrasonic Distance Sensor controls Servos
//for skelly
//
//By Jordan Gonzales


#include <Servo.h>    //servo library
#include <NewPing.h>  //ultrasonic library

const int ServoPin1 = 11;
const int TriggerPin = 3;
const int EchoPin = 2;
int waveCount = 0;

void(*resetFunc)(void) = 0;

//100cm is max detection distance
NewPing sonar(TriggerPin, EchoPin, 100);
Servo servo1;          //first servo object

void setup() {

  Serial.begin(9600);         
  servo1.attach(ServoPin1);   //attach first servo to arduino pin 11
  
}

void loop() {

  int cm = sonar.ping_cm();
  Serial.println(cm);

  //int angle = map(cm, 20, 50, 80, 120);
  //servo1.write(angle);

  //makes a wave gesture if somebody is within 50cm of sensor
  if (cm <= 100 && cm > 5) {

    servo1.write(45);
    delay(250);
    servo1.write(0);
    delay(250);
    servo1.write(45);
    delay(250);
    servo1.write(0);
    delay(250);

    waveCount += 1;

    if (waveCount == 3) {
      delay(10000);
      resetFunc();
    }


    //delay(10000);
    //cm = sonar.ping_cm();
    
  }

  delay(250);

}

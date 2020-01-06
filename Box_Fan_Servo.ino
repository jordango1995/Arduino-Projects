/*
Remote-controlled fan servo
by Jordan Gonzales

Press a button on the IR remote and it turns the servo to change the dial on the box fan.
*/


#include <Servo.h>    //includes servo library
#include <IRremote.h> //includes IR Remote library

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;


//hexcodes for buttons on remote
#define BUTTON_1 0x1
#define BUTTON_2 0x2
#define BUTTON_3 0x3
#define BUTTON_0 0x33
#define BUTTON_OK 0xFF38C7

//int outPin = 5; //putting the signal to pin 5 of arduino

Servo servo;

int pos = 0;
int outPin = 5; //putting the signal to pin 5 of arduino

//#include <FastLED.h>
//#define LED_PIN   5

void setup() {

  pinMode (outPin, OUTPUT);
  servo.attach(5);
  irrecv.enableIRIn();      //IR receiver input from remote
    
}

void loop() {

  if (irrecv.decode(&results))
  {
    if (results.value == BUTTON_0)
    {
      for (pos = 1; pos >= 0; pos -= 1);
      servo.write(pos);
      delay(15);
    }
  }

  if (irrecv.decode(&results))
  {
    if (results.value == BUTTON_1)
    {
      for (pos = 0; pos <= 15; pos += 1)
        servo.write(pos);
        delay(15);
    }
  }

   if (irrecv.decode(&results))
  {
    if (results.value == BUTTON_2)
    {
      servo.write(30);
      delay(15);
    }
  }

   if (irrecv.decode(&results))
  {
    if (results.value == BUTTON_3)
    {
      servo.write(45);
      delay(15);
    }
  }
}

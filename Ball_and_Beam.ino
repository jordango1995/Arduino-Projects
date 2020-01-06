
#include <Wire.h>  // I2C Library
#include <Servo.h> // Servomotor library 
#include <SparkFun_VL53L1X.h> // distance sensor library

#define BAUD_RATE 19200
#define MOTOR_OUT_PIN 8 
#define N 10 // Filter length 

// Definitions for servo motor setpoints 
#define ANGLE_OFFSET 90 
#define SERVO_PULSE_MIN 600
#define SERVO_PULSE_MAX 2300
#define SERVO_PULSE_MID 1500 // the neutral position of the servo

// PID Gain Definitions 
#define KP 30
#define KI 1
#define KD 50
#define MAX_INT 10

SFEVL53L1X distanceSensor;   // sensor object for distance readings 
Servo myservo;              // servo object for motor control 

// Filter coefficients 
float filter[10] = {-0.0053,-0.0028,0.0435,0.1695,0.2951,0.2951,0.1695,0.0435,-0.0028,-0.0053}; 
float prevDistVals[N] = {0,0,0,0,0,0,0,0,0,0}; 
float prevDeriv[N] = {0,0,0,0,0,0,0,0,0,0}; 

// Variables for control
float desiredPos = 300; 
float distance = 0;
float filtDist = 0;
float prevFiltDist = 0;
float error = 0; 
float prevError = 0; 
float intError = 0; 
float derError = 0; 
float filtDeriv = 0; 
float motorSetPos = 0; 
float integral = 0; //ADDED

// Variables for timing data 
uint32_t ts0;
uint32_t ts1;
uint32_t ts2;
int stepTime; 


void setup(void)
{
  Wire.begin(); // Initialize I2C
  Serial.begin(BAUD_RATE); // start serial communication 

  // Initialize servo motor object 
  myservo.attach(MOTOR_OUT_PIN, SERVO_PULSE_MIN, SERVO_PULSE_MAX);

  // Test range sensor initialization 
  if (distanceSensor.begin() == false)
    Serial.println("Sensor online!");
  else Serial.println("Sensor FAIL!");

  // Configure range sensor
  distanceSensor.setDistanceModeShort();
  distanceSensor.startRanging();

  // get intial timing data
  ts0 = millis(); 
  ts1 = ts0; 
}


void loop(void)
{

  // Start by getting distance sensor measurements 
  distance = distanceSensor.getDistance(); 

  // Shift sensor measurement array and add new value 
  memcpy(prevDistVals, &prevDistVals[1], sizeof(prevDistVals) - sizeof(float)); 
  prevDistVals[9] = distance; 

  // Multiply by filter coefficients to calculate filtered motor position 
  filtDist = 0; 
  for(int i=0;i<10;i++){
    filtDist += prevDistVals[i]*filter[i]; 
    
  }
  
  // Each loop, calculate the time elapsed 
  ts2 = millis() / 1000; //Converts time from ms to sec
  float(stepTime) = ts2-ts1; 
  Serial.print("Current time: ");
  Serial.print(ts2-ts0);
  ts1 = ts2;


  // Calculate error, integrated error, and derivative of error 
  // Convert error to meters and timing to seconds  
  error = desiredPos - distance;
  error = error / 1000; //Converts mm to m
  integral = error * stepTime;
  intError = intError + integral;
  derError = error - prevError / stepTime;
  
  prevError = error; 
  
  // Shift derivative array and add new value prevDeriv
  memcpy(prevDeriv, &prevDeriv[1], sizeof(prevDeriv) - sizeof(float)); 
  prevDeriv[9] = derError; 

  // Multiply by filter coefficients to calculate filtered motor position 
  filtDeriv = 0; 
  for(int i=0;i<10;i++){
    filtDeriv += prevDeriv[i]*filter[i]; 
  }
  
  // Limit max/min integrated error 
  if(intError>MAX_INT)
    intError = MAX_INT;
  if(intError<-MAX_INT)
    intError = -MAX_INT; 
  
  
  // Calculate motor set position using PID gains 
  motorSetPos = KP*error + KI * intError + KD * derError;
  motorSetPos = 9.44 * motorSetPos; //pwm in us


  // Limit max/min motor angle 
  if(motorSetPos>90)
    motorSetPos = 90;
  if(motorSetPos<-90)
    motorSetPos = -90; 
  
  // Print filtered distance 
  Serial.print("\t filtDist(mm): ");
  Serial.print(filtDist); 
  Serial.println();
  
  // Set motor angle, must add motorSetPos angle scaled up to microseconds using linear relationship from Lab 6
  myservo.writeMicroseconds(SERVO_PULSE_MID + motorSetPos);
  
  
}


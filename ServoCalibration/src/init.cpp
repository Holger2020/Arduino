#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685 16-Channel Servo Controller
// Adafruit_PWMServoDriver servo = Adafruit_PWMServoDriver();

// #define SERVOMIN 100  // min position of each servo
// #define SERVOMAX 600  // max position of each servo

// #define SERVO_Foot1 1  // Foot, right front
// #define SERVO_Knee1 2  // Knee, right front
// #define SERVO_Hip1 0   // Hip,  right front
// #define SERVO_0 0
// #define SERVO_1 1
// #define SERVO_2 2
// #define SERVO_3 3
// #define SERVO_4 4
// #define SERVO_14 14
// #define SERVO_15 15

// #define MODE_LEFT 0
// #define MODE_RIGHT 1
// #define MODE_STEP_LEFT 2
// #define MODE_STEP_RIGHT 3

// Bewegungsraum:
// Hip: 300..600, 20..30%,

// uint8_t servonum = 0;
// uint8_t numberOfServos = 5;
// float servoFactor = (SERVOMAX - SERVOMIN) / 100;
// int i = 0;

/**
 * Setup 
 */
// void setup() {

//   Serial.begin(9600);
//   Serial.println("");
//   Serial.println("#####################");
//   Serial.println("###  Start Main  ####");
//   Serial.println("#####################");

//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(LED_BUILTIN, OUTPUT);

//   // initialized servos
//   servo.begin();
//   servo.setPWMFreq(60);
//   // servoHome();
//   // servo.writeMicroseconds(1500); //set initial servo position if desired
//   //myservo.attach(7);  //the pin for the servo control
// }

/**
 * Main loop
 */
// void loop() {

//   // console output
//   Serial.print("i=");
//   Serial.print(i);
//   Serial.println(".");
//   i++;

//   // Serial.print("Move servo: ");
//   // Serial.print(foot);
//   // Serial.println("");


//   // servo.setPWM(foot, 0, end);
//   // servoMove(SERVO_2,99,end, start);
//   // delay(3000);

//   // servo at port 15
//   servoMoveTest15();
//   delay(3000);

//   // All servos move
//   //servoMoveTestMultiple();



//   blinkLed();
// }

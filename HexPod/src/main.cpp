#include <Arduino.h>
#include <SPI.h>
#include <../lib/led.h>
#include <../lib/boardPins.h>
#include <../lib/leg.h>
#include <../lib/button.h>
#include <../lib/move.h>
#include <Adafruit_PWMServoDriver.h>

// int i = 0;
Led *m_ledRed = nullptr;    
Led *m_ledYellow = nullptr; 
Led *m_ledGreen = nullptr;  
Digits m_digits = Digits(DIGIT_DATA_PIN, DIGIT_CLOCK_PIN, DIGIT_CS_PIN);
// Button m_button = Button(BUTTON);
Leg *m_leg;
Move *m_move;
boolean m_moveForward; // move direction
Adafruit_PWMServoDriver m_servoDriver;
boolean m_doDelay = false;

/**
 * Setup
 */
void setup()
{
    Serial.begin(9600);
    Serial.println("");
    Serial.println("#####################");
    Serial.println("###  Start Main 1 ####");
    Serial.println("#####################");

    // initialize digital pin LED_BUILTIN as an output.
    // pinMode(LED_BUILTIN, OUTPUT);
    // pinMode(LED_RED, OUTPUT);
    // pinMode(LED_YELLOW, OUTPUT);
    // pinMode(LED_GREEN, OUTPUT);

    m_ledRed = new Led(LED_RED);
    m_ledGreen = new Led(LED_GREEN);
    m_ledYellow = new Led(LED_YELLOW);

    m_ledRed->enable(true);
    m_ledYellow->enable(true);
    m_ledGreen->enable(true);

    m_ledRed->activate(true);
    m_ledYellow->activate(true);
    m_ledGreen->activate(true);
    delay(500);
    m_ledRed->activate(false);
    m_ledYellow->activate(false);
    m_ledGreen->activate(false);
    // delay(00);

    // m_ledRed->setTimeOnOff(500, 2000);
    // m_ledYellow->setTimeOnOff(2000, 500);
    // m_ledGreen->setTimeOnOff(5000, 1000);

    m_moveForward = true;
    m_servoDriver = Adafruit_PWMServoDriver();
    m_servoDriver.begin();
    m_servoDriver.setPWMFreq(60);

    m_leg = new Leg(&m_servoDriver, LEG_1, SERVO_LEG1_HIP, SERVO_LEG1_KNEE, SERVO_LEG1_FOOT);  // hip, knee, foot
    // m_leg = new Leg(&m_servoDriver, LEG_1, SERVO_LEG1_HIP, SERVO_NONE, SERVO_NONE); // hip
    // m_leg = new Leg(&m_servoDriver, LEG_1, SERVO_NONE, SERVO_LEG1_KNEE, SERVO_NONE); // kne
    // m_leg = new Leg(&m_servoDriver, LEG_1, SERVO_NONE, SERVO_NONE, SERVO_LEG1_FOOT); // foot
    // m_leg = new Leg(&m_servoDriver, LEG_1, SERVO_NONE, SERVO_LEG1_KNEE, SERVO_LEG1_FOOT); // knee, foot

    m_move = new Move(m_leg);

    // m_digits.show(7, 6, 5, 4, 3, 2, 1, 0);
    // delay(1000);
    // m_digits.show(6, 5, 4, 3, 2, 1, 0, 7);
    // delay(1000);
    // m_digits.show(5, 4, 3, 2, 1, 0, 7, 6);
    // delay(1000);
    // m_digits.show(4, 3, 2, 1, 0, 7, 6, 5);
    // delay(1000);
    // m_digits.show(3, 2, 1, 0, 7, 6, 5, 4);
    // delay(1000);
    // m_digits.show(2, 1, 0, 7, 6, 5, 4, 3);
    // delay(1000);
    // m_digits.show(1, 0, 7, 6, 5, 4, 3, 2);
    // delay(1000);
    // m_digits.show(0, 7, 6, 5, 4, 3, 2, 1);
    // delay(1000);
    // m_digits.show(7, 6, 5, 4, 3, 2, 1, 0);
    // delay(3000);
    m_digits.clear();
    // delay(3000);
    // m_digits.showAtPosition(0,100);
    // m_digits.showAtPosition(1,101);
    // m_digits.showAtPosition(2,56);
    // m_digits.showAtPosition(3,78);

    Serial.println("");
    Serial.println("#####################");
    Serial.println("###     OUT      ####");
    Serial.println("#####################");
    delay(2000);
} // setup()

/**
 * Main loop
 */
void loop()
{
    // Serial.print("Loop: i=");
    // Serial.println(i);

    // m_ledRed->blinkLed();
    // m_ledGreen->blinkLed();
    // m_ledYellow->blinkLed();
    // m_ledGreen->activate(true);
    // delay(50);
    // m_ledGreen->activate(false);

    if (m_move->isMoveCompleted())
    {
        if (m_doDelay)
        {
            // wait after each moveforward/backward
            // delay(4000);
            m_doDelay = false;
        }
        Serial.println("Loop: isMoveCompleted()=true, initialize new move now");
        if (m_moveForward)
        {
            m_move->forwardInit();
            if (m_move->isForwardCompleted())
            {
                Serial.println("Loop: isForwardCompleted()=true");
                m_moveForward = false;

                m_ledYellow->activate(false);
                m_ledRed->activate(true);
                m_doDelay = true;
            }
        }
        else // moveBackwards
        {
            m_move->backwardsInit();
            if (m_move->isBackwardsCompleted())
            {
                Serial.println("Loop: isBackwardsCompleted()=true");
                m_moveForward = true;

                m_ledYellow->activate(true);
                m_ledRed->activate(false);
                m_doDelay = true;
            }
        }
    }
    MoveDatax moveData = m_move->getMoveData();
    m_digits.showAtPosition(0,moveData.hip);
    m_digits.showAtPosition(1,moveData.knee);
    m_digits.showAtPosition(2,moveData.foot);
    // m_digits.showAtPosition(3,m_move->getMoveCounter()); // show nn
    m_digits.showAtPositionNeg(3,m_move->getMoveCounter());  // show +n or -n
    m_move->move();

    // if (m_button.isButtonPressed())
    // {
    //     // m_ledRed->activate(true);
    // }
    // else
    // {
    //     // m_ledRed->activate(false);
    // }

    // digitalWrite(LED_BUILTIN, LOW);
    // digitalWrite(LED_RED, LOW);
    // digitalWrite(LED_GREEN, LOW);
    // digitalWrite(LED_YELLOW, LOW);

    // console output
    // Serial.print("i=");
    // Serial.print(i);
    // Serial.println(".");
    // i++;
}

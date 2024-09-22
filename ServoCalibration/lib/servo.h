#ifndef SERVO_H
#define SERVO_H
#include <Adafruit_PWMServoDriver.h>
#include <../lib/digits.h>

class Servo
{
private:
    Adafruit_PWMServoDriver* m_servoDriver;
    unsigned int m_servoNumber = 0; // Adafruit PCA9685 16-Channel Servo Controller number
    float m_servoFactor = -1.0;
    float m_startPos;
    float m_endPos;
    // Digits m_digits;
    boolean m_endReached;  // move until the end was reached
    unsigned long m_delayTime;  // time to slow down the servo movement
    unsigned int m_up; // direction of servo movement
    unsigned int m_servoStart;  // start servo position 
    unsigned int m_servoEnd; // end servo position
    unsigned int m_prevEnd; // end servo position from previous move
    unsigned int m_steps; // steps between start and end servo position
    unsigned int m_currStep;  // current step between 0..m_steps
    unsigned int m_servoPosition;  // current servo position between SERVO_MIN and SERVO_MAX
    unsigned int m_stepSize; // defines the speed of the servo moves
    // enum
    // {
    //     MODE_LEFT,
    //     MODE_RIGHT,
    //     MODE_STEP_LEFT_not_used,
    //     MODE_STEP_RIGHT_not_used,
    //     HOME_POSITION_not_used
    // } m_moveMode;
    void init(unsigned int servoNumber);

public:
    Servo(); // Default constructor
    Servo(Adafruit_PWMServoDriver* servoDriver, unsigned int servoNum);
    void servoHome();
    void initMove(unsigned int speed, unsigned int end);
    void move();
    boolean isMoveCompleted();

    // no yield methods:
    void servoMove(unsigned int speed, unsigned int start, unsigned int end);
    void servoMoveRel(unsigned int speed, unsigned int start, unsigned int end);

    //obsolete
    // void setPosition(float start, float end);
    // void servoCtl(unsigned int servoNum, int mode, unsigned int speed, unsigned int position);
    // void servoMoveMultiple(int servoData[], int speed);
};

#endif
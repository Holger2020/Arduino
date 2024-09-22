#ifndef LEG_H
#define LEG_H

#include <../lib/servo.h>
#include <Adafruit_PWMServoDriver.h>

#define LEG_1 1

/**
 * A leg
 */
class Leg
{
private:
    unsigned int m_legNumber; 
    unsigned int m_servoNumberHip; 
    unsigned int m_servoNumberKnee; 
    unsigned int m_servoNumberFoot; 
    float m_startPos;
    float m_endPos;
    Servo* m_servoHip = nullptr; 
    Servo* m_servoKnee = nullptr; 
    Servo* m_servoFoot = nullptr; 
    void init(Adafruit_PWMServoDriver* servoDriver, unsigned int legNumber, unsigned int servoHip, unsigned int servoKnee, unsigned int servoFoot);

public:
    Leg(); // Default constructor
    Leg(Adafruit_PWMServoDriver* servoDriver, unsigned int legNumber, unsigned int servoHip, unsigned int servoKnee, unsigned int servoFoot);
    void initMove(unsigned int moveData[]);
    void initMove(unsigned int moveData[], unsigned int startPos);
    void move();
    boolean isMoveCompleted();

    // void moveHome();
    // void moveCtl(unsigned int servoNum, int mode, unsigned int speed, unsigned int position);
    // void move(unsigned int servoNum, unsigned int speed, unsigned int start, unsigned int end);
    // void moveRel(unsigned int servoNum, unsigned int speed, unsigned int start, unsigned int end);
    // void moveMultiple(int servoData[], int speed);
    // void moveTestMultiple();
    // void setPosition(float start, float end);
};

#endif
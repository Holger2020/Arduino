#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <../lib/servo.h>
#include <../lib/digits.h>
#include <../lib/boardPins.h>

/**
 * A single servo motor
 */

#define SERVOMIN 100     // min position of each servo - 100%
#define SERVOMAX 600     // max position of each servo - 0%
#define HOME_POSITION 50 /* in %, start with 50% as home position */
#define STEP_SIZE 5
#define MIN_STEP 3000

/**
 * Control a single servo
 * Used controller:
 * - PCA9685 16-Channel Servo Controller
 * - Adafruit_PWMServoDriver
 */

/**
 * Default Constructor
 */
Servo::Servo()
{
    Serial.println("Servo() Default Constructor");
}

/**
 * Constructor
 */
Servo::Servo(Adafruit_PWMServoDriver *servoDriver, unsigned int servoNumber)
{
    m_servoDriver = servoDriver;
    // Serial.print("Servo::Servo() IN: servoNumber=");
    // Serial.print(servoNumber);
    // Serial.print(", servoAdr=");
    // Serial.print((uintptr_t)this, HEX);

    init(servoNumber);

    // Serial.print(", m_startPos=");
    // Serial.print(m_prevEnd);
    // Serial.println("Servo::Servo() OUT");
    // Serial.print(m_servoNumber);
    // Serial.println(", Servo() OUT");
}

/**
 * Initialize servo
 */
void Servo::init(unsigned int servoNumber)
{
    m_endReached = true; // this means that new move params can be accepted
    m_servoNumber = servoNumber;
    m_servoPosition = 0;
    m_stepSize = STEP_SIZE;
    m_servoFactor = (float)(SERVOMAX - SERVOMIN) / 100.0;
    m_startPos = int(m_servoFactor * HOME_POSITION + SERVOMIN);
    m_prevEnd = HOME_POSITION; // define the start position for the next move
    m_lastStep = 0L;
}

/**
 * Initial position of the servo
 */
void Servo::servoHome()
{
    // Serial.print("Servo::servoHome() IN: servoNumber=");
    // Serial.print(m_servoNumber);

    m_servoDriver->setPWM(m_servoNumber, 0, m_startPos);

    // Serial.println(", servoHome() OUT");
}

/**
 * Set move parameters for loop movements
 * @param speed    of the servo movement (0: slow, 100:highest speed)
 * @param start    from 0...100% - this is the end from the previous move
 * @param end      from 0...100%
 * y=mx + n
 * m=(END-START)/100%
 * servoPos = END - (END-START)/100% * valueIn
 * Mapping: start left
 * input - servoPosition
 * 0%    -  600 (most left)
 * 20%   -  500
 * 40%   -  400
 * 60%   -  300
 * 80%   -  200
 * 100%  -  100 (most right)
 */
void Servo::initMove(unsigned int speed, unsigned int end)
{
    // Serial.print("Servo::initMove() IN: servoNumber=");
    // Serial.print(m_servoNumber);
    // Serial.print(", start=");
    // Serial.print(m_prevEnd);
    // Serial.print(", end=");
    // Serial.print(end);
    // Serial.print(", servoAdr=");
    // Serial.print((uintptr_t)this, HEX);

    // IN=0   --> 50 msec
    // IN=100 --> 0 msec
    m_delayTime = 100L - speed; /* msec */

    unsigned int newStart;
    unsigned int newEnd;

    if (m_prevEnd < end)
    {
        // move up
        m_up = true;
        newStart = m_prevEnd;
        newEnd = end;
    }
    else
    {
        // move down
        m_up = false;
        newStart = end;
        newEnd = m_prevEnd;
    }
    m_prevEnd = end; // the end position is the start position for the next move

    // Serial.print(", servoFactor=");
    // Serial.println(m_servoFactor);

    // translate percentage (0..100%) to (SERVO_MIN..SERVO_MAX)
    m_servoStart = int(SERVOMAX - m_servoFactor * newStart);
    m_servoEnd = int(SERVOMAX - m_servoFactor * newEnd);

    // Serial.print(", m_servoStart=");
    // Serial.print(m_servoStart);
    // Serial.print(", m_servoEnd=");
    // Serial.println(m_servoEnd);

    m_steps = m_servoStart - m_servoEnd;
    m_currStep = 0;
    m_endReached = false;

    // Serial.println("Servo::initMove() OUT");
}

/**
 * Control Servo Move with relative position from 0%...100%
 * This method is iterative, i.e. it can be called in a loop until isMoveCompleted() returns true;
 */
void Servo::move()
{
    // Serial.print("Servo::move() IN: servoNumber=");
    // Serial.print(m_servoNumber);
    // Serial.print(", servoAdr=");
    // Serial.print((uintptr_t)this, HEX);
    // Serial.print(", m_endReached=");
    // Serial.print(m_endReached);
    // Serial.print(", m_servoStart=");
    // Serial.print(m_servoStart);
    // Serial.print(", m_servoEnd=");
    // Serial.print(m_servoEnd);
    // Serial.print(", m_currStep=");
    // Serial.print(m_currStep);

    if (m_endReached)
    {
        // do not accept new move parameters
        // Serial.println(", end reached, return");
        return;
    }

    unsigned int servoPosition;
    if (m_up)
    {
        servoPosition = m_servoStart - m_currStep;
    }
    else
    {
        servoPosition = m_servoEnd + m_currStep;
    }

    // Serial.print(", up=");
    // Serial.print(m_up);
    // Serial.print(", servoPosition=");
    // Serial.println(servoPosition);

    if (m_servoPosition != servoPosition)
    {
        // move the servo only when the servoPosition has changed
        if (m_servoPosition != servoPosition)
        {
            // if too fast, then the end position was not yet reached and then it goes to the other direction without completing the move
            m_servoDriver->setPWM(m_servoNumber, 0, servoPosition);
            // unsigned long now = millis();
            // if (now - m_lastStep < MIN_STEP) {
            //     //  Serial.print("minStep=");
            //     //  Serial.println(now - m_lastStep);
            //     delay(9);
            //     m_lastStep  = now;
            // }
        }
        m_servoPosition = servoPosition;
    }
    if (m_delayTime != 0)
    {
        delay(m_delayTime);
    }
    m_currStep += m_stepSize;

    if (m_currStep > m_steps)
    {
        // movement is completed
        m_endReached = true;
    }
    // Serial.println("Servo::Move() OUT");
}

/**
 * Return true if the end of the loop movement has been reached
 * If true means that new move params can be accepted.
 */
boolean Servo::isMoveCompleted()
{
    return m_endReached;
}

/**
 * Control Servo Move
 * Move directly from start to end without yield.
 * @param speed of the servo movement (0: slow, 100:highest speed)
 * @param start position , must be between SERVOMIN and SERVOMAX
 * @param end   position , must be between SERVOMIN and SERVOMAX
 */
void Servo::servoMove(unsigned int speed, unsigned int start, unsigned int end)
{
    unsigned int delayTime = 500 - (speed * 5);

    bool up;
    int nStart;
    int nEnd;
    if (start < end)
    {
        // move up
        up = true;
        nStart = start;
        nEnd = end;
    }
    else
    {
        // move down
        up = false;
        nStart = end;
        nEnd = start;
    }

    int pos;
    int steps = nEnd - nStart;

    // complete the move, no yield
    for (int i = 0; i <= steps; i++)
    {
        if (up)
        {
            pos = nEnd - i;
        }
        else
        {
            pos = nStart + i;
        }

        m_servoDriver->setPWM(m_servoNumber, 0, pos);
        if (delayTime != 0)
        {
            delay(delayTime);
        }
    }
}

/**
 * Control Servo Move with relative position from 0%...100%
 * @param speed    of the servo movement (0: slow, 100:highest speed)
 * @param start.   from 0...100%
 * @param end.     from 0...100%
 * y=mx + n
 * m=(END-START)/100%
 * servoPos = (END-START)/100% * valueIn + START
 */
void Servo::servoMoveRel(unsigned int speed, unsigned int start, unsigned int end)
{
    unsigned int delayTime = 500 - (speed * 5);

    bool up;
    int nStart;
    int nEnd;
    if (start < end)
    {
        // move up
        up = true;
        nStart = start;
        nEnd = end;
    }
    else
    {
        // move down
        up = false;
        nStart = end;
        nEnd = start;
    }

    nStart = int(m_servoFactor * nStart + SERVOMIN);
    nEnd = int(m_servoFactor * nEnd + SERVOMIN);

    int pos;
    int steps = nEnd - nStart;

    // complete the move, no yield
    for (int i = 0; i <= steps; i++)
    {

        if (up)
        {
            pos = nEnd - i;
        }
        else
        {
            pos = nStart + i;
        }

        // m_digits.show(pos);
        m_servoDriver->setPWM(m_servoNumber, 0, pos);
        if (delayTime != 0)
        {
            delay(delayTime);
        }
    }
}

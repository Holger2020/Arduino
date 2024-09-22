#include <Arduino.h>
#include <../lib/leg.h>
#include <../lib/servo.h>
#include <../lib/boardPins.h>
#include <Adafruit_PWMServoDriver.h>

/**
 * A leg
 */

/**
 * Default Constructor
 */
Leg::Leg()
{
    Serial.println("Leg() Default  Constructor");
}

/**
 * Constructor
 */
Leg::Leg(Adafruit_PWMServoDriver *servoDriver, unsigned int legNumber, unsigned int servoHip, unsigned int servoKnee, unsigned int servoFoot)
{
    // Serial.println("Leg::Leg() IN");
    init(servoDriver, legNumber, servoHip, servoKnee, servoFoot);
    // Serial.println("Leg::Leg() OUT");
}

/**
 * Initialize leg
 */
void Leg::init(Adafruit_PWMServoDriver *servoDriver, unsigned int legNumber, unsigned int servoHip, unsigned int servoKnee, unsigned int servoFoot)
{
    m_legNumber = legNumber;
    m_servoNumberHip = servoHip;
    m_servoNumberKnee = servoKnee;
    m_servoNumberFoot = servoFoot;
    m_moveData = MoveDatax{0, 0, 0};
    // m_moveData = MoveDatax();
    // m_moveData.hip = 0;
    // m_moveData.knee = 0;
    // m_moveData.foot = 0;

    // Serial.print("Leg::init() IN: nHip=");
    // Serial.print(m_servoNumberHip);
    // Serial.print(", nKnee=");
    // Serial.print(m_servoNumberKnee);
    // Serial.print(", nFoot=");
    // Serial.print(m_servoNumberFoot);
    // Serial.print(", legNumber=");
    // Serial.print(m_legNumber);

    if (m_servoNumberHip != SERVO_NONE)
    {
        m_servoHip = new Servo(servoDriver, m_servoNumberHip);
        m_servoHip->servoHome();
    }
    if (m_servoNumberKnee != SERVO_NONE)
    {
        m_servoKnee = new Servo(servoDriver, m_servoNumberKnee);
        m_servoKnee->servoHome();
    }
    if (m_servoNumberFoot != SERVO_NONE)
    {
        m_servoFoot = new Servo(servoDriver, m_servoNumberFoot);
        m_servoFoot->servoHome();
    }

    // Serial.print(", servoHipAdr=");
    // Serial.print((uintptr_t)m_servoHip, HEX);
    // Serial.print(", servoKneeAdr=");
    // Serial.print((uintptr_t)m_servoKnee, HEX);
    // Serial.print(", servoFootAdr=");
    // Serial.print((uintptr_t)m_servoFoot, HEX);
    // Serial.print(", legAdr=");
    // Serial.println((uintptr_t)this, HEX);
    // Serial.println("Leg::init() OUT");
}

/**
 * Initiate a move, i.e. all three servos are initialized with their move data: speed, start, stop.
 * @param moveData array of three tupels. Each tupel has [speed, pos] data for hip, knee, foot.
 * Example: hip[speed,pos], knee[speed,pos], foot[speed,pos] --> 6 consecutive values in the array
 */
void Leg::initMovexxx(unsigned int moveData[])
{
    // Serial.print("Leg::initMove() IN: nHip=");
    // Serial.print(m_servoNumberHip);
    // Serial.print(", nKnee=");
    // Serial.print(m_servoNumberKnee);
    // Serial.print(", nFoot=");
    // Serial.print(m_servoNumberFoot);
    // Serial.print(", legAdr=");
    // Serial.println((uintptr_t)this, HEX);

    if (m_servoNumberHip != SERVO_NONE)
    {
        m_servoHip->initMove(moveData[0], moveData[1]);
    }
    if (m_servoNumberKnee != SERVO_NONE)
    {
        m_servoKnee->initMove(moveData[2], moveData[3]);
    }
    if (m_servoNumberFoot != SERVO_NONE)
    {
        m_servoFoot->initMove(moveData[4], moveData[5]);
    }

    // Serial.print(", servoHip=");
    // Serial.print((uintptr_t)m_servoHip, HEX);
    // Serial.print(", servoKnee=");
    // Serial.println((uintptr_t)m_servoKnee, HEX);
    // Serial.print(", servoFoot=");
    // Serial.println((uintptr_t)m_servoFoot, HEX);
    // Serial.println("Leg::initMove() OUT");
}

/**
 * Initiate a move, i.e. all three servos are initialized with their move data: speed, start, stop.
 * @param moveData array of three tupels. Each tupel has [speed, pos] data for hip, knee, foot.
 * Example: hip[speed,pos], knee[speed,pos], foot[speed,pos] --> 6 consecutive values in the array
 * @param startPos take the next 6 values from the moveData array
 */
void Leg::initMove(unsigned int moveData[], unsigned int startPos)
{
    // Serial.print("Leg::initMove() IN: nHip=");
    // Serial.print(m_servoNumberHip);
    // Serial.print(", nKnee=");
    // Serial.print(m_servoNumberKnee);
    // Serial.print(", nFoot=");
    // Serial.print(m_servoNumberFoot);
    // Serial.print(", legAdr=");
    // Serial.println((uintptr_t)this, HEX);

    startPos = 6 * startPos; // start position of the data for this move
    if (m_servoNumberHip != SERVO_NONE)
    {
        m_servoHip->initMove(moveData[startPos + 0], moveData[startPos + 1]);
        m_moveData.hip = moveData[startPos + 1];
        // m_servoPosition = moveData[startPos + 1];
    }
    if (m_servoNumberKnee != SERVO_NONE)
    {
        m_servoKnee->initMove(moveData[startPos + 2], moveData[startPos + 3]);
        m_moveData.knee = moveData[startPos + 3];
        // m_servoPosition = moveData[startPos + 3];
    }
    if (m_servoNumberFoot != SERVO_NONE)
    {
        m_servoFoot->initMove(moveData[startPos + 4], moveData[startPos + 5]);
        m_moveData.foot = moveData[startPos + 5];
        // m_servoPosition = moveData[startPos + 5];
    }

    // Serial.print(", servoHip=");
    // Serial.print((uintptr_t)m_servoHip, HEX);
    // Serial.print(", servoKnee=");
    // Serial.println((uintptr_t)m_servoKnee, HEX);
    // Serial.print(", servoFoot=");
    // Serial.println((uintptr_t)m_servoFoot, HEX);
    // Serial.println("Leg::initMove() OUT");
}

/**
 * Return true if all servos have completed their moves
 */
boolean Leg::isMoveCompleted()
{
    boolean completed = true;
    if (m_servoNumberHip != SERVO_NONE)
    {
        completed &= m_servoHip->isMoveCompleted();
    }
    if (!completed)
    {
        return false;
    }
    if (m_servoNumberKnee != SERVO_NONE)
    {
        completed &= m_servoKnee->isMoveCompleted();
    }
    if (!completed)
    {
        return false;
    }
    if (m_servoNumberFoot != SERVO_NONE)
    {
        completed &= m_servoFoot->isMoveCompleted();
    }
    return completed;
}

/**
 * Return true if all servos have completed their moves
 */
void Leg::move()
{
    if (m_servoNumberHip != SERVO_NONE)
    {
        m_servoHip->move();
    }
    if (m_servoNumberKnee != SERVO_NONE)
    {
        m_servoKnee->move();
    }
    if (m_servoNumberFoot != SERVO_NONE)
    {
        m_servoFoot->move();
    }
}

/**
 * Get the target servo position of the hip server
 */
MoveDatax Leg::getMoveData()
{
    return m_moveData;
}

/**
 * Get the target servo position of the hip server
 */
// unsigned int Leg::getServoPosition() {
//     return m_servoPosition;
// }

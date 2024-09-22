#include <Arduino.h>
#include <Wire.h>
#include <../lib/leg.h>
#include <../lib/move.h>
#include <../lib/moveData.h>

// #define SPEED 20
// #define FORWARD_STEPS 2
// #define BACKWARDS_STEPS 2

/**
 * Move legs
 */

/**
 * Hip range: 20...50%
 */
// unsigned int m_moveDataForward[] =
//     {SPEED, 20,  // hip: move 0
//      SPEED, 50,  // knee
//      SPEED, 0,   // foot
//      SPEED, 50,  // hip: move 1
//      SPEED, 70,  // knee
//      SPEED, 50}; // foot

// unsigned int m_moveDataBackwards[] =
//     {SPEED, 50,  // hip: move 0
//      SPEED, 70,  // knee
//      SPEED, 50,  // foot
//      SPEED, 20,  // hip: move 1
//      SPEED, 50,  // knee
//      SPEED, 0}; // foot

/**
 * Default Constructor
 */
Move::Move()
{
    Serial.println("Move() Default Constructor");
}

/**
 * Constructor
 */
Move::Move(Leg *leg)
{
    // Serial.println("Move() IN");
    init(leg);
    // Serial.println("Move() OUT");
}

/**
 * Initialize
 */
void Move::init(Leg *leg)
{
    m_leg = leg;
    m_isMovingForward = false;
    m_isMovingBackwards = false;
    m_isForwardCompleted = false;
    m_isBackwardsCompleted = false;
    m_forwardCounter = 0;
    m_backwardsCounter = 0;
}

/**
 * Initialized forward move
 */
void Move::forwardInit()
{
    Serial.print("Move::forwardInit() IN: m_forwardCounter=");
    Serial.println(m_forwardCounter);

    m_isMovingForward = true;
    m_leg->initMove(m_moveDataForward, m_forwardCounter);
    m_forwardCounter++;
    if (m_forwardCounter == FORWARD_STEPS)
    {
        m_forwardCounter = 0;
        m_isMovingForward = false;
        m_isForwardCompleted = true;
    }
    Serial.println("Move::forwardInit() OUT");
}

/**
 * Initialized backwards move
 */
void Move::backwardsInit()
{
    Serial.print("Move::backwardsInit() IN: m_backwardsCounter=");
    Serial.println(m_backwardsCounter);
    // unsigned int moveData[] = {SPEED, 60, 50,
    //                            SPEED, 70, 60,
    //                            SPEED, 50, 0};
    // m_leg->initMove(moveData);

    m_isMovingBackwards = true;
    m_leg->initMove(m_moveDataBackwards, m_backwardsCounter);
    m_backwardsCounter++;
    if (m_backwardsCounter == FORWARD_STEPS)
    {
        m_backwardsCounter = 0;
        m_isMovingBackwards = false;
        m_isBackwardsCompleted = true;
    }
    Serial.println("Move::backwardsInit() OUT");
}

/**
 * Incremental Move
 * Yield after each incremental step.
 */
void Move::move()
{
    m_leg->move();
}

/**
 * Return true if the move has been completed
 */
boolean Move::isMoveCompleted()
{
    return m_leg->isMoveCompleted();
}

/**
 * Return true if the forward movement has been completed
 */
boolean Move::isForwardCompleted()
{
    return m_isForwardCompleted;
}

/**
 * Return true if the backwards movement has been completed
 */
boolean Move::isBackwardsCompleted()
{
    return m_isBackwardsCompleted;
}

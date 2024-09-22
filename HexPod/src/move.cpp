#include <Arduino.h>
#include <Wire.h>
#include <../lib/leg.h>
#include <../lib/move.h>
#include <../lib/moveData.h>

/**
 * Move legs
 */

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
    m_isNoMove = true;
    m_forwardCounter = 0;
    m_backwardsCounter = 0;
    m_moveCounter;
}

/**
 * Initialized forward move
 */
void Move::forwardInit()
{
    Serial.print("Move::forwardInit() IN: m_forwardCounter=");
    Serial.println(m_forwardCounter);

    if (FORWARD_STEPS == 0)
    {
        m_isNoMove = true;
        Serial.println("Move::backwardsInit(): no move, return");
        return;
    }
    m_isNoMove = false;
    m_isMovingForward = true;
    m_leg->initMove(m_moveDataForward, m_forwardCounter);
    m_moveCounter = m_forwardCounter;
    m_forwardCounter++;
    if (m_forwardCounter == FORWARD_STEPS)
    {
        // Serial.print("Move::forwardInit(): m_forwardCounter=");
        // Serial.println(m_forwardCounter);
        m_forwardCounter = 0;
        m_isMovingForward = false;
        m_isForwardCompleted = true;
    }
    else
    {
        m_isForwardCompleted = false;
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

    if (BACKWARDS_STEPS == 0)
    {
        m_isNoMove = true;
        Serial.println("Move::backwardsInit(): no move, return");
        return;
    }

    m_isNoMove = false;
    m_isMovingBackwards = true;
    m_leg->initMove(m_moveDataBackwards, m_backwardsCounter);
    m_moveCounter = -1 * m_backwardsCounter - 1; // make -1 from 0 to indicate backwards move
    m_backwardsCounter++;
    if (m_backwardsCounter == BACKWARDS_STEPS)
    {
        // Serial.print("Move::backwardsInit(): m_backwardsCounter=");
        // Serial.println(m_backwardsCounter);
        m_backwardsCounter = 0;
        m_isMovingBackwards = false;
        m_isBackwardsCompleted = true;
    }
    else
    {
        m_isBackwardsCompleted = false;
    }
    Serial.println("Move::backwardsInit() OUT");
}

/**
 * Incremental Move
 * Yield after each incremental step.
 */
void Move::move()
{
    if (m_isNoMove)
    {
        return;
    }
    m_leg->move();
}

/**
 * Return true if the move has been completed
 */
boolean Move::isMoveCompleted()
{
    if (m_isNoMove)
    {
        return true;
    }
    return m_leg->isMoveCompleted();
}

/**
 * Return true if the forward movement has been completed
 */
boolean Move::isForwardCompleted()
{
    if (m_isNoMove)
    {
        return true;
    }
    return m_isForwardCompleted;
}

/**
 * Return true if the backwards movement has been completed
 */
boolean Move::isBackwardsCompleted()
{
    if (m_isNoMove)
    {
        return true;
    }
    return m_isBackwardsCompleted;
}

/**
 * Get the moveData of the current move
 */
MoveDatax Move::getMoveData()
{
    if (m_isNoMove)
    {
        return MoveDatax{0, 0, 0};
    }
    return m_leg->getMoveData();
}

/**
 * Get the target servo position of the hip server
 */
// unsigned int Move::getServoPosition()
// {
//     return m_leg->getServoPosition();
// }

/**
 * Get the current move counter.
 * Is forward moving: return the  number of the move, e.g. 0,1,2,3,...
 * Is backwards moving: return the  number of the move plus 10, e.g. 10,11,12,13 (1 indicates backwards)
 */
int Move::getMoveCounter()
{
    // if (m_isMovingForward)
    // {
    //     return (m_forwardCounter == 0) ? 0 : m_forwardCounter - 1;
    // }
    // else
    // {
    //     return (m_backwardsCounter == 0) ? 10 : m_backwardsCounter - 1 + 10;
    //     // return m_backwardsCounter + 10;
    // }
    return m_moveCounter;
}

// Simulated 8-digit display (for simplicity we will use an array of characters)
// std::array<char, 8> display = {'_', '_', '_', '_', '_', '_', '_', '_'};

// Function to update the display at a given digit position
// void updateDisplay(int digit_position, unsigned int value) {
//     // Check that digit_position is valid (0 to 3) and value is less than 100
//     if (digit_position < 0 || digit_position > 3 || value >= 100) {
//         std::cerr << "Invalid input" << std::endl;
//         return;
//     }

//     // Calculate the starting position on the display for this digit pair
//     int start_pos = digit_position * 2;

//     // Split the value into two digits
//     int tens = value / 10;
//     int ones = value % 10;

//     // Update the display array
//     display[start_pos] = '0' + tens;  // Convert digit to corresponding character
//     display[start_pos + 1] = '0' + ones;

//     // Output the updated display (optional)
//     for (char digit : display) {
//         std::cout << digit;
//     }
//     std::cout << std::endl;
// }

// int main() {
//     // Test cases
//     updateDisplay(0, 45);  // Shows 45 at position 0 (first two digits)
//     updateDisplay(1, 99);  // Shows 99 at position 1 (third and fourth digits)
//     updateDisplay(2, 12);  // Shows 12 at position 2 (fifth and sixth digits)
//     updateDisplay(3, 78);  // Shows 78 at position 3 (seventh and eighth digits)

//     return 0;
// }

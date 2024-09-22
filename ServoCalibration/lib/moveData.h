#ifndef MOVEDATA_H
#define MOVEDATA_H

/**
 * Move data for leg movements
 */

#define SPEED 100
#define FORWARD_STEPS 4
#define BACKWARDS_STEPS 2

unsigned int hipStart = 40;
unsigned int hipEnd = 50;

/**
 * Hip range: 20...50%
 */
unsigned int m_moveDataForward[] =
    {SPEED, 40,  // hip: move 0
     SPEED, 30,  // knee
     SPEED, 0,   // foot
     SPEED, 20,  // hip: move 0
     SPEED, 20,  // knee
     SPEED, 0,   // foot
     SPEED, 30,  // hip: move 0
     SPEED, 40,  // knee
     SPEED, 0,   // foot
     SPEED, 50,  // hip: move 1
     SPEED, 70,  // knee
     SPEED, 50}; // foot

unsigned int m_moveDataBackwards[] =
    {SPEED, 50,  // hip: move 0
     SPEED, 70,  // knee
     SPEED, 50,  // foot
     SPEED, 40,  // hip: move 1
     SPEED, 30,  // knee
     SPEED, 0}; // foot

#endif
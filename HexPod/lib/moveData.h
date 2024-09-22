#ifndef MOVEDATA_H
#define MOVEDATA_H

/**
 * Move data for leg movements
 */

#define SPEED 100
#define FORWARD_STEPS 4
#define BACKWARDS_STEPS 0

unsigned int hipStart = 40;
unsigned int hipEnd = 50;

/**
 * Hip range: 40...60%
 */
unsigned int m_moveDataForward[] =
    {
        100, 40,   // hip: move 0   nach vorne
        100, 30,   // knee
        90, 20,   // foot
        100, 70,    // hip: move 1  knie runter, fuss nach vorne
        SPEED, 30, // knee
        90, 80,    // foot

        SPEED, 70, // hip: move 2   knie hoch
        100, 50, // knee
        90, 80, // foot
        100, 40, // hip: move 3
        100, 50, // knee
        90, 20
    }; // foot

unsigned int m_moveDataBackwards[] =
    {
        100, 100, // hip: move 0
        100, 100, // knee
        100, 100  // foot
}; // end
//  100, 68,  // hip: move 1
//  100, 68,  // knee
//  100, 88, // foot
//  100, 47,  // hip: move 2
//  100, 37,  // knee
//  100, 87, // foot
//  100, 66,  // hip: move 3
//  100, 86,  // knee
//  100, 86, // foot
//  100, 45,  // hip: move 4
//  100, 25,  // knee
//  100, 85, // foot
//  100, 64,  // hip: move 5
//  100, 84,  // knee
//  100, 44, // foot
//  100, 43,  // hip: move 6
//  100, 53,  // knee
//  100, 83
//  }; // foot

#endif
#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include <../lib/defs.h>
#include <../lib/leg.h>

/**
 * Move legs
 */
class Move
{
private:
    Leg *m_leg;
    boolean m_isMovingForward;
    boolean m_isMovingBackwards;
    boolean m_isForwardCompleted;
    boolean m_isBackwardsCompleted;
    boolean m_isNoMove;
    unsigned int m_forwardCounter;
    unsigned int m_backwardsCounter;
    int m_moveCounter;  // -9 ... 9 current move position, -1 is negative 0
    void init(Leg *leg);

public:
    Move(); // Default constructor
    Move(Leg *leg);
    void forwardInit();
    void backwardsInit();
    void move();
    boolean isMoveCompleted();
    boolean isForwardCompleted();
    boolean isBackwardsCompleted();
    MoveDatax getMoveData();
    int getMoveCounter();
};

#endif
#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include <../lib/leg.h>

/**
 * Move legs
 */
class Move
{
private:
    Leg* m_leg;
    boolean m_isMovingForward;
    boolean m_isMovingBackwards;
    boolean m_isForwardCompleted;
    boolean m_isBackwardsCompleted;
    unsigned int m_forwardCounter;
    unsigned int m_backwardsCounter;
    void init(Leg* leg);

public:
    Move(); // Default constructor
    Move(Leg* leg);
    void forwardInit();
    void backwardsInit();
    void move();
    boolean isMoveCompleted();
    boolean isForwardCompleted();
    boolean isBackwardsCompleted();
};

#endif
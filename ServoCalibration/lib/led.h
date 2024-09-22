#ifndef LED_H
#define LED_H

// #include <../lib/boardPins.h>

class Led
{
private:
    unsigned int m_pinNumber{0};
    unsigned int m_timeOn;
    unsigned int m_timeOff;
    unsigned long int m_timestamp;
    boolean m_enabled = true;
    enum
    {
        AUS,
        EIN
    } m_state;


public:
    Led(); // Default constructor
    Led(unsigned int pinNumber);
    void init(unsigned int pinNumber);
    void blinkLed();
    void activate(boolean active);
    void enable(boolean enable);
    void setTimeOnOff(unsigned int timeOn, unsigned int timeOff);
};

#endif
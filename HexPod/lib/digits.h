#ifndef DIGITS_H
#define DIGITS_H

#include <LedControl.h>

class Digits
{
private:
    LedControl m_lc = LedControl(0, 0, 0, 0);
    void init();

public:
    Digits(); 
    Digits(int dataPin, int clkPin, int csPin);
    void clear();
    void show(byte digit7, byte digit6, byte digit5, byte digit4, byte digit3, byte digit2, byte digit1, byte digit0);
    void show(byte position, byte digit);
    void show(unsigned long number);
    void showAtPosition(unsigned int position, unsigned int value);
    void showAtPositionNeg(unsigned int position, int value);
};

#endif
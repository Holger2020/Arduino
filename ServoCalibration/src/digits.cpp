#include <Arduino.h>
#include <LedControl.h>
#include <../lib/digits.h>

/**
 * 7 Digits Display
 */

/**
 * Constructor
 * Params:
 * dataPin		pin on the Arduino where data gets shifted out
 * clockPin		pin for the clock
 * csPin		pin for selecting the device
 */
Digits::Digits()
{
}

/**
 * Constructor
 * Params:
 * dataPin		pin on the Arduino where data gets shifted out
 * clockPin		pin for the clock
 * csPin		pin for selecting the device
 */
Digits::Digits(int dataPin, int clkPin, int csPin)
{
    m_lc = LedControl(dataPin, clkPin, csPin, 1);
    init();
}

/**
 * Initialize digits
 */
void Digits::init()
{
    //The MAX72XX is in power-saving mode on startup
    m_lc.shutdown(0, false);
    m_lc.setIntensity(0, 8);  // brightness
    m_lc.clearDisplay(0);
}

/**
 * Show digits
 */
void Digits::show(byte digit7, byte digit6, byte digit5, byte digit4, byte digit3, byte digit2, byte digit1, byte digit0)
{
    m_lc.setDigit(0, 0, digit7, false);
    m_lc.setDigit(0, 1, digit6, false);
    m_lc.setDigit(0, 2, digit5, false);
    m_lc.setDigit(0, 3, digit4, false);
    m_lc.setDigit(0, 4, digit3, false);
    m_lc.setDigit(0, 5, digit2, false);
    m_lc.setDigit(0, 6, digit1, false);
    m_lc.setDigit(0, 7, digit0, false);
}

/**
 * Show a specific digit
 * @param position 0...7, position 0 is most right
 * @param digit 0...9
 */
void Digits::show(byte position, byte digit)
{
    m_lc.setDigit(0, position, digit, false);
}

/**
 * Show a specific digit
 */
void Digits::show(unsigned long number)
{
    // Extract digits from right to left
    for (int i = 7; i >= 0; i--)
    {
        int digit = number % 10; // Get the rightmost digit
        m_lc.setDigit(0, 7 - i, (byte)digit, false);
        number /= 10; // Remove the rightmost digit
    }
}

// Test digits:

//     m_digits.show(0, 0, 0, 0, 0, 0, 0, 0);
//     delay(1000);
//     m_digits.show(9,9,9,9,9,9,9,9);
// delay(waitTimer);
// m_digits.show(6, 5, 4, 3, 2, 1, 0, 7);
// delay(waitTimer);
// m_digits.show(5, 4, 3, 2, 1, 0, 7, 6);
// delay(waitTimer);
// m_digits.show(4, 3, 2, 1, 0, 7, 6, 5);
// delay(waitTimer);
// m_digits.show(3, 2, 1, 0, 7, 6, 5, 4);
// delay(waitTimer);
// m_digits.show(2, 1, 0, 7, 6, 5, 4, 3);
// delay(waitTimer);
// m_digits.show(1, 0, 7, 6, 5, 4, 3, 2);
// delay(waitTimer);
// m_digits.show(0, 7, 6, 5, 4, 3, 2, 1);
// delay(waitTimer);
// m_digits.show(7, 6, 5, 4, 3, 2, 1, 0);
// delay(waitTimer);

// m_digits.show(0,9);
// delay(waitTimer);
// m_digits.show(123);
// delay(waitTimer);
// m_digits.show(1234);
// delay(waitTimer);
// m_digits.show(123456);
// delay(waitTimer);
// m_digits.show(1234567);
// delay(waitTimer);
// m_digits.show(12345678);

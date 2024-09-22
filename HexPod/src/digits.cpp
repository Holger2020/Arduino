#include <Arduino.h>
#include <LedControl.h>
#include <../lib/digits.h>

/**
 * 7 Digits Display
 */

// representation of the 8 7-digit displays
// char display[8];

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
    // The MAX72XX is in power-saving mode on startup
    m_lc.shutdown(0, false);
    m_lc.setIntensity(0, 8); // brightness
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
 * @param digit 0...0xF (hex value)
 */
void Digits::show(byte position, byte digit)
{
    m_lc.setDigit(0, position, digit, false);
}

/**
 * Clear the display with '--------'
 */
void Digits::clear()
{
    for (int i = 0; i < 8; i++)
    {
        // display[i] = '-';  // Represent empty with '-'
        // m_lc.setDigit(0, i, 0, false);
        m_lc.setChar(0, i, '-', false);
    }
}

/**
 * Show the long number on all 8 digits
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

/**
 * Display a 2-digit number at a given position on the 7-digit display
 *
 * @param position is 3...0: Digit: '88.88.88.88' (position 0 is most right)
 *
 * Note: the value 100 is shown as 99, the value 99 is also shown as 99.
 *
 */
void Digits::showAtPosition(unsigned int position, unsigned int value)
{
    // Calculate the starting index on the display
    unsigned int start_index = position << 1;

    // Check display value
    if (value == 100)
    {
        value = 99; // show 99 instead of 100 (for 100% values)
    }
    else if (value >= 100)
    {
        // invalid value, show 'FF'
        m_lc.setChar(0, start_index, 'F', true);
        m_lc.setChar(0, start_index + 1, 'F', false);
        return;
    }

    // Ensure digit_position is between 0 and 3 (since only 4 positions available)
    if (position > 3)
    {
        return; // Invalid position
    }

    // Extract the tens and ones place digits
    unsigned int tens = value / 10;
    unsigned int ones = value % 10;

    // Place the tens and ones digits on the display
    m_lc.setChar(0, start_index, ones + '0', true);
    m_lc.setChar(0, start_index + 1, tens + '0', false);
}

/**
 * Display a 1-digit number at a given position on the 7-digit display
 *
 * @param position is 3...0: Digit: '88.88.88.88' (position 0 is most right)
 *
 * Note: the value 9 is shown as ' 9', the value -9 is also shown as '-9'
 *
 */
void Digits::showAtPositionNeg(unsigned int position, int value)
{
    // Calculate the starting index on the display
    unsigned int start_index = position << 1;

    // Check display value
    if (value > 9)
    {
        // invalid value, show 'FF'
        m_lc.setChar(0, start_index, ' ', true);
        m_lc.setChar(0, start_index + 1, 'F', false);
        return;
    }
    else if (value < -9)
    {
        // invalid value, show 'FF'
        m_lc.setChar(0, start_index, '-', true);
        m_lc.setChar(0, start_index + 1, 'F', false);
        return;
    }

    // Ensure digit_position is between 0 and 3 (since only 4 positions available)
    if (position > 3)
    {
        return; // Invalid position
    }

    // Extract the tens and ones place digits
    // unsigned int tens = value / 10;
    // unsigned int ones = value % 10;

    // Show the single digit value and sign 
    if (value >= 0)
    {
        m_lc.setChar(0, start_index, value + '0', true);
        m_lc.setChar(0, start_index + 1, ' ', false);
    }
    else
    {
        value = -1 * value -1; // -1: 0, -2: 1
        m_lc.setChar(0, start_index, value + '0', true);
        m_lc.setChar(0, start_index + 1, '-', false);
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

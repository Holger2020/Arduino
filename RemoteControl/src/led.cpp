#include <Arduino.h>
#include <../lib/led.h>
#include <../lib/boardPins.h>

/**
 * A single LED
 */

// default blink time 1sec-1sec
#define BLINK_TIME_OFF 1000
#define BLINK_TIME_ON 1000

/**
 * Default Constructor
 */
Led::Led() : m_pinNumber{LED_RED}
{
    m_state = AUS;
    m_timestamp = 0;
}

/**
 * Constructor
 */
Led::Led(unsigned int pinNumber) : m_pinNumber{pinNumber}
{
    init(m_pinNumber);
}

/**
 * Initialize Led
 */
void Led::init(unsigned int pinNumber)
{
    m_pinNumber = pinNumber;
    m_state = AUS;
    m_timestamp = 0;
    m_timeOn = BLINK_TIME_ON;
    m_timeOff = BLINK_TIME_OFF;
    pinMode(m_pinNumber, OUTPUT);
    digitalWrite(m_pinNumber, LOW); 
}

void Led::setTimeOnOff(unsigned int timeOn, unsigned int timeOff) {
    m_timeOn = timeOn;
    m_timeOff = timeOff;
}

/**
 * Switch LED permanently on/off
 */
void Led::activate(boolean active)
{
    if (!m_enabled) {
        return;
    }
    digitalWrite(m_pinNumber, active?HIGH:LOW); 
}

/**
 * Switch LED permanently on/off
 */
void Led::enable(boolean enable)
{
  m_enabled = enable;    
}

/**
 * Blink LED
 */
void Led::blinkLed()
{
        if (!m_enabled) {
        return;
    }
    switch (m_state)
    {
    case AUS:
        if (millis() - m_timestamp >= m_timeOff) // Bedingung: 100 ms später
        {
            digitalWrite(m_pinNumber, HIGH); // turn the LED on (HIGH is the voltage level)

            m_timestamp = millis();
            m_state = EIN; // Neuer Zustand: EIN
        }
        break;

    case EIN:
        if (millis() - m_timestamp >= m_timeOn) // Bedingung: 100 ms später
        {
            digitalWrite(m_pinNumber, LOW); // turn the LED on (HIGH is the voltage level)

            m_timestamp = millis();
            m_state = AUS; // Neuer Zustand: AUS
        }
        break;
    }
}

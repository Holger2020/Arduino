#include <Arduino.h>
// #include <../lib/button.h>
#include <button.h>

/**
 * A button
 */

/**
 * Constructor
 */
Button::Button(unsigned int buttonPin)
{
    m_buttonPin = buttonPin;
    m_buttonState = false;

    // initialize the button pin as an input
    pinMode(m_buttonPin, INPUT);
}

/**
 * Return true if the button is pressed
 */
bool Button::isButtonPressed()
{
    // read the state of the button value
    int buttonState = digitalRead(m_buttonPin);

    // return true if the button is pressed
    return (buttonState == HIGH);
}

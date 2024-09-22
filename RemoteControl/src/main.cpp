#include <Arduino.h>
#include <../lib/led.h>
#include <../lib/digits.h>
#include <../lib/boardPins.h>

// int i = 0;
Led *m_ledRed = nullptr;    
Led *m_ledYellow = nullptr; 
Led *m_ledGreen = nullptr;  
Digits m_digits = Digits(DIGIT_DATA_PIN, DIGIT_CLOCK_PIN, DIGIT_CS_PIN);
// Button m_button = Button(BUTTON);
boolean m_doDelay = false;

/**
 * Setup
 */
void setup()
{
    Serial.begin(9600);
    Serial.println("");
    Serial.println("#####################");
    Serial.println("###  Start Main 1 ####");
    Serial.println("#####################");

    // initialize digital pin LED_BUILTIN as an output.
    // pinMode(LED_BUILTIN, OUTPUT);
    // pinMode(LED_RED, OUTPUT);
    // pinMode(LED_YELLOW, OUTPUT);
    // pinMode(LED_GREEN, OUTPUT);

    m_ledRed = new Led(LED_RED);
    m_ledGreen = new Led(LED_GREEN);
    m_ledYellow = new Led(LED_YELLOW);

    m_ledRed->enable(true);
    m_ledYellow->enable(true);
    m_ledGreen->enable(true);

    m_ledRed->activate(true);
    m_ledYellow->activate(true);
    m_ledGreen->activate(true);
    delay(500);
    m_ledRed->activate(false);
    m_ledYellow->activate(false);
    m_ledGreen->activate(false);
    // delay(00);

    // m_ledRed->setTimeOnOff(500, 2000);
    // m_ledYellow->setTimeOnOff(2000, 500);
    // m_ledGreen->setTimeOnOff(5000, 1000);

    // m_digits.show(7, 6, 5, 4, 3, 2, 1, 0);
    // delay(1000);
    // m_digits.show(6, 5, 4, 3, 2, 1, 0, 7);
    // delay(1000);
    // m_digits.show(5, 4, 3, 2, 1, 0, 7, 6);
    // delay(1000);
    // m_digits.show(4, 3, 2, 1, 0, 7, 6, 5);
    // delay(1000);
    // m_digits.show(3, 2, 1, 0, 7, 6, 5, 4);
    // delay(1000);
    // m_digits.show(2, 1, 0, 7, 6, 5, 4, 3);
    // delay(1000);
    // m_digits.show(1, 0, 7, 6, 5, 4, 3, 2);
    // delay(1000);
    // m_digits.show(0, 7, 6, 5, 4, 3, 2, 1);
    // delay(1000);
    // m_digits.show(7, 6, 5, 4, 3, 2, 1, 0);
    // delay(3000);
    m_digits.clear();
    // delay(3000);
    // m_digits.showAtPosition(0,100);
    // m_digits.showAtPosition(1,101);
    // m_digits.showAtPosition(2,56);
    // m_digits.showAtPosition(3,78);

    Serial.println("");
    Serial.println("#####################");
    Serial.println("###     OUT      ####");
    Serial.println("#####################");
    delay(2000);
} // setup()

/**
 * Main loop
 */
void loop()
{
    // Serial.print("Loop: i=");
    // Serial.println(i);

    // m_ledRed->blinkLed();
    // m_ledGreen->blinkLed();
    // m_ledYellow->blinkLed();
    // m_ledGreen->activate(true);
    // delay(50);
    // m_ledGreen->activate(false);

    // digitalWrite(LED_BUILTIN, LOW);
    // digitalWrite(LED_RED, LOW);
    // digitalWrite(LED_GREEN, LOW);
    // digitalWrite(LED_YELLOW, LOW);

    // console output
    // Serial.print("i=");
    // Serial.print(i);
    // Serial.println(".");
    // i++;
}

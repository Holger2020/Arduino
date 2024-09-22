#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
    unsigned int m_buttonPin;
    bool m_buttonState = false;
    
public:
    Button(unsigned int buttonPin);
    bool isButtonPressed();
};

#endif
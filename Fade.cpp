/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
#include "Fade.h"
#include "Arduino.h"

static int fadeAmount = FADE_AMOUNT;

/*Returns the brightness of the led at the next step, which is between the limits*/
int nextStep(int current)
{
    current += fadeAmount;
    if (current <= FADE_LIMIT_MIN || current >= FADE_LIMIT_MAX)
    {
        fadeAmount = -fadeAmount;
    }
    return current;
}

/*Sets the brigthness to the given amount to the connected led on the pin, given that the led supports PWM
Takes more than FADEDELAY (usually 5) milliseconds to execute to allow the fade to work*/
void setBrightness(int b, int pin_led)
{
    analogWrite(pin_led, b);
    unsigned long before = millis();
    unsigned long now;
    do
    {
        now = millis();
    } while (now - before < FADEDELAY);
}
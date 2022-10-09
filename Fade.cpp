#include <Fade.h>

int fadeAmount = FADE_AMOUNT;

/*Returns the brightness of the led at the next step, which is between the limits*/
int nextStep(int current)
{
    current += FADE_AMOUNT;
    if (current == FADE_LIMIT_MIN || current == FADE_LIMIT_MAX)
    {
        fadeAmount = -fadeAmount;
    }
    return current;
}

/*Sets the brigthness to the given amount to the connected led on the pin, given that the led supports PWM*/
void setBrightness(int b, int pin_led)
{
    analogWrite(pin_led, b);
}
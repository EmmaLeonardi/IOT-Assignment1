#ifndef FADE_H
#define FADE_H

// The step amount for the fading of a led
#define FADE_AMOUNT 10;

// The minumum brightness a led can take
#define FADE_LIMIT_MIN 0

// The maximum brightness a led can take
#define FADE_LIMIT_MAX 255

/*Returns the brightness of the led at the next step, which is between the limits*/
int nextStep(int current);

/*Sets the brigthness to the given amount to the connected led on the pin, given that the led supports PWM*/
void setBrightness(int b, int pin_led);

#endif
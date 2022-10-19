#ifndef FADE_H
#define FADE_H

// The step amount for the fading of a led
#define FADE_AMOUNT 5

// The minumum brightness a led can take
#define FADE_LIMIT_MIN 0

// The maximum brightness a led can take
#define FADE_LIMIT_MAX 255

//This constant is the amount of time in milliseconds needed to allow the fading of the led to be visible
#define FADEDELAY 6

/*Returns the brightness of the led at the next step, which is between the limits*/
int nextStep(int current);

/*Sets the brigthness to the given amount to the connected led on the pin, given that the led supports PWM
Takes more than FADEDELAY (usually 6) milliseconds to execute to allow the fade to work*/
void setBrightness(int b, int pin_led);

#endif
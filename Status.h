#ifndef STATUS_H
#define STATUS_H

/*Turns off all the leds in the led array, and sets the status accordingly*/
void turnAllOff(int *ledArray, bool *status, int SIZE);

/*Turns on all the leds in the led array, and sets the status accordingly*/
void turnAllOn(int *ledArray, bool *status, int SIZE);

/*Copies the pattern in the array to the status array*/
void setStatusAsGiven(bool *pattern, bool *status, int SIZE);

/*Turns on the led to the pin given for the time set */
void turnLedOnFor(int pinLed, int time);
#endif
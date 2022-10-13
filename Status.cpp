#include "Status.h"
#include "Arduino.h"

/*Turns off all the leds in the led array, and sets the status accordingly*/
void turnAllOff(int *ledArray, bool *status, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        digitalWrite(ledArray[i], LOW);
        status[i] = false;
    }
}

/*Turns on all the leds in the led array, and sets the status accordingly*/
void turnAllOn(int *ledArray, bool *status, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        digitalWrite(ledArray[i], HIGH);
        status[i] = true;
    }
}

/*Copies the pattern in the array to the status array*/
void setStatusAsGiven(bool *pattern, bool *status, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        status[i] = pattern[i];
    }
}
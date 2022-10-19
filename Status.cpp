/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
#include "Status.h"
#include "Arduino.h"
#include "Constants.h"

// This variable is used for timing, for turning leds on for a given time
unsigned long start;

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

/*Turns on the led to the pin given for the time set in seconds*/
void turnLedOnFor(int pinLed, int time)
{
    unsigned long start = millis();
    digitalWrite(pinLed, HIGH);
    unsigned long now = millis();
    while (now - start < time * MSECTOSEC)
    {
        now=millis();
    }
    digitalWrite(pinLed, LOW);
}
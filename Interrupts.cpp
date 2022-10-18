#define LIBCALL_ENABLEINTERRUPT
#include "Interrupts.h"
#include "Pins.h"
#include "Arduino.h"
#include <stdint.h>
// Used to query the Enable Interrupt library to ask what pin called the interrupt
#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>

// If interrupts come faster than this amount of ms, assume it's a bounce and ignore
#define DEBOUNCE 180

/*Interrupt handler, to play the game
Reads what button called the interrupt and turns on the relative led*/
void interruptLed()
{
    unsigned int i = getIndex(arduinoInterruptedPin);
    if (i != N)
    {
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        if (interrupt_time - last_interrupt_time > DEBOUNCE)
        {
            if (statusL[i] == false)
            {
                digitalWrite(LPins[i], HIGH);
                statusL[i] = true;
            }
            else
            {
                digitalWrite(LPins[i], LOW);
                statusL[i] = false;
            }
            last_interrupt_time = interrupt_time;
        }
    }
}

/*Finds the index of the pin given*/
unsigned int getIndex(unsigned int j)
{
    for (unsigned int i = 0; i < N; i++)
    {
        if (BPins[i] == (int) j)
        {
            return i;
        }
    }
    return N;
}

/*Interrupt handler, to start the game*/
void startGame()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        gameStarts = 1;
        last_interrupt_time = interrupt_time;
    }
}

/*Function to reset the game*/
void resetGame()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        gameStarts = 0;
        last_interrupt_time = interrupt_time;
    }
}

/*Retuns the status of gameStarts
0 if the game hasn't started
1 if the game has started
-1 if the game has to go in deep sleep*/
int getGameStatus()
{
    return gameStarts;
}

/*Interrupt handler for the timer*/
void deepSleepEvent()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        gameStarts = -1;
        last_interrupt_time = interrupt_time;
    }
}

/*Interrupt handler, called when game over*/
void timeHasEnded()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        endTime = 1;
        last_interrupt_time = interrupt_time;
    }
}

/*Returns the status of endTime
0 if the time hasn't ended
1 if the time has ended*/
int getEndTime()
{
    return endTime;
}

/*Function to reset the endTime*/
void resetEndTime()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        endTime = 0;
        last_interrupt_time = interrupt_time;
    }
}

/*Button 0 handler, turns on and off the led 0*/
void buttonPressed0()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        int i = 0;
        if (statusL[i] == false)
        {
            digitalWrite(LPins[i], HIGH);
            statusL[i] = true;
        }
        else
        {
            digitalWrite(LPins[i], LOW);
            statusL[i] = false;
        }
        last_interrupt_time = interrupt_time;
    }
}

/*Button 1 handler, turns on and off the led 1*/
void buttonPressed1()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        int i = 1;
        if (statusL[i] == false)
        {
            digitalWrite(LPins[i], HIGH);
            statusL[i] = true;
        }
        else
        {
            digitalWrite(LPins[i], LOW);
            statusL[i] = false;
        }
        last_interrupt_time = interrupt_time;
    }
}

/*Button 2 handler, turns on and off the led 2*/
void buttonPressed2()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        int i = 2;
        if (statusL[i] == false)
        {
            digitalWrite(LPins[i], HIGH);
            statusL[i] = true;
        }
        else
        {
            digitalWrite(LPins[i], LOW);
            statusL[i] = false;
        }
        last_interrupt_time = interrupt_time;
    }
}

/*Button 3 handler, turns on and off the led 3*/
void buttonPressed3()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        int i = 3;
        if (statusL[i] == false)
        {
            digitalWrite(LPins[i], HIGH);
            statusL[i] = true;
        }
        else
        {
            digitalWrite(LPins[i], LOW);
            statusL[i] = false;
        }
        last_interrupt_time = interrupt_time;
    }
}

/*Interrupt handler, called when the pattern is shown*/
void patternPressed()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        patternPress = 1;
        last_interrupt_time = interrupt_time;
    }
}

/*Function to restart patternPressed*/
void resetPatternPressed()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE)
    {
        patternPress = 0;
        last_interrupt_time = interrupt_time;
    }
}

/*Returns the value of patterPressed,
1-> if a patternPressed was called
0-> otherwise*/
int getPatternPressed()
{
    return patternPress;
}
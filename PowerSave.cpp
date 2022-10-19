/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
//This constant is defined to avoid compilation errors from multiple inclusions of the Enable Interrupt library 
#define LIBCALL_ENABLEINTERRUPT
//Used to query the Enable Interrupt library to ask what pin called the interrupt
#define EI_ARDUINO_INTERRUPTED_PIN
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "PowerSave.h"
#include "Pins.h"

static volatile unsigned long lastInterrupt = 0;

/*Calling this function enables sleep mode,
attaches interrupts to all the button pins to wakeup the Arduino*/
void sleep()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    for (int i = 0; i < N; i++)
    {
        enableInterrupt(BPins[i], wakeup, RISING);
    }
    sleep_mode();
}

/*Calling this function disables sleep mode,
unconnects all interrupts to all the button pins*/
void wakeup()
{
    sleep_disable();
    for (int i = 0; i < N; i++)
    {
        disableInterrupt(BPins[i]);
    }
    lastInterrupt = millis();
}

/*Returns the time of the last interrupt in millis*/
unsigned long getLastInterruptTime()
{
    return lastInterrupt;
}
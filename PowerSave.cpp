#define LIBCALL_ENABLEINTERRUPT
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "PowerSave.h"
#include "Pins.h"


static unsigned long lastInterrupt=0;

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
    lastInterrupt = millis();
    sleep_disable();
    for (int i = 0; i < N; i++)
    {
        disableInterrupt(BPins[i]);
    }
}

/*Returns the time of the last interrupt in millis*/
int getLastInterruptTime(){
    return lastInterrupt;
}
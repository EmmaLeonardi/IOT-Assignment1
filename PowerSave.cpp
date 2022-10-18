#define LIBCALL_ENABLEINTERRUPT
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "PowerSave.h"
#include "Pins.h"
#define DEBOUNCED 200


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
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCED)
    {
        last_interrupt_time = interrupt_time;
        sleep_disable();
        for (int i = 0; i < N; i++)
        {
            disableInterrupt(BPins[i]);
        }
    }
}
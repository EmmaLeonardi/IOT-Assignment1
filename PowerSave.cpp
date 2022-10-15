#define LIBCALL_ENABLEINTERRUPT
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "PowerSave.h"
#include "Pins.h"

/*Calling this function enables sleep mode,
attaches interrupts to all the button pins to wakeup the Arduino*/
void sleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    for(int i=0; i<N; i++){
        enableInterrupt(BPins[i],wakeup,CHANGE);
    }
    sleep_mode();

}

/*Calling this function disables sleep mode,
unconnects all interrupts to all the button pins*/
void wakeup(){
    sleep_disable();
    for(int i=0; i<N; i++){
        disableInterrupt(BPins[i]);
    }
}
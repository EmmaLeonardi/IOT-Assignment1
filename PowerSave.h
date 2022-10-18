#ifndef POWER_SAVE_H
#define POWER_SAVE_H

#define DEBOUNCED 200

/*Calling this function enables sleep mode,
attaches interrupts to all the button pins to wakeup the Arduino*/
void sleep();

/*Calling this function disables sleep mode,
unconnects all interrupts to all the button pins*/
void wakeup();

/*Returns the time of the last interrupt in millis*/
unsigned long getLastInterruptTime();

#endif
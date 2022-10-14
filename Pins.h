#ifndef PINS_H
#define PINS_H

#include "Constants.h"

// A free analog pin (not connected) used to initialize a random generator
#define AnalogFree A0

// The pin of the red led
#define LS 12

// The analog pin of the potentiometer
#define Pot 1

// The min value of the potentiomenter
#define POTMIN 0
// The max value of the potentiomenter
#define POTMAX 1023

/*Array of the button pins*/
extern int BPins[N];

/*Array of the led pins*/
extern int LPins[N];

/*The status of the leds, to know if a given led is on or off
false->off/LOW, true->on/HIGH
*/
extern bool statusL[N];

#endif
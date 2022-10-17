#include "Pins.h"
/*Array of the button pins*/
int BPins[N] = {7, 6, 5, 4};

/*Array of the led pins*/
int LPins[N] = {12, 10, 9, 8};

/*The status of the leds, to know if a given led is on or off
false->off/LOW, true->on/HIGH
*/
bool statusL[N];
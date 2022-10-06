#ifndef PINS_H
#define PINS_H

#include<Constants.h>

//The pin of the red led
#define LS 12

//The analog pin of the potentiometer
#define Pot 1

//The min value of the potentiomenter
#define POTMIN 0
//The max value of the potentiomenter
#define POTMAX 1023

extern const int* BPins;
extern const int* LPins;

#endif
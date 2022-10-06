#ifndef PATTERNS_H
#define PATTERNS_H

/* This method uses a pseudorandom generator to create a pattern on the given array
*/
void generatePattern(boolean* a, int SIZE);

/* This method sets the pattern stored in the given array 
on the leds connected to the array of pins.
false->LOW
true->HIGH
*/
void setPattern(boolean* a, int* pins, int SIZE);

/* This method compares the given arrays and
returns true if the pattern is the same
*/
boolean comparePattern(boolean* a, boolean* b, int SIZE);

#endif
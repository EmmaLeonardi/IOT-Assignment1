#ifndef PATTERNS_H
#define PATTERNS_H

/* This method uses a pseudorandom generator to create a pattern on the given array
 */
void generatePattern(bool *a, int SIZE);

/* This method uses a pseudorandom generator to create a pattern on the given array a.
The pattern will never be all empty (all cells are false)
 */
void generatePatternNoVoid(bool *a, int SIZE);

/* This method sets the pattern stored in the given array
on the leds connected to the array of pins.
false->LOW
true->HIGH
*/
void setPattern(bool *a, int *pins, int SIZE);

/* This method compares the given arrays and
returns true if the pattern is the same
*/
bool comparePattern(bool *a, bool *b, int SIZE);

#endif
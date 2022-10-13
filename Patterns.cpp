#include "Patterns.h"
#include "Arduino.h"

/* This method uses a pseudorandom generator to create a pattern on the given array a.
 */
void generatePattern(bool *a, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        bool b = rand() % 2;
        a[i] = b;
    }
}

/* This method sets the pattern stored in the given array a
on the leds connected to the array of pins.
false->LOW
true->HIGH
*/
void setPattern(bool *a, int *pins, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        bool app = a[i];
        if (app == false)
        {
            digitalWrite(pins[i], LOW);
        }
        else
        {
            digitalWrite(pins[i], HIGH);
        }
    }
}

/* This method compares the given arrays a and b and
returns true if the pattern is the same.
*/
bool comparePattern(bool *a, bool *b, int SIZE)
{
    bool equals = true;
    int i = 0;
    do
    {
        if (a[i] != b[i])
        {
            equals = false;
        }
        i++;
    } while (equals == true || i < SIZE);
}
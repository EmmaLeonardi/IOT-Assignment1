#ifndef DIFFICULTY_H
#define DIFFICULTY_H

// The minimum time to wait for the pattern to appear
#define RANDOMWAITMIN 2

// The maximum time to wait for the pattern to appear
#define RANDOMWAITMAX 5

// The maximum number of penalty before game over
#define PENALTYMAX 3

// The time to wait after a game over before a new game can be started
#define GAMEOVERWAIT 10

// The time to turn on the penality led after a penality
#define PENALITYLEDON 1

/*Returns the start time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getStartTime(int lv);

/*Returns the time for the next level, given the previous one */
int nextLevelTime(int previousTime);

/*Returns the memorize time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getMemorizeTime(int lv);

/*Returns the time for the next memorize, given the previous one */
int nextMemorizeTime(int previousTime);

/*Returns the time for a random wait between MIN and MAX */
int randomWaitTime();

/*Adds a penality, returns true if the number is less than PENALITY MAX, otherwise false*/
bool addPenality();

/*Resets the number of penalities*/
void resetPenality();

#endif
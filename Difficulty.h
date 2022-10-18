#ifndef DIFFICULTY_H
#define DIFFICULTY_H

// The minimum time in seconds to wait for the pattern to appear
#define RANDOMWAITMIN 1

// The maximum time in seconds to wait for the pattern to appear
#define RANDOMWAITMAX 3

// The maximum number of penalty before game over
#define PENALTYMAX 3

// The time to wait in seconds after a game over before a new game can be started
#define GAMEOVERWAIT 10

// The time in seconds to turn on the penalty led after a penalty
#define PENALTYLEDON 1

/*Returns the start time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
double getStartTime(int lv);

/*Returns the time for the next level, given the previous one
It will never be less then a second*/
double nextLevelTime(double previousTime);

/*Returns the memorize time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
double getMemorizeTime(int lv);

/*Returns the time for the next memorize, given the previous one 
It will never be less then a second*/
double nextMemorizeTime(double previousTime);

/*Returns the time for a random wait between MIN and MAX */
int randomWaitTime();

/*Adds a penalty*/
void addPenalty();

/*Resets the number of penalties*/
void resetPenalty();

/*Returns the number of penalties*/
int getPenalty();

#endif
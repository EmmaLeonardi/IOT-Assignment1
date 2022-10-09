#ifndef DIFFICULTY_H
#define DIFFICULTY_H

//The minimum time to wait for the pattern to appear
#define RANDOMWAITMIN 2

//The maximum time to wait for the pattern to appear
#define RANDOMWAITMAX 5

//The maximum number of penalty before game over
#define PENALTYMAX 3

/*Returns the start time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getStartTime(int lv);

/*Returns the time for the next level, given the previous one */
int nextLevelTime(int previousTime);

/*Returns the memorize time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getMemorizeTime(int lv);

/*Returns the time for the next memorize, given the previous one */
int nextLevelTime(int previousTime);

#endif
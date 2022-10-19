/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
#include <stdlib.h>
#include "Difficulty.h"
#include "Constants.h"

// Defines the initial time at the easiest difficulty
#define EasyStartTime 10

// Defines the percentage of time reduction for each level that is harder than the easiest one
#define HarderStartTimePercentage 0.85

// Defines the percentage speedup of each consecutive level
#define NextLevelSpeedup 0.85

// Defines the memorize time at the easiest difficulty
#define EasyMemorizeTime 8

// Defines the percentage of time reduction for each level that is harder than the easiest one
#define HarderMemorizeTimePercentage 0.95

// Defines the percentage speedup of each consecutive level
#define NextMemorizeSpeedup 0.95

// The number of penalties
static int penaltyN=0;

/*Returns the start time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
double getStartTime(int lv)
{
    if (lv >= 1 && lv <= LV)
    {
        if (lv == 1)
        {
            return EasyStartTime;
        }
        else
        {
            double a = EasyStartTime;
            int l = 1;
            while (l < lv)
            {
                a = a * HarderStartTimePercentage;
                l++;
            }
            return a;
        }
    }
    return -1;
}

/*Returns the time for the next level, given the previous one 
It will never be less then a second*/
double nextLevelTime(double previousTime)
{
    return (previousTime * NextLevelSpeedup)<1?1:previousTime*NextLevelSpeedup;
}

/*Returns the memorize time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
double getMemorizeTime(double lv)
{
    if (lv >= 1 && lv <= LV)
    {
        if (lv == 1)
        {
            return EasyMemorizeTime;
        }
        else
        {
            double a = EasyMemorizeTime;
            int l = 1;
            while (l < lv)
            {
                a = a * HarderMemorizeTimePercentage;
                l++;
            }
            return a;
        }
    }
    return -1;
}

/*Returns the time for the next memorize, given the previous one 
It will never be less then a second*/
double nextMemorizeTime(double previousTime)
{
    return (previousTime * NextMemorizeSpeedup)<1?1:previousTime*NextMemorizeSpeedup;
}

/*Returns the time for a random wait between MIN and MAX */
int randomWaitTime()
{
    return rand() % (RANDOMWAITMAX - RANDOMWAITMIN) + RANDOMWAITMIN;
}

/*Adds a penalty*/
void addPenalty(){
    penaltyN++;
}

/*Resets the number of penalties*/
void resetPenalty(){
    penaltyN=0;
}

/*Returns the number of penalties*/
int getPenalty(){
    return penaltyN;
}
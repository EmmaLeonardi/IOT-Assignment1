#include "Difficulty.h"
#include "Constants.h"

// Defines the initial time at the easiest difficulty
#define EasyStartTime 30

// Defines the percentage of time reduction for each level that is harder than the easiest one
#define HarderStartTimePercentage 0.85

// Defines the percentage speedup of each consecutive level
#define NextLevelSpeedup 0.85

// Defines the memorize time at the easiest difficulty
#define EasyMemorizeTime 10

// Defines the percentage of time reduction for each level that is harder than the easiest one
#define HarderMemorizeTimePercentage 0.95

// Defines the percentage speedup of each consecutive level
#define NextMemorizeSpeedup 0.95

/*Returns the start time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getStartTime(int lv)
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

/*Returns the time for the next level, given the previous one */
int nextLevelTime(int previousTime)
{
    return previousTime * NextLevelSpeedup;
}

/*Returns the memorize time for the difficulty level selected.
The level has to be between 1 (easiest) and LV (hardest, defined in constants), otherwise returns -1*/
int getMemorizeTime(int lv)
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

/*Returns the time for the next memorize, given the previous one */
int nextMemorizeTime(int previousTime)
{
    return previousTime * NextMemorizeSpeedup;
}
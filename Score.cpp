/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
#include "Score.h"

/*This function calculates the number of points gained by succesfully clearing a level at the given difficulty*/
int countPoints(int lv)
{
    return lv * LVCOMPLETE;
}
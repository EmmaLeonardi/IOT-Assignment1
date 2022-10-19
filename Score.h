/*This code was written by Emma Leonardi (emma.leonardi2@studio.unibo.it)*/
#ifndef SCORE_H
#define SCORE_H

/*For each level completed the player gains points based on the difficulty level*/
#define LVCOMPLETE 100

/*This function calculates the number of points gained by succesfully clearing a level at the given difficulty*/
int countPoints(int lv);

#endif
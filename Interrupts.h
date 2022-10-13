#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// This variable is set to 1 when the function start game is called, -1 if the timer ticked, otherwise 0
static int gameStarts;

/*Interrupt handler, to play the game*/
void interruptLed();

/*Interrupt handler, to start the game*/
void startGame();

/*Function to reset the gameStatus*/
void resetGame();

/*Retuns the status of gameStarts
0 if the game hasn't started
1 if the game has started
-1 if the game has to go in deep sleep*/
int getGameStatus();

/*Interrupt handler for the timer*/
void deepSleepEvent();

#endif
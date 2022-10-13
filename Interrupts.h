#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// This variable is set to 1 when the function start game is called, -1 if the timer ticked, otherwise 0
static int gameStarts;

// This variable is set to 1 when the function end time is called, otherwise 0
static int endTime;

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

/*Interrupt handler, called when game over*/
void timeHasEnded();

/*Returns the status of endTime
0 if the time hasn't ended
1 if the time has ended*/
int getEndTime();

/*Function to reset the endTime*/
void resetEndTime();

#endif
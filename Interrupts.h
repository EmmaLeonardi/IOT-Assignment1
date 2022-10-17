#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// This variable is set to 1 when the function start game is called, -1 if the timer ticked, otherwise 0
volatile static int gameStarts;

// This variable is set to 1 when the function end time is called, otherwise 0
volatile static int endTime;

// This variable is set to 1 when the function pattern press is called, otherwise 0
volatile static int patternPress;

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

/*Interrupt handler, called when time has ended*/
void timeHasEnded();

/*Returns the status of endTime
0 if the time hasn't ended
1 if the time has ended*/
int getEndTime();

/*Function to reset the endTime*/
void resetEndTime();

/*Button 0 handler, turns on and off the led 0*/
void buttonPressed0();

/*Button 1 handler, turns on and off the led 1*/
void buttonPressed1();

/*Button 2 handler, turns on and off the led 2*/
void buttonPressed2();

/*Button 3 handler, turns on and off the led 3*/
void buttonPressed3();

/*Interrupt handler, called when the pattern is shown*/
void patternPressed();

/*Function to restart patternPressed*/
void resetPatternPressed();

/*Returns the value of patterPressed,
1-> if a patternPressed was called
0-> otherwise*/
int getPatternPressed();

#endif
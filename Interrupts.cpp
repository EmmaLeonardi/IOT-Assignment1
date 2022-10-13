#include "Interrupts.h"

/*Interrupt handler, to play the game*/
void interruptLed(){
    //TODO: https://github.com/GreyGnome/EnableInterrupt#determine-the-pin-that-was-interrupted
    //Read what button has called the interrupt and switch the status of the correct led
}

/*Interrupt handler, to start the game*/
void startGame()
{
    gameStarts = 1;
}

/*Function to reset the game*/
void resetGame()
{
    gameStarts = 0;
}

/*Retuns the status of gameStarts
0 if the game hasn't started
1 if the game has started
-1 if the game has to go in deep sleep*/
int getGameStatus(){
    return gameStarts;
}

/*Interrupt handler for the timer*/
void deepSleepEvent(){
    gameStarts=-1;
}

void timeHasEnded(){
    endTime=1;
}

int getEndTime(){
    return endTime;
}

/*Function to reset the endTime*/
void resetEndTime(){
    endTime=0;
}
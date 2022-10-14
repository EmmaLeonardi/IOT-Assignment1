#include "Interrupts.h"
#include "Pins.h"
#include "Arduino.h"

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

/*Interrupt handler, called when game over*/
void timeHasEnded(){
    endTime=1;
}

/*Returns the status of endTime
0 if the time hasn't ended
1 if the time has ended*/
int getEndTime(){
    return endTime;
}

/*Function to reset the endTime*/
void resetEndTime(){
    endTime=0;
}

/*Button 0 handler, turns on and off the led 0*/
void buttonPressed0(){
    int i=0;
    if(statusL[i]==false){
        digitalWrite(LPins[i],HIGH);
        statusL[i]=true;
    }else{
        digitalWrite(LPins[i],LOW);
        statusL[i]=false;
    }
}

/*Button 1 handler, turns on and off the led 1*/
void buttonPressed1(){
    int i=1;
    if(statusL[i]==false){
        digitalWrite(LPins[i],HIGH);
        statusL[i]=true;
    }else{
        digitalWrite(LPins[i],LOW);
        statusL[i]=false;
    }
}

/*Button 2 handler, turns on and off the led 2*/
void buttonPressed2(){
    int i=2;
    if(statusL[i]==false){
        digitalWrite(LPins[i],HIGH);
        statusL[i]=true;
    }else{
        digitalWrite(LPins[i],LOW);
        statusL[i]=false;
    }
}

/*Button 3 handler, turns on and off the led 3*/
void buttonPressed3(){
    int i=3;
    if(statusL[i]==false){
        digitalWrite(LPins[i],HIGH);
        statusL[i]=true;
    }else{
        digitalWrite(LPins[i],LOW);
        statusL[i]=false;
    }
}
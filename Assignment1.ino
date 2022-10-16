#include "Pins.h"
#include "Constants.h"
#include "Patterns.h"
#include "Fade.h"
#include "Difficulty.h"
#include "Score.h"
#include "Interrupts.h"
#include "Status.h"
#include "PowerSave.h"
#include <TimerOne.h>
#include <EnableInterrupt.h>

/*
0->the main menu, choose difficulty
1->generating the led pattern
2->the player is guessing the pattern
3->guessed rigth, increase score and decrease time
4->game over
*/
int status;

// The level of difficulty of the game, chosen at the start
int lv = 0;

// Used to print only once instructions
bool hasPrinted = false;

// The brigthness of the fading led
int brightness = 0;

// The game score
int score = 0;

// The pattern of leds to guess
bool pattern[N];

// The time for which the pattern is shown
int timeShow = 0;

// The time given to guess the pattern
int timeGuess = 0;

void setup()
{
    for (int i = 0; i < N; i++)
    {
        pinMode(LPins[i], OUTPUT);
        pinMode(BPins[i], INPUT);
        statusL[i] = false;
    }
    pinMode(Pot, INPUT);
    pinMode(LS, OUTPUT);
    status = 0;
    Serial.begin(9600);
    srand(analogRead(AnalogFree));
    Serial.flush();
}

void loop()
{
    switch (status)
    {
    case (0):;
        {
            if (hasPrinted == false)
            {
                Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start.");
                hasPrinted = true;
                // Turn on interrupts for B1
                enableInterrupt(BPins[0], startGame, CHANGE);
                Timer1.initialize(WAITFORSTART * USECTOSEC);
                Timer1.attachInterrupt(deepSleepEvent);
            }
            int pValue = analogRead(Pot);
            int tmp = map(pValue, POTMIN, POTMAX, LVMIN, LVMAX);
            if (tmp != lv)
            {
                // The difficulty has changed
                lv = tmp;
                Serial.print("Difficulty set to: ");
                Serial.println(lv);
                timeShow = getStartTime(lv);
                timeGuess = getMemorizeTime(lv);
            }
            // Ls pulses
            brightness = nextStep(brightness);
            setBrightness(brightness, LS);
            if (getGameStatus() == -1)
            {
                //  Remove timer1 handler
                Timer1.detachInterrupt();
                // Removed interrupt handler
                disableInterrupt(BPins[0]);
                // Reset game status
                resetGame();
                // Deep sleep triggered, all buttons trigger interrupts to wakeup arduino
                sleep();
                // Reset status
                status = 0;
            }
            else if (getGameStatus() == 1)
            {
                // Remove timer1 handler
                Timer1.detachInterrupt();
                // Removed interrupt handler
                disableInterrupt(BPins[0]);
                Serial.println("Go!");
                brightness = FADE_LIMIT_MIN;
                setBrightness(brightness, LS);
                // Reset score, next part of game
                score = 0;
                status = 1;
                hasPrinted = false;
                resetGame();
                turnAllOff(LPins, statusL, N);
            }
            else
            {
                // Still waiting for button press or timer event
            }
        }
        break;
    case (1):;
        {
            // Waiting a t1 random time
            delay(randomWaitTime());
            // Generate pattern
            generatePattern(pattern, N);
            // Turn on led
            setPattern(pattern, LPins, N);
            setStatusAsGiven(pattern, statusL, N);
            // Wait
            delay(timeShow);
            // Turn off all leds
            turnAllOff(LPins, statusL, N);
            status = 2;
        }
        break;
    case (2):;
        {
            if (hasPrinted == false)
            {
                // I have t3 time to guess
                hasPrinted = true;
                Timer1.initialize(timeGuess * USECTOSEC);
                Timer1.attachInterrupt(timeHasEnded);
                // Connect all buttons with the interrupts to all the leds, keeping status updated
                enableInterrupt(BPins[0], buttonPressed0, CHANGE);
                enableInterrupt(BPins[1], buttonPressed1, CHANGE);
                enableInterrupt(BPins[2], buttonPressed2, CHANGE);
                enableInterrupt(BPins[3], buttonPressed3, CHANGE);
            }
            if (getEndTime() == 1)
            {
                hasPrinted = false;
                // The time has ended
                Timer1.detachInterrupt();
                // Remove all button interrupts
                for (int i = 0; i < N; i++)
                {
                    disableInterrupt(BPins[i]);
                }
                bool guess = comparePattern(pattern, statusL, N);
                if (guess)
                {
                    // Guessed rigth!
                    status = 3;
                }
                else
                {
                    // Guessed wrong
                    Serial.println("Penality!");
                    // Red led turns on 1 second, then turned off
                    turnLedOnFor(LS, PENALITYLEDON);
                    if (addPenality() == false)
                    {
                        // Game over
                        status = 4;
                    }
                    else
                    {
                        // Guessed wrong, try again
                        status = 2;
                    }
                }
            }
        }
        break;
    case (3):;
        {
            // Increase score, print score
            score += countPoints(lv);
            Serial.print("New point! Score: ");
            Serial.println(score);
            // Speedup
            timeGuess = nextMemorizeTime(timeGuess);
            timeShow = nextLevelTime(timeGuess);
            // Back to pattern generation
            status = 1;
        }
        break;
    case (4):;
        {
            // Game over
            Serial.print("Game Over. Final Score: ");
            Serial.println(score);
            delay(GAMEOVERWAIT);
            // New game
            status = 0;
        }
        break;
    default:
        //??
        ;
        {
        }
    };
}
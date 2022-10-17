#include "Pins.h"
#include "Constants.h"
#include "Patterns.h"
#include "Fade.h"
#include "Difficulty.h"
#include "Score.h"
#include "Interrupts.h"
#include "Status.h"
#include "PowerSave.h"
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

// This variable is used to store the time
unsigned long previousTime = 0;

// If the debug symbol has been defined, extra prints appear on the console as testing checks
#define DEBUG

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
#ifdef DEBUG
    Serial.println("Debug activated, setup correct");
#endif
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
                // Reset the game
                resetGame();
                // Reset penalty
                resetPenalty();
                // Reset score
                score = 0;
                // Turn off all game leds
                turnAllOff(LPins, statusL, N);
#ifdef DEBUG
                Serial.println("D: Connecting the button interrupt and timer");
#endif
                // Turn on interrupts for B1
                enableInterrupt(BPins[0], startGame, CHANGE);
                previousTime = millis();
#ifdef DEBUG
                Serial.print("D: Inizialized previous time, value");
                Serial.println(previousTime);
#endif
            }
            int pValue = analogRead(Pot);
            int tmp = map(pValue, POTMIN, POTMAX, LVMIN, LVMAX);
            if (tmp != lv)
            {
                // The difficulty has changed
                lv = tmp;
                Serial.print("D: Difficulty set to: ");
                Serial.println(lv);
                timeShow = getStartTime(lv);
                timeGuess = getMemorizeTime(lv);
            }
            // Ls pulses
            brightness = nextStep(brightness);
            setBrightness(brightness, LS);
            unsigned long now = millis();
            if (now-previousTime>= WAITFORSTART * MSECTOSEC)
            {
                deepSleepEvent();
                previousTime = now;
            }
            if (getGameStatus() == -1)
            {
#ifdef DEBUG
                Serial.println("D: Timer event has run out, system entering deep sleep mode");
#endif
                // Removed interrupt handler
                disableInterrupt(BPins[0]);
                // Reset game status
                resetGame();
                // Turning off LS
                brightness = FADE_LIMIT_MIN;
                setBrightness(brightness, LS);
                // Deep sleep triggered, all buttons trigger interrupts to wakeup arduino
                sleep();
                // Reset status
                status = 0;
                // Reset has printed
                hasPrinted = false;
#ifdef DEBUG
                Serial.println("D: System has exited deep sleep mode");
#endif
            }
            else if (getGameStatus() == 1)
            {
#ifdef DEBUG
                Serial.println("D: Interrupt on button activated, game starting");
#endif
                // Removed interrupt handler
                disableInterrupt(BPins[0]);
                Serial.println("Go!");
                brightness = FADE_LIMIT_MIN;
                setBrightness(brightness, LS);
                // Reset score, next part of game
                score = 0;
                status = 1;
                hasPrinted = false;
            }
            else
            {
                // Still waiting for button press or timer event
            }
        }
        break;
    case (1):;
        {
#ifdef DEBUG
            Serial.println("D: Generating a led pattern");
#endif

            // Waiting a t1 random time
            delay(randomWaitTime());
            // Generate pattern
            generatePattern(pattern, N);
            // Turn on led
            setPattern(pattern, LPins, N);
            setStatusAsGiven(pattern, statusL, N);
#ifdef DEBUG
            Serial.println("D: Waiting for the player to memorize");
#endif
            // Wait
            delay(timeShow);
            // Turn off all leds
            turnAllOff(LPins, statusL, N);
            status = 2;
#ifdef DEBUG
            Serial.println("D: Going to next fase");
            Serial.print("D: Difficulty: ");
            Serial.println(lv);
#endif
        }
        break;
    case (2):;
        {
            if (hasPrinted == false)
            {
                // I have t3 time to guess
                hasPrinted = true;
#ifdef DEBUG
                Serial.println("D: Connecting to all buttons to interrupts, to change the corrisponding led status");
                Serial.print("D: Memory time: ");
                Serial.println(timeShow);
                Serial.print("D: Guess time: ");
                Serial.println(timeGuess);
#endif
                // Connect all buttons with the interrupts to all the leds, keeping status updated
                enableInterrupt(BPins[0], buttonPressed0, CHANGE);
                enableInterrupt(BPins[1], buttonPressed1, CHANGE);
                enableInterrupt(BPins[2], buttonPressed2, CHANGE);
                enableInterrupt(BPins[3], buttonPressed3, CHANGE);

                previousTime = millis();
#ifdef DEBUG
                Serial.print("D: Set timer interrupt, millis value is");
                Serial.println(previousTime);
#endif
            }
            unsigned long now = millis();
            if (now- previousTime >= timeGuess * MSECTOSEC)
            {
                timeHasEnded();
                previousTime = now;
            }

            if (getEndTime() == 1)
            {
#ifdef DEBUG
                Serial.println("D: Time out");
#endif
                hasPrinted = false;
                // The time has ended
#ifdef DEBUG
                Serial.println("D: Removing all interrupts");
#endif
                // Remove all button interrupts
                for (int i = 0; i < N; i++)
                {
                    disableInterrupt(BPins[i]);
                }
#ifdef DEBUG
                Serial.println("D: Comparing patterns");
#endif
                bool guess = comparePattern(pattern, statusL, N);
                if (guess)
                {
#ifdef DEBUG
                    Serial.println("D: Guessed rigth");
#endif
                    // Guessed rigth!
                    status = 3;
                }
                else
                {
#ifdef DEBUG
                    Serial.println("D: Guessed wrong");
#endif
                    // Guessed wrong
                    Serial.println("Penalty!");
                    // Red led turns on 1 second, then turned off
                    turnLedOnFor(LS, PENALTYLEDON);
                    addPenalty();
                    if (getPenalty() == PENALTYMAX)
                    {
#ifdef DEBUG
                        Serial.println("D: Game over");
#endif
                        // Game over
                        status = 4;
                    }
                    else
                    {
#ifdef DEBUG
                        Serial.print("D: Not yet game over, penalty number ");
                        Serial.println(getPenalty());
#endif
                        // Guessed wrong, try again
                        status = 2;
                    }
                }
            }
        }
        break;
    case (3):;
        {
#ifdef DEBUG
            Serial.println("D: Next round soon:");
#endif
            // Increase score, print score
            score += countPoints(lv);
            Serial.print("New point! Score: ");
            Serial.println(score);
            // Speedup
            timeShow = nextMemorizeTime(timeShow);
            timeGuess = nextLevelTime(timeGuess);
#ifdef DEBUG
            Serial.print("D: Time to memorize");
            Serial.println(timeShow);
            Serial.print("D: Time to guess");
            Serial.println(timeGuess);
#endif
            // Back to pattern generation
            status = 1;
        }
        break;
    case (4):;
        {
            // Game over
            Serial.print("Game Over. Final Score: ");
            Serial.println(score);
#ifdef DEBUG
            Serial.print("D: Number of penalties ");
            Serial.println(getPenalty());
#endif
            delay(GAMEOVERWAIT);
            // New game
            status = 0;
        }
        break;
    default:
#ifdef DEBUG
        Serial.println("Empty case, should never be accessed");
#endif
        ;
        {
        }
    };
}
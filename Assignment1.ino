#include "Pins.h"
#include "Constants.h"
#include "Patterns.h"
#include "Fade.h"
#include "Difficulty.h"
#include "Score.h"
#include "Interrupts.h"
#include "Status.h"
#include <TimerOne.h>
#include <EnableInterrupt.h>

bool statusL[N];
// 0->spenti, 1->accesi

int status;
int lv = 0;
bool hasPrinted = false;
int brightness = 0;
int score = 0;
bool pattern[N];
int time=0;

/*
0->il gioco è nel menù iniziale, decidi difficoltà
1->sto generando il pattern dei led
2->il giocatore sta creando il suo pattern
3->controllo pattern, controllo errori e aumento punti (3->1)
4->game over
*/

void setup()
{
    for (int i = 0; i++; i < N)
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
                time=getStartTime(lv);
            }
            // Ls pulses
            brightness = nextStep(brightness);
            setBrightness(brightness, LS);
            if (getGameStatus() == -1)
            {
                //TODO: Deep sleep triggered
                //TODO: Attach interrupt to all buttons to wakeup Arduino
                // Remove timer1 handler
                Timer1.detachInterrupt();
                // Removed interrupt handler
                disableInterrupt(BPins[0]);
                // Reset game status
                resetGame();
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
                score = 0;
                status = 1;
                hasPrinted = false;
                resetGame();
            }
            else
            {
                // Still waiting for button press or timer event
            }
        }
        break;
    case (1):;
        {
            //Waiting a t1 random time
            delay(randomWaitTime());
            //Generate pattern
            generatePattern(pattern,N);
            //Turn on led
            setPattern(pattern,LPins,N);
            setStatusAsGiven(pattern,statusL,N);
            //Wait
            delay(time);
            //Turn off all leds
            turnAllOff(LPins,statusL,N);
            status=2;
        }
        break;
    case (2):;
        {
            // Ho t3 tempo per indovinare
            // Leggo gli interrupt, accendo led corrispondenti
            // Timeout->aumento penalià o pattern corretto
            // Se penalità >max allowed (game over)->4
            // Altrimenti vai in 1 (dopo print penalità)
        }
        break;
    case (3):;
        {
            // Aumento punteggio, stampo punteggio
            // Torno a 1
        }
        break;
    case (4):;
        {
            // Stampa game over, punteggio, difficoltà
            // Ritorna dopo tot in 1
            // resetta game started
        }
        break;
    default:
        //??
        ;
        {
        }
    };
}
#include "Pins.h"
#include "Constants.h"
#include "Patterns.h"
#include "Fade.h"

bool statusL[N];
// 0->spenti, 1->accesi

int status;
int lv = 0;
bool hasPrinted = false;
int brightness = 0;
int score=0;

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
    case (0):
        if (hasPrinted == false)
        {
            Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start.");
            hasPrinted = true;
            // Ls pulses
        }
        int pValue = analogRead(Pot);
        int tmp = map(pValue, POTMIN, POTMAX, LVMIN, LVMAX);
        if (tmp != lv)
        {
            // The difficulty has changed
            lv = tmp;
            Serial.print("Difficulty set to: ");
            Serial.println(lv);
        }
        brightness = nextStep(brightness);
        setBrightness(brightness, LS);
        // Interrupt handler per T1
        // Se premi il pulsante->1
        // Se non premi pulsante sleep
        Serial.println("Go!");
        //
        brightness=FADE_LIMIT_MIN;
        setBrightness(brightness,LS);
        score=0;
        status=1;
        hasPrinted = false;
        break;
    case (1):
        // Spengo led per t1 tempo casuale
        // Genero pattern
        // Accendo led
        // Aspetto tempo casuale t2 acceso
        // Spengo tutto
        break;
    case (2):
        // Ho t3 tempo per indovinare
        // Leggo gli interrupt, accendo led corrispondenti
        // Quando hai il pattern corretto->3
        // Timeout->aumento penalià
        // Se penalità >max allowed (game over)->4
        // Altrimenti vai in 1 (dopo print penalità)
        break;
    case (3):
        // Aumento punteggio, stampo punteggio
        // Torno a 1
        break;
    case (4):
        // Stampa game over, punteggio, difficoltà
        // Ritorna dopo tot in 1
        break;
    default:
        //??
    }
}
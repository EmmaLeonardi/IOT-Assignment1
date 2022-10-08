#include <Pins.h>
#include <Constants.h>
#include <Patterns.h>

boolean statusL[N];
// 0->spenti, 1->accesi

int status;
int lv=0;

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
        statusL[i]=false;
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
        Serial.println("“Welcome to the Catch the Led Pattern Game. Press Key T1 to Start.");
        // 0->1023
        int pValue = analogRead(Pot);
        lv = map(pValue, POTMIN, POTMAX, LVMIN, LVMAX);
        // Cambio la difficoltà e lo stampo
        Serial.print("Difficoltà impostata a: ");
        Serial.println(lv);
        //Se premi il pulsante->1
        //Se non premi pulsante sleep
        //Led rosso varie
        //Go!
        break;
    case (1):
        //Resetto punteggio
        //Genero pattern
        //Accendo led
        //Aspetto tempo casuale t1 acceso
        //Spengo per tempo casuel t2
        break;
    case (2):
        //Leggo gli interrupt, accendo led corrispondenti
        //Quando hai il pattern corretto->3
        //Timeout->aumento penalià
        //Se penalità >max allowed (game over)->4
        //Altrimenti vai in 1 (dopo print penalità)
        break;
    case (3):
        //Aumento punteggio, stampo punteggio
        //Torno a 1
        break;
    case (4):
        //Stampa game over, punteggio, difficoltà
        //Ritorna dopo tot in 1
        break;
    default:
        //??
    }
}
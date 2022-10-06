
#define LS 12
#define NLed 4
#define Pot 1
//Analog 1

int LPins[NLed]={11,10,9,8};
int statusL[NLed]={0,0,0,0};
//0->spenti, 1->accesi

int BPins[NLed]={7,6,5,4};

int status;
/* 
0->il gioco è nel menù iniziale, decidi difficoltà
1->sto generando il pattern dei led
2->il giocatore sta creando il suo pattern
3->controllo pattern, controllo errori e aumento punti (3->1)
4->game over
*/

#define POTMIN 0
#define POTMAX 1023
#define LVMIN 1
#define LVMAX 4

void setup(){
    for(int i=0;i++;i<NLed){
    pinMode(LPins[i],OUTPUT);
    pinMode(BPins[i],INPUT);
    }
    pinMode(Pot,INPUT);
    pinMode(LS,OUTPUT);
    status=0;
    Serial.begin(9600);
}

void loop(){
    switch(status){
        case(0):
        Serial.flush();
        Serial.println("“Welcome to the Catch the Led Pattern Game. Press Key T1 to Start.");
        //0->1023
        int pValue=analogRead(Pot);
        int lv=map(pValue,POTMIN,POTMAX,LVMIN,LVMAX);
        //Cambio la difficoltà e lo stampo
        switch(lv){
            case(1):
            break;
            case(2):
            break;
            case(3):
            break;
            case(4):
            break;
            default:
        }


        break;
        case(1):
        break;
        case(2):
        break;
        case(3):
        break;
        case(4):
        break;
        default:
        //??
    }

    
}

// librariile standard de folosire 
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "tetris.h"


// tabla de joc
int tabla[RANDURI][COLOANE];
Piesa piesa_curenta;
static int sac[DIM_SAC];
static int indice_sac;
int scor;

int piesa_urmatoare_id;
int piesa_hold_id;
int hold_folosit;

// se vor folosi STATICS!!! pentru a nu permite modificarea pe parcursul rularii programului
static const int sabloane[7][4][4] = 
{
    {// I shape
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    {// Square shape
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    {// T Junction shpaee
        {0,0,0,0},
        {0,1,1,1},
        {0,0,1,0},
        {0,0,0,0}
    },
    {//L right shape
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0}
    },
    {//L left shape
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0}
    },
    {//S right shape aka S
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    },
    {//S left shape aka Z
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0}
    }
};


static void reumple_sac(){// regenereaza piese dupa chletuire
    for(int i = 0 ;i <DIM_SAC;i++)
    {
        sac[i]=i;
    }
    for(int i =DIM_SAC-1;i>0;i--)
    {
        int new = rand() % (i+1);
        // swap la valori
        int temp   = sac[i];
            sac[i] = sac[new];
            sac[new] = temp;
    }
    indice_sac=0;
}
static int  verifica_coliziune(int nr,int nc,int forma[4][4])
{
    for(int a=0;a<4;a++)
    {
        for(int b=0;b<4;b++)
        {
            if(!forma[a][b])continue;
            int br = nr +a;
            int bc = nc +b;
            if( br< 0 ||bc<0 || br >= RANDURI || bc>=COLOANE)return 1;
            if(tabla[br][bc])return 1;
        }
    }
    // nu am gasit coliziune
    return 0;
}
static void fixeaza_piesa()
{
    for (int a =0;a<4;a++)
    {
        for(int b=0;b<4;b++)
        {
            if(piesa_curenta.forma[a][b])
            {
                tabla[piesa_curenta.rand+a][piesa_curenta.coloana+b] = 1;
            }
        }
    }
}
static void sterge_linii()
{
    for(int a =0;a<RANDURI;a++)
    {
        int plin=1;
        for(int b=0;b<COLOANE;b++)
        {
            if(!tabla[a][b])
            {
                plin = 0;
                break;
            }
        }
        if(plin)
        {
            for(int r=a;r>0;r--)
            {
                memcpy(tabla[r],tabla[r-1],sizeof(tabla[0]));
            memset(tabla[0], 0 , sizeof(tabla[0]));
            scor+=100;
            }
        }
    }
}





// generate new tetromino for the grid function
static void genereaza_piesa(void)
{
    piesa_curenta.id=piesa_urmatoare_id;
    memcpy(piesa_curenta.forma, sabloane[piesa_curenta.id], sizeof(piesa_curenta.forma));
    piesa_curenta.rand=0;
    piesa_curenta.coloana=COLOANE/2 -2;

    if (indice_sac >= DIM_SAC) reumple_sac();
    piesa_urmatoare_id = sac[indice_sac++];
    hold_folosit = 0;
     // nu mergea overflow detection
     if (verifica_coliziune(piesa_curenta.rand,piesa_curenta.coloana,piesa_curenta.forma))
     {
        stare_joc = STARE_JOC_PIERDUT;
     }

}


void comuta_hold(void){
    if (hold_folosit)return;
    int temp = piesa_hold_id;
    piesa_hold_id = piesa_curenta.id;
    if (temp<0)
    {
        piesa_curenta.id = piesa_urmatoare_id;
        if (indice_sac >= DIM_SAC )reumple_sac();
        piesa_urmatoare_id = sac[indice_sac++];
    }
    else
    {
        piesa_curenta.id = temp;
    }
    memcpy(piesa_curenta.forma, sabloane[piesa_curenta.id], sizeof(piesa_curenta.forma));
    piesa_curenta.rand = 0;
    piesa_curenta.coloana = COLOANE/2 -2;
     hold_folosit =1;
}





void  init_joc(void)
{
    srand((unsigned)time(NULL));
    memset(tabla, 0 , sizeof(tabla));
    scor=0;
    reumple_sac();
    
    piesa_hold_id  =-1;
    hold_folosit = 0;
    piesa_urmatoare_id = sac[indice_sac++];
}
void porneste_joc(void) 
{ 
    init_joc( );
    genereaza_piesa();
    stare_joc = STARE_JOC;
    
}
void actualizeaza_joc(void) 
{
    if( stare_joc!=STARE_JOC)return;
    if(!verifica_coliziune(piesa_curenta.rand +1,piesa_curenta.coloana,piesa_curenta.forma))
    {
        piesa_curenta.rand++;
    }
    else{
        fixeaza_piesa();
        sterge_linii();
        genereaza_piesa();
    }    
 }

void muta_piesa_stanga(void)  
{ 
    if(!verifica_coliziune(piesa_curenta.rand ,piesa_curenta.coloana -1,piesa_curenta.forma)){
        piesa_curenta.coloana--;
    }
    
}


void muta_piesa_dreapta(void)  
{ 
    if(!verifica_coliziune(piesa_curenta.rand ,piesa_curenta.coloana +1,piesa_curenta.forma)){
        piesa_curenta.coloana++;
    }
}


void roteste_piesa(void)       { 
    int temp[4][4];
    for    (int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            temp[c][3 - r] = piesa_curenta.forma[r][c];    
        }
    }
        if(!verifica_coliziune(piesa_curenta.rand,piesa_curenta.coloana,temp))
        {
            memcpy(piesa_curenta.forma,temp,sizeof ( temp ) );
        }
    
}


void coboara_piesa(void)       
{
     while(!verifica_coliziune(piesa_curenta.rand+1,piesa_curenta.coloana,piesa_curenta.forma)){
        piesa_curenta.rand++;
     }
    
}



const int (*get_sabloane(void))[4][4]{
    return sabloane;
}










//rotate pieces function

// method I -- o n^2 cu transpusa matricii 

/*
Rotate by +90:

    Transpose    ji = ij  trebuie temp arr
    Reverse each row n-1 = 0    trebuie int temp

*/

//Method2 -- lookup table cu switch case   o (1 aka complexitatea de cautare a switch case) avem maxim 9 cazuri
/*
Square are un singur caz
I shape are 2 cazuri
Snake shapes au ambele cate 2 cazuri
L shapes au cate 4 cazuri
T shape are 4 cazuri

static const int rotate_pieces(int input){
    switch (input)
    {
    case constant expression:
       
        break;
    default:
        break;
    }
}


*/



// color render function
//de ddocumentat de pe sdl


// functie de mutare a piesei cu call la grid colission 

// grid collision detection cu update

// bool function care verifica viitoarea pozitie  a piesei cu gridul 

// cand se updateaza game grid odata la perioada timpului de vazut daca active piece se atinge de grid, daca da de freezuit piesa si de generat una noua
// line clearing cu update dupa ce se termina grid collison  de verificat daca avem linii completate si de == 0
//score update dupa line clearing daca avem line cleared marim scoreul in functie de cate linii odata au fost compoletate

// integration  cu restul codului
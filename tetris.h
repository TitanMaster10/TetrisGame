
//name of module
#ifndef TETRIS_H
#define TETRIS_H

#include "input.h"
//helpers
//logical functions
#include <stdbool.h>

// graphics 
//#include <SDL2/SDL.h>
// de linkat libraryul 



// GRID 
#define RANDURI  20
#define COLOANE   10
#define DIM_SAC   7


typedef struct {
    
    int forma[4][4];
    int rand;
    int coloana;
    int id;

} Piesa;

extern int tabla[RANDURI][COLOANE];
extern Piesa piesa_curenta;
extern int scor;

extern int piesa_urmatoare_id;
extern int piesa_hold_id;
extern int hold_folosit;


void init_joc(void);
void porneste_joc(void);
void actualizeaza_joc(void);
// structura cu jocul in general
// starea gridului, piesei actuale , urmatoarea piesa generata,  score counter, starea jocului

// restul functiilor din .c updater rotater ...
void muta_piesa_stanga(void);
void muta_piesa_dreapta(void);
void roteste_piesa(void);
void coboara_piesa(void);

const int (*get_sabloane(void))[4][4];

#endif
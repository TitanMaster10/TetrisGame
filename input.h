#ifndef INPUT_H
#define INPUT_H



//#include <SDL2/SDL.h>
#include <stdbool.h>

// adaugat actiunile imputului posibile
// left right up down arrow
//pause resume quit  restart

// " baga enum cai mai simplu de vizualizat"


typedef enum {
    STARE_MENIU,
    STARE_JOC,
    STARE_PAUZA,
    STARE_JOC_PIERDUT
} StareJoc;

extern StareJoc stare_joc;

void init_mod_input(void);
void reseteaza_mod_input(void);
void gestioneaza_input(void);
void comuta_hold(void);

#endif


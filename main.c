#include <stdio.h>
#include "input.h"
#include "tetris.h"
#include "graphics.h"
#include "utils.h"

int main(void) {
    init_mod_input();
    init_joc();
    afiseaza_cadru();

    // până când ecranul pierdut + q
    const unsigned long INTERVAL_CADERE = 1500;
    unsigned long ultimul_tick = timp_curent_ms();

    while (!(stare_joc==STARE_JOC_PIERDUT && getchar()=='q')) {
        gestioneaza_input(); // poate ajunge in pause
        if (stare_joc == STARE_JOC){
            unsigned long acum = timp_curent_ms();

            if (stare_joc==STARE_JOC && acum - ultimul_tick >=INTERVAL_CADERE ) {
                actualizeaza_joc();
                ultimul_tick = acum;
            }
        }
        afiseaza_cadru  ();// resource heavy
        intarzie(100);
    }

    reseteaza_mod_input();
    return 0;
}

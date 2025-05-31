// srcSdl/main.c

#include <stdio.h>
#include "input.h"
#include "tetris.h"
#include "graphics.h"
#include "utils.h"

int main(void) {
    init_graphics();
    init_joc();
    // meniul inainte de game
    afiseaza_cadru();

    unsigned long last     = timp_curent_ms();
    unsigned long interval = 500; //ms

    while (!quit_requested) {
        handle_input();
        if (stare_joc == STARE_JOC) {
            unsigned long now = timp_curent_ms();
            if (now - last >= interval) {
                actualizeaza_joc();
                last = now;
            }
        }
        afiseaza_cadru();

        // 60 fps
        SDL_Delay(16);
    }

    destroy_graphics();
    return 0;
}
// switch case cu tipurile de input date 

/*

#include "input.h"
#include "tetris.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

*/

/*


*/

// SDL‐based input handling
#include <SDL.h>
#include "input.h"
#include "tetris.h"
#include <stdlib.h>
int quit_requested = 0;
StareJoc stare_joc  = STARE_MENIU;

void handle_input(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {  quit_requested = 1;}
        else if (e.type == SDL_KEYDOWN) {
            SDL_Keycode k = e.key.keysym.sym;
           
           
            switch (stare_joc) {
              case STARE_MENIU:
                if (k == SDLK_RETURN) porneste_joc();
                else if (k==SDLK_q || k==SDLK_ESCAPE) quit_requested = 1;
                break;
              case STARE_JOC:
                if      (k==SDLK_a || k==SDLK_LEFT ) muta_piesa_stanga();
                else if (k==SDLK_d || k==SDLK_RIGHT) muta_piesa_dreapta();
                else if (k==SDLK_w || k==SDLK_UP   ) roteste_piesa();
                else if (k==SDLK_s || k==SDLK_DOWN )  coboara_piesa();
                else if (k==SDLK_h                 )  comuta_hold();
                else if (k==SDLK_p)                  stare_joc = STARE_PAUZA;
                else if (k==SDLK_q)                  stare_joc = STARE_JOC_PIERDUT;
                break;
              case STARE_PAUZA:
                if (k==SDLK_p)    stare_joc = STARE_JOC;
                else if (k==SDLK_q) stare_joc = STARE_JOC_PIERDUT;
                break;
              case STARE_JOC_PIERDUT:
                if (k==SDLK_r)    porneste_joc();
                else if (k==SDLK_q || k==SDLK_ESCAPE) quit_requested = 1;
                break;
            }
        }
    }
}


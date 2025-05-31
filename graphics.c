// srcSdl/graphics.c

#include "graphics.h"
#include "tetris.h"
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>    // snprintf
extern int quit_requested;
extern StareJoc stare_joc;
extern int tabla[RANDURI][COLOANE];
extern Piesa piesa_curenta;
extern int piesa_urmatoare_id;
extern int piesa_hold_id;
extern int scor;
const int (*get_sabloane(void))[4][4];

static SDL_Window   *win      = NULL;
static SDL_Renderer *renderer = NULL;
static const int CELL = 24;  // dimensiunea bloc

void init_graphics(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        exit(1);
    }
    win = SDL_CreateWindow(
        "Tetris SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        COLOANE * CELL + CELL * 6,
        RANDURI  * CELL,
        0
    );
    if (!win) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(
        win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        exit(1);
    }
}

void destroy_graphics(void) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (win)      SDL_DestroyWindow(win);
    SDL_Quit();
}

void afiseaza_cadru(void) {
    // Clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //  UI din dreapta
    SDL_Rect zonaUI = {
        COLOANE * CELL,     // x start
        0,                  // y start
        CELL * 6,           // width
        RANDURI * CELL      // height
    };
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &zonaUI);

    // Linie separator 
    int xsep = COLOANE * CELL;
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawLine(renderer, xsep, 0, xsep, RANDURI * CELL);

    //  Blocuri fixe

    // ne-randomizator de culori pentru afisarea diferita a blocurilor
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int r = 0; r < RANDURI; ++r) {
        for (int c = 0; c < COLOANE; ++c) {
            if (tabla[r][c]) {
                SDL_Rect rc = { c * CELL, r * CELL, CELL, CELL };
                SDL_RenderFillRect(renderer, &rc);
            }
        }
    }

    //Piesa curenta
    const int (*S)[4][4] = get_sabloane();
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    for (int pr = 0; pr < 4; ++pr) {
        for (int pc = 0; pc < 4; ++pc) {
            if (piesa_curenta.forma[pr][pc]) {
                SDL_Rect rc = {
                    (piesa_curenta.coloana + pc) * CELL,
                    (piesa_curenta.rand    + pr) * CELL, CELL, CELL
                };
                SDL_RenderFillRect(renderer, &rc);
            }
        }
    }

    // Next preview 
    SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
    for (int pr = 0; pr < 4; ++pr) {
        for (int pc = 0; pc < 4; ++pc) {
            if (S[piesa_urmatoare_id][pr][pc]) {
                SDL_Rect rc = {
                    COLOANE * CELL + CELL + pc * (CELL/2),
                    pr * (CELL/2) + CELL,
                    CELL/2, CELL/2
                };
                SDL_RenderFillRect(renderer, &rc);
            }
        }
    }

    // Hold preview 
    SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
    if (piesa_hold_id >= 0) {
        for (int pr = 0; pr < 4; ++pr) {
            for (int pc = 0; pc < 4; ++pc) {
                if (S[piesa_hold_id][pr][pc]) {
                    SDL_Rect rc = {
                        COLOANE * CELL + CELL + pc * (CELL/2),
                        5 * CELL + pr * (CELL/2),
                        CELL/2, CELL/2
                    };
                    SDL_RenderFillRect(renderer, &rc);
                }
            }
        }
    }

 // STARE_MENIU
    switch (stare_joc) {
      case STARE_MENIU: {
          static int meniu_afisat = 0;
          if (!meniu_afisat) {
              const char *text =
                  "COMENZI TETRIS:\n"
                  "A / stanga  \n"
                  "D / dreapta  \n"
                  "W / roteste  \n"
                  "S / coboara jos  \n"
                  "H      : hold\n"
                  "P      : pauza\n"
                  "R      : resart\n"
                  "Q      : quit\n\n"
                  "Apasă ENTER pentru a incepe.";
              SDL_ShowSimpleMessageBox(
                  SDL_MESSAGEBOX_INFORMATION,
                  "Meniu Tetris",
                  text,
                  win
              );
              meniu_afisat = 1;
          }
          // ecran(negru) după stopare
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);
          SDL_RenderPresent(renderer);
          return;  // asteapta enter
      }
      default:
          break;
    }





    //  frame
    SDL_RenderPresent(renderer);

    // Actualizează titlul 
    {
        char titlu[128];
        if (stare_joc == STARE_PAUZA) {
            snprintf(titlu, sizeof titlu,
                     "Tetris SDL2 — Scor: %d — PAUZĂ", scor);
        }
        else if (stare_joc == STARE_JOC_PIERDUT) {
            snprintf(titlu, sizeof titlu,
                     "Tetris SDL2 — Scor: %d — GAME OVER", scor);
        }
        else {
            snprintf(titlu, sizeof titlu,
                     "Tetris SDL2 — Scor: %d", scor);
        }
        SDL_SetWindowTitle(win, titlu);
    }
}
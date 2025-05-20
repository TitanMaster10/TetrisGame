#include "graphics.h"
#include "input.h"
#include "tetris.h"
#include <stdio.h>

void sterge_ecran(void) { printf("\033[H\033[J"); }

void afiseaza_cadru(void) {
    sterge_ecran();

    const int (*sabloane_ptr)[4][4] = get_sabloane();
    switch (stare_joc) {
      case STARE_MENIU:
      { 
        printf(" ===TETRIS===\n\nApasă pe ENTER pentru a porni \n\nControls:W-rotate- S-setpos A-move left D- move right\nP for Pause\n");

        break;
      }
      case STARE_JOC:       
      case STARE_PAUZA: {
        for(int r = 0; r<RANDURI;r++){
            printf("|");
            for(int col=0;col<COLOANE;col++){
                char c =  tabla[r][col] ? '#':' ';
                for(int pr = 0 ; pr <4;pr++){
                    for(int pc=0;pc<4;pc++){
                        if(piesa_curenta.forma[pr][pc] && piesa_curenta.rand+pr == r && piesa_curenta.coloana+pc == col){
                            c = '@';
                        }
                    }
                }
                printf("%c",c);
            }
            printf("|\n");
        } 
        printf("===============\nSCOR: %d\n",scor);

        printf("\nURMATOAREA:\n");
        for(int pr=0;pr<4;pr++){
            printf(" ");
            for(int pc=0;pc<4;pc++){
                char ch = sabloane_ptr[piesa_urmatoare_id][pr][pc] ? '#':' ';
                printf("%c",ch);
            }
            printf("\n");
        }
        printf("\nHold (H) :\n");
        if(piesa_hold_id>=0){
            for(int pr=0;pr<4;pr++){
                printf(" ");
                 for(int pc=0;pc<4;pc++){
                    char ch = sabloane_ptr[piesa_hold_id][pr][pc] ? '#': ' ';
                    printf("%c",ch);
                 }
                 printf("\n");
            }
        }
        else
        {
            printf(" GOL \n");
        }
        
        if(stare_joc == STARE_PAUZA){
            printf("\n JOCUL ESTE IN PAUZA\nAPASA (p) pentru continuare (q) pentru iesire \n");
        }
        break;     
    }
      case STARE_JOC_PIERDUT: {
        printf("======GAME OVER======\n\nSCOR TOTAL: %d\n(r = restart, q= exit )\n",scor);       
        break;
     }
    }
}

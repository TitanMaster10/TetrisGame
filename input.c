// switch case cu tipurile de input date 
#include "input.h"
#include "tetris.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

static struct termios term_original;
StareJoc stare_joc = STARE_MENIU;


static int citeste_tasta_nonblock(void){
    char c;
    if(read(STDIN_FILENO, &c, 1) == 1)return (int)c;
    return -1;
}

void init_mod_input(void)     { 
    tcgetattr(STDIN_FILENO,  &term_original);
    struct termios t = term_original;
    t.c_lflag  &=~(ICANON | ECHO);
    t.c_cc[VMIN]  = 0;
    t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

}


void reseteaza_mod_input(void) { 
    tcsetattr(STDIN_FILENO, TCSANOW, &term_original);
}


void gestioneaza_input(void)   {
    int c = citeste_tasta_nonblock();
    if (c == -1 )return;
    switch (stare_joc){
        
        case STARE_MENIU:
            if(c == '\n' || c == '\r'){
                porneste_joc();
            }
            break;

        case STARE_JOC:
            if      ( c == 'q' ) stare_joc = STARE_JOC_PIERDUT ;
            else if ( c == 'p' ) stare_joc = STARE_PAUZA ;
            else if ( c == 'a' ) muta_piesa_stanga ()    ;
            else if ( c == 'd' ) muta_piesa_dreapta()    ;
            else if ( c == 'w' ) roteste_piesa() ;
            else if ( c == 's' ) coboara_piesa() ;

            else if ( c == 'h' ) comuta_hold  ();
            break;

        case STARE_PAUZA:
            if      ( c == 'p' ) stare_joc = STARE_JOC ;
            else if ( c == 'q' ) stare_joc = STARE_JOC_PIERDUT;
            break;

        case STARE_JOC_PIERDUT:
            if( c == 'r' ) porneste_joc();
            else if (c == 'q'){
                reseteaza_mod_input();
                exit(0); //a stdlib
            }
            break;
    }
}




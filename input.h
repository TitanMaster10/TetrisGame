#ifndef INPUT_H
#define INPUT_H



#include <SDL.h>
#include <stdbool.h>
#include "tetris.h"


extern int     quit_requested;
//extern StareJoc stare_joc;

// Poll SDL events & translate to mutări/rotiri/hold/pauză/restart/exit
void handle_input(void);
#endif


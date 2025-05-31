#ifndef GRAPHICS_H
#define GRAPHICS_H
/*
void sterge_ecran(void);
void afiseaza_cadru(void);
*/


#include <SDL.h>

// intitializare sdl game window si renderer
void init_graphics(void);

// curata resursele sdl
void destroy_graphics(void);

// deseneaza assest- tabla piesa curenta urmatoare si piesa hold
void afiseaza_cadru(void);
#endif

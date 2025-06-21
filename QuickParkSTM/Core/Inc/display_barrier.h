#ifndef DISPLAY_BARRIER_H
#define DISPLAY_BARRIER_H

#include "main.h"

// Inizializza tutto: display e sbarre
void display_init(void);

// Aggiorna il display con i posti liberi
void display_update(uint8_t free_spots);

// Azioni sbarre — ingresso
void barrier_open_entry(void);  // alza sbarra ingresso
void barrier_close_entry(void);   // abbassa sbarra ingresso

// Azioni sbarre — uscita
void barrier_open_exit(void);   // alza sbarra uscita
void barrier_close_exit(void);    // abbassa sbarra uscita

#endif // DISPLAY_BARRIER_H

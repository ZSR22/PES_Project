#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#define LUNGHEZZA_MASSIMA 50
#include <time.h>
#include "Lezioni.h"
typedef struct{
    unsigned int ID;
    Lezione lezione;
    char nome_partecipante[LUNGHEZZA_MASSIMA];
    char cognome_partecipante[LUNGHEZZA_MASSIMA];
} Prenotazione;

void visualizza_prenotazione(const Prenotazione prenotazione);

#endif
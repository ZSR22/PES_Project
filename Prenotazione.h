#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#define LUNGHEZZA_MASSIMA 50
#include <time.h>
typedef struct{
    unsigned int ID;
    char nome_lezione[LUNGHEZZA_MASSIMA];
    char nome_partecipante[LUNGHEZZA_MASSIMA];
    char cognome_partecipante[LUNGHEZZA_MASSIMA];
    time_t orario;
} Prenotazione;

void visualizza_prenotazione(const Prenotazione prenotazione);

#endif
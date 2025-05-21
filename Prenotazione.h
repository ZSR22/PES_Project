/* 
=============================================================================
 File: Prenotazioni.h
 Descrizione: Definizioni di struttura e prototipi per la gestione delle prenotazioni
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/
#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#define LUNGHEZZA_MASSIMA 50
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Lezioni.h"
#include "Utilities.h"
// Struttura rappresentante una singola prenotazione
typedef struct{
    unsigned int ID;
    Lezione lezione;
    char nome_partecipante[LUNGHEZZA_MASSIMA];
    char cognome_partecipante[LUNGHEZZA_MASSIMA];
} Prenotazione;

void visualizza_prenotazione(const Prenotazione prenotazione);

#endif
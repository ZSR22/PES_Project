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

#include "Lezioni.h"
#include "Utilities.h"
#include "abbonamenti.h"
// Struttura rappresentante una singola prenotazione
typedef struct{
    unsigned int ID;
    Lezione lezione;
    Cliente partecipante;
} Prenotazione;

void visualizza_prenotazione(const Prenotazione prenotazione);

#endif
/*
=============================================================================
 File: Lezioni.h
 Descrizione: Definizioni di strutture e prototipi per la gestione delle lezioni
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/
#ifndef LEZIONI_H
#define LEZIONI_H
#include <time.h>
#include "Utilities.h"
#define MAX_NOME 50
#define  CAPACITÀ_INIZIALE 4

// Struttura rappresentante una singola lezione
typedef struct{
    unsigned int ID;
    char nome[MAX_NOME];
    int max_posti;
    time_t data;
} Lezione;

// Struttura rapprensentante un catalogo dinamico di lezioni
typedef struct{
    Lezione* lezione;
    int numero_lezioni;
    size_t capacità; // dimensione allocata dell'array
} Catalogo_Lezioni;

void inizializza_catalogo(Catalogo_Lezioni* catalogo);
void aggiungi_lezione(Catalogo_Lezioni* catalogo, const Lezione nuova_lezione);
void elimina_lezione(Catalogo_Lezioni* catalogo, const Lezione lezione_da_eliminare);
void mostra_lezioni(const Catalogo_Lezioni catalogo);
const Lezione* trova_lezione(const Catalogo_Lezioni* catalogo, Lezione lezione);
#endif
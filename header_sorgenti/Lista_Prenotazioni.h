/* 
=============================================================================
 File: Lista_Prenotazioni.h
 Descrizione: Definizioni per la gestione delle prenotazioni in lista collegata
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/

#ifndef LISTA_PRENOTAZIONI_H
#define LISTA_PRENOTAZIONI_H
#include <stdbool.h>
#include "abbonamenti.h"
#include "Lezioni.h"
#include "Prenotazione.h"
// Struttura rappresentante un nodo della lista collegata
typedef struct NodoPrenotazione {
    Prenotazione prenotazione;
    struct NodoPrenotazione* next;
} NodoPrenotazione;

typedef NodoPrenotazione* Lista_Prenotazioni;

Lista_Prenotazioni* crea_lista_prenotazioni();
bool aggiungi_prenotazione(Lista_Prenotazioni* lista, const Prenotazione prenotazione);
bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione);
void visualizza_prenotazioni(const Lista_Prenotazioni* lista);
void libera_lista_prenotazioni(Lista_Prenotazioni* lista);
int conteggia_prenotazioni( const Lista_Prenotazioni* lista, const Lezione* lezione); 
bool lezione_piena(const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare);
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante);
Prenotazione* trova_prenotazione(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante);
bool cliente_prenotato(const Lista_Prenotazioni lista, const Cliente partecipante);
bool lezione_prenotata(const Lista_Prenotazioni lista, const Lezione lezione);

#endif
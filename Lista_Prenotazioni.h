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
#include "Prenotazione.h"
// Struttura rappresentante un nodo della lista collegata
typedef struct{
    Prenotazione prenotazione;
    struct nodo_prenotazione* next;
} NodoPrenotazione;

typedef NodoPrenotazione* Lista_Prenotazioni;

Lista_Prenotazioni crea_lista_prenotazioni();
void aggiungi_prenotazione(Lista_Prenotazioni* lista, const Prenotazione prenotazione);
bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione);
void visualizza_prenotazioni(const Lista_Prenotazioni lista);
void libera_lista_prenotazioni(Lista_Prenotazioni* lista);
int conteggia_prenotazioni( const Lista_Prenotazioni* lista, const Lezione* lezione); // Dovrà contare quante prenotazioni effettuate per orario e lezione
bool lezione_piena(const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare);// valore True se la lezione scelta ha raggiunto gli iscritti massimi
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante);// Controlla se esiste già una prenotazione nello stesso orario e stessa lezione
Prenotazione* trova_prenotazione(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante);

#endif
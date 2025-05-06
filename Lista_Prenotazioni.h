#ifndef LISTA_PRENOTAZIONI_H
#define LISTA_PRENOTAZIONI_H
#include "Prenotazione.h"
#include <stdbool.h>


typedef struct{
    Prenotazione prenotazione;
    struct nodo* next;
} Nodo;

typedef Nodo* Lista_Prenotazioni;
Lista_Prenotazioni crea_lista_prenotazioni();
void aggiungi_Prenotazione(Lista_Prenotazioni* lista, Prenotazione prenotazione);
bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione);
void visualizza_prenotazioni(const Lista_Prenotazioni lista);
void libera_lista_prenotazioni(Lista_Prenotazioni* lista);
int conteggia_prenotazioni( const Lista_Prenotazioni lista, const Lezione lezione); // Dovrà contare quante prenotazioni effettuate per orario e lezione
bool lezione_piena(const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare);// valore True se la lezione scelta ha raggiunto gli iscritti massimi
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const char* nome, const char* cognome);// Controlla se esiste già una prenotazione nello stesso orario e stessa lezione


#endif
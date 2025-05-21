/*
    File: abbonamenti.h
    Descrizione: File di intestazione per la gestione degli abbonamenti
    Autore: Salvatore Zurino
    Data: 14/05/2025
    Versione: 1.2
 */
#ifndef ABBONAMENTI_H
#define ABBONAMENTI_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char nome[20];
    char cognome[20];
    char codice_fiscale[16];
    char data_nascita[11];
    int durata; // la durata dell'abbonamento in giorni percio la facciamo con l' intero
    time_t data_inizio; // la data di inizio dell'abbonamento
    unsigned int id_abbonamento; // il numero dell'abbonamento
    } Cliente;
typedef struct Nodo {
    Cliente cliente;
    struct Nodo* sx;
    struct Nodo* dx;
} Nodo;

Nodo* inserisci_cliente(Nodo* radice, Cliente c);
int abbonamento_valido(Cliente c);
void stampa_clienti_ordinati(Nodo* radice);
void libera_clienti(Nodo* radice);
Nodo* ricerca_cliente(Nodo* radice, const char* codice_fiscale);
void ricerca_e_verifica_cliente(Nodo* radice, const char* codice_fiscale);

#endif

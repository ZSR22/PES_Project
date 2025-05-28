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

// lunghezza stringa nome e cognome
#define MAX_CHAR 20
// lunghezza stringa codice fiscale
#define MAX_CF 16
// lunghezza stringa data nascita
#define MAX_DN 11

typedef struct {
    char nome[MAX_CHAR];
    char cognome[MAX_CHAR];
    char codice_fiscale[MAX_CF];
    char data_nascita[MAX_DN];
    int durata; // la durata dell'abbonamento in giorni percio la facciamo con l' intero
    time_t data_inizio; // la data di inizio dell'abbonamento
    unsigned int id_abbonamento; // il numero dell'abbonamento
    } Cliente;
typedef struct NodoAlbero {
    Cliente cliente;
    struct NodoAlbero* sx;
    struct NodoAlbero* dx;
} NodoAlbero;



NodoAlbero* inserisci_cliente(NodoAlbero* radice, Cliente c);
int abbonamento_valido(Cliente c);
void stampa_clienti_ordinati(NodoAlbero* radice);
void libera_clienti(NodoAlbero* radice);
NodoAlbero* ricerca_cliente(NodoAlbero* radice, const char* codice_fiscale);
void ricerca_e_verifica_cliente(NodoAlbero* radice, const char* codice_fiscale);
NodoAlbero* elimina_cliente(NodoAlbero* radice, const char* codice_fiscale);

#endif

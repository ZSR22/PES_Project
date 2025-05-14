/*
    File: abbonamenti.h
    Descrizione: File di intestazione per la gestione degli abbonamenti
    Autore: Salvatore Zurino
    Data: 14/05/2025
    Versione: 1.1
 */
#include <time.h>


typedef struct {
    char nome[20];
    char cognome[20];
    char codice_fiscale[16];
    char data_nascita[11];
    int durata; // la durata dell'abbonamento in giorni percio la facciamo con l' intero
    time_t data_inizio; // la data di inizio dell'abbonamento
    unsigned int id_abbonamento; // il numero dell'abbonamento
    } Cliente;

Nodo* inserisci_cliente();
Cliente* cerca_cliente();
int abbonamento_valido();
void stampa_clienti_ordinati();
void libera_clienti();

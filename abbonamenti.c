#include "abbonamenti.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[20];
    char cognome[20];
    char codice_fiscale[16];
    char data_nascita[11];
    int durata; // la durata dell'abbonamento in giorni percio la facciamo con l' intero
    time_t data_inizio; // la data di inizio dell'abbonamento
    unsigned int id_abbonamento; // il numero dell'abbonamento
    } Cliente;

typedef struct nodo {
    Cliente cliente;
    struct nodo* sx;
    struct nodo* dx;
} Nodo;

Nodo* crea_nodo(Cliente c) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovo == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    nuovo->cliente = c;
    nuovo->sx = NULL;
    nuovo->dx = NULL;
    fprintf("Cliente %s %s è stato salvato con successo\n", c.nome, c.cognome);
    return nuovo;
}

Nodo* inserisci_cliente(Nodo* radice, Cliente c) {
    if (radice == NULL) {
        return crea_nodo(c);
    }
    if (nuovo.id < radice->cliente.id_abbonamento){
        radice->sx = inserisci_cliente(radice->sx, c);
    } else if (nuovo.id > radice->cliente.id_abbonamento) {
        radice->dx = inserisci_cliente(radice->dx, c);
    } else {
        fprintf(stderr, "ID abbonamento già esistente\n");
    }
    return radice;
}

int abbonamento_valido(Cliente c) {
    time_t ora = time(NULL); // ottiene l'ora corrente
    int giorni_passati = difftime(ora, c.data_inizio)/ (60 * 60 * 24);// calcola i giorni passati dall'inizio dell'abbonamento con la differenza di tempo e la conversione in giorni
    if (giorni_passati < 0) {
        fprintf(stderr, "Data di inizio non valida\n");
        return 0;
    }
    return giorni_passati <= c.durata; // Se i giorni passati sono minori o uguali alla durata dell'abbonamento, è valido
}

void stampa_clienti_ordinati(Nodo* radice) {
    if (radice != NULL) {
        stampa_clienti_ordinati(radice->sx);
        printf("Nome: %s\t Cognome: %s\t ID: %u\t Valido:%s\n\n", radice->cliente.nome, radice->cliente.cognome, radice->cliente.id_abbonamento, abbonamento_valido(radice->cliente) ? "SI" : "NO");
        stampa_clienti_ordinati(radice->dx);
    }else {
        fprintf(stderr, "Nessun cliente trovato\n");
    }
    return;
}

void libera_clienti(Nodo* radice) {
    if (radice != NULL) {
        libera_clienti(radice->sx);
        libera_clienti(radice->dx);
        free(radice);
    }
    return;
}
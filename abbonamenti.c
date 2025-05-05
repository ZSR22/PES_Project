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
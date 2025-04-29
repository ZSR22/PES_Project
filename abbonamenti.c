//  * File: abbonamenti.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

/* Creazione di un albero binario di ricerca per gestire gli abbonamenti*/

typedef struct Nodo {
    Cliente cliente;
    struct Nodo* sinistro;
    struct Nodo* destro;
    int altezza;
} Nodo;


/*
    specifica sintattica: Nodo* inserisci(Nodo* radice, Cliente nuovoCliente);
    specifica semantica: inserisce un nuovo cliente nell'albero binario di ricerca
    precondizione: radice è un puntatore alla radice dell'albero
    postcondizione: l'albero è bilanciato e il nuovo cliente è stato inserito
*/

void inserisci(Nodo** radice, Cliente nuovoCliente) {
    if (*radice == NULL) {
        *radice = (Nodo*)malloc(sizeof(Nodo));
        (*radice)->cliente = nuovoCliente;
        (*radice)->sinistro = NULL;
        (*radice)->destro = NULL;
        (*radice)->altezza = 1; 
    } else if (strcmp(nuovoCliente.nome, (*radice)->cliente.nome) < 0) {
        inserisci(&(*radice)->sinistro, nuovoCliente);
    } else if (strcmp(nuovoCliente.nome, (*radice)->cliente.nome) > 0) {
        inserisci(&(*radice)->destro, nuovoCliente);
    }
}
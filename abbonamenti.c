/*
    File: abbonamenti.c
    Descrizione: Funzioni per la gestione degli abbonamenti
    Autore: Salvatore Zurino
    Data: 14/05/2025
    Versione: 1.2

*/

#include "abbonamenti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creazione di un albero binario di ricerca per la memorizzazione dei clienti
typedef struct nodo {
    Cliente cliente;
    struct nodo* sx;
    struct nodo* dx;
} Nodo;

/*
Funzione crea_nodo
----------------
restituisce il nuovo nodo compilato dell'albero binario

Parametri:
    Cliente c

Precondizione:
    Devono essere stati dati tutti i dati del cliente

Post condizione:
    ritorna il nodo creato
*/
Nodo* crea_nodo(Cliente c) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    // controlla se l' allocazione è avvenuta con successo
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

/*
Funzione inserisci_cliente
----------------
    inserisce un cliente nell' albero binario di ricerca
    se l' albero è vuoto crea un nuovo nodo
    se l' albero non è vuoto inserisce il cliente in modo ordinato
    in base al codice fiscale
    se il cliente è già presente restituisce il nodo esistente
    se non è stato possibile allocare memoria restituisce NULL
Parametri:
    Radice albero binario
    Cliente c

Precondizione:
    Devono essere stati dati tutti i dati del cliente
    La radice dell'albero binario non deve essere NULL

Post condizione:
    ritorna il nodo creato
    se già presente restituisce il nodo esistente
    restituisce NULL se non è stato possibile allocare memoria
    se l' albero è vuoto crea un nuovo nodo
    se l' albero non è vuoto inserisce il cliente in modo ordinato
    in base al codice fiscale
*/
Nodo* inserisci_cliente(Nodo* radice, Cliente c) {
    if (radice == NULL) {
        Nodo* nuovo = crea_nodo(c);
        return nuovo; 
    }
    /*
    abbiamo deciso di ordinare i clienti in base al codice fiscale perchè
    univoco ed in questo modo non ci sono problemi di duplicati o di ordinamento
    */
   int cmp = strcmp(c.codice_fiscale, radice->cliente.codice_fiscale);
    if (cmp < 0){
        radice->sx = inserisci_cliente(radice->sx, c);
    } else if (cmp > 0) {
        radice->dx = inserisci_cliente(radice->dx, c);
    } else {
        fprintf(stderr, "ID abbonamento già esistente\n");
    }
    return radice;
}
/*
Funzione abbonamento_valido
----------------
    ritorna 1 se l' abbonamento è valido
    ritorna 0 se l' abbonamento non è valido
    stampa un errore se la data di inizio non è valida
    calcola i giorni passati dall' inizio dell' abbonamento
    controlla se i giorni passati sono minori o uguali alla durata dell' abbonamento
    se si ritorna 1 altrimenti ritorna 0    

Parametri:
    Cliente c

Precondizione:
    Devono essere stati dati tutti i dati del cliente

Post condizione:
    ritorna 1 se l' abbonamento è valido
    ritorna 0 se l' abbonamento non è valido
    stampa un errore se la data di inizio non è valida
*/
int abbonamento_valido(Cliente c) {
    time_t ora = time(NULL); // ottiene l'ora corrente
    int giorni_passati = difftime(ora, c.data_inizio)/ (60 * 60 * 24);// calcola i giorni passati dall'inizio dell'abbonamento con la differenza di tempo e la conversione in giorni
    if (giorni_passati < 0) {
        fprintf(stderr, "Data di inizio non valida\n");
        return 0;
    }
    return giorni_passati <= c.durata; // Se i giorni passati sono minori o uguali alla durata dell'abbonamento, è valido
}
/*
Funzione stampa_clienti_ordinati
----------------
    stampa i clienti ordinati in base al codice fiscale
    stampa il nome, cognome, id abbonamento e se l' abbonamento è valido o meno
    se l' albero è vuoto stampa un errore

Parametri:
    Radice albero binario

Precondizione:
    la radice dell'albero binario non deve essere NULL

Post condizione:
    nessuna la funzione non modifica l' albero binario
*/

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
/*
Funzione stampa_clienti_ordinati
----------------
    libera la memoria allocata per l' albero binario
    se l' albero è vuoto stampa un errore  

Parametri:
    Radice albero binario

Precondizione:
    la radice dell'albero binario non deve essere NULL
    l' albero binario deve essere stato creato
    l' albero binario deve essere stato popolato

Post condizione:
    libera la memoria allocata per l' albero binario
    se l' albero è vuoto stampa un errore
    la funzione non restituisce nulla

*/
void libera_clienti(Nodo* radice) {
    if (radice != NULL) {
        libera_clienti(radice->sx);
        libera_clienti(radice->dx);
        free(radice);
    }
    return;
}
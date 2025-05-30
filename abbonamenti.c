/*
=====================================================
    File: abbonamenti.c
    Descrizione: Funzioni per la gestione degli abbonamenti
    Autore: Salvatore Zurino
    Data: 14/05/2025
    Versione: 1.2
=======================================================
*/

#include "abbonamenti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creazione di un albero binario di ricerca per la memorizzazione dei clienti

/**
 * Crea un nuovo nodo dell'albero binario di ricerca con un cliente.
 * 
 * Questa funzione alloca memoria per un nuovo nodo, inizializza il cliente e i puntatori ai figli sinistro e destro.
 * Se l'allocazione della memoria fallisce, il programma termina con un messaggio di errore.
 * 
 * @param c Cliente da inserire nel nodo.
 * @return Puntatore al nuovo nodo creato.
 * 
 * Precondizione:
 * - Il cliente deve essere valido e non NULL.
 * side effects:
 * - Stampa un messaggio di errore se l'allocazione della memoria fallisce.
 * - Stampa un messaggio di successo quando il cliente viene salvato con successo.
 */
NodoAlbero* crea_nodo(Cliente c) {
NodoAlbero* nuovo = (NodoAlbero*)malloc(sizeof(NodoAlbero));
    // controlla se l' allocazione è avvenuta con successo
    if (nuovo == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    nuovo->cliente = c;
    nuovo->sx = NULL;
    nuovo->dx = NULL;
    printf("===========================\n");
    printf("Cliente %s %s è stato salvato con successo\n", c.nome, c.cognome);
    return nuovo;
}

/**
 * Inserisce un cliente nell'albero binario di ricerca.
 * 
 * Questa funzione inserisce un nuovo cliente nell'albero binario di ricerca in base al codice fiscale.
 * Se il nodo corrente è NULL, viene creato un nuovo nodo con il cliente.
 * Se il codice fiscale del cliente è minore del nodo corrente, la funzione ricorsivamente inserisce il cliente nel sottoalbero sinistro.
 * Se il codice fiscale del cliente è maggiore, viene inserito nel sottoalbero destro.
 * Se il codice fiscale del cliente esiste già, viene stampato un messaggio di errore.  
 * 
 * @param radice Puntatore alla radice dell'albero.
 * @param c Cliente da inserire.
 * @return La nuova radice dell'albero dopo l'inserimento.
 * Precondizione:
 * - La radice dell'albero non deve essere NULL.
 * side effects:
 * - Stampa un messaggio di errore se il codice fiscale del cliente esiste già.
 * - Stampa un messaggio di successo se il cliente è stato inserito correttamente.
 */
NodoAlbero* inserisci_cliente(NodoAlbero* radice, Cliente c) {
    if (radice == NULL) {
        NodoAlbero* nuovo = crea_nodo(c);
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
        printf("===========================\n");
        printf("\n");
        fprintf(stderr, "Codice fiscale già in uso\n");
        printf("\n");
        return NULL;
    }
    return radice;
}
/**
 * Verifica se l'abbonamento di un cliente è ancora valido.
 * 
 * Questa funzione calcola la differenza tra la data corrente e la data di inizio dell'abbonamento
 * del cliente, e confronta il numero di giorni trascorsi con la durata dell'abbonamento.
 * Se i giorni trascorsi sono minori o uguali alla durata, l'abbonamento è considerato valido.
 * 
 * @param c Cliente da verificare.
 * @return 1 se l'abbonamento è valido, 0 altrimenti.
 * Precondizione:
 * - La data di inizio dell'abbonamento deve essere valida e non nel futuro.
 * side effects:
 * - Stampa un messaggio di errore se la data di inizio non è valida.
 * @return 1 se l'abbonamento è valido, 0 altrimenti.
 */
int abbonamento_valido(Cliente c) {
    time_t ora = time(NULL); // ottiene l'ora corrente
    int giorni_passati = difftime(ora, c.data_inizio)/ (60 * 60 * 24);// calcola i giorni passati dall'inizio dell'abbonamento con la differenza di tempo e la conversione in giorni
    if (giorni_passati < 0) {
        fprintf(stderr, "Data di inizio non valida\n");
        return 0;
    }
    return (giorni_passati <= c.durata) ? 1 : 0; // Se i giorni passati sono minori o uguali alla durata dell'abbonamento, è valido
}
/**
 * Stampa i clienti in ordine crescente in base al codice fiscale.
 *
 * Questa funzione esegue una visita in-order dell'albero binario di ricerca e stampa i dettagli dei clienti.
 * I clienti vengono stampati in ordine crescente in base al loro codice fiscale.
 * Se l'albero è vuoto, viene stampato un messaggio di errore.
 * 
 * @param radice Puntatore alla radice dell'albero binario di ricerca.
 * Precondizione:
 * - La radice dell'albero non deve essere NULL.
 * side effects:
 * - Stampa i dettagli dei clienti in ordine crescente.
 * - Se l'albero è vuoto, stampa un messaggio di errore.
 */

void stampa_clienti_ordinati(NodoAlbero* radice) {

    if(radice == NULL){ return;}

    stampa_clienti_ordinati(radice->sx);

    printf("Nome: %s\n Cognome: %s\n ID: %u\n Valido:%s\n",
        radice->cliente.nome,
        radice->cliente.cognome,
        radice->cliente.id_abbonamento,
        abbonamento_valido(radice->cliente) ? "SI" : "NO");
    printf("\n");
    stampa_clienti_ordinati(radice->dx);   
        
}
/**
 * Cancella ricorsivamente tutti i nodi dell'albero binario di ricerca.
 * 
 * Questa funzione libera la memoria allocata per ogni nodo dell'albero binario di ricerca.
 * Viene chiamata ricorsivamente per i nodi sinistro e destro, e infine libera il nodo corrente.
 * 
 * @param radice Puntatore alla radice dell'albero da liberare.
 * Precondizione:
 * - La radice dell'albero non deve essere NULL.
 * side effects:
 * - Libera la memoria allocata per tutti i nodi dell'albero binario di ricerca.
 */
void libera_clienti(NodoAlbero* radice) {
    if (radice != NULL) {
        libera_clienti(radice->sx);
        libera_clienti(radice->dx);
        free(radice);
    }
    return;
}


/**
 * Cerca un cliente nell'albero binario di ricerca in base al codice fiscale.
 * 
 * Questa funzione esegue una ricerca ricorsiva nell'albero binario per trovare un cliente
 * con un codice fiscale specifico. Se il cliente viene trovato, viene restituito il nodo corrispondente.
 * @param radice Puntatore alla radice dell'albero.
 * @param codice_fiscale Codice fiscale del cliente da cercare.
 * @return Puntatore al nodo del cliente trovato, o NULL se il cliente non esiste nell'albero.	
 * Precondizione:
 * - La radice dell'albero non deve essere NULL.
 * side effects: Nessuno.
 */
NodoAlbero* ricerca_cliente(NodoAlbero* radice, const char* codice_fiscale) {
    if (!radice) return NULL;
    int cmp = strcmp(codice_fiscale, radice->cliente.codice_fiscale);
    if (cmp == 0) return radice;
    else if (cmp < 0) return ricerca_cliente(radice->sx, codice_fiscale);
    else return ricerca_cliente(radice->dx, codice_fiscale);
}

/**
 * Stampa i dettagli di un cliente cercato nell'albero binario.	
 * 
 * @param radice Puntatore alla radice dell'albero.
 * @param codice_fiscale Codice fiscale del cliente da cercare.
 * @return Nessun valore restituito.
 * Precondizione:
 * - La radice dell'albero non deve essere NULL.`
 * side effects: Stampa i dettagli del cliente trovato o un messaggio di errore se non trovato.
 */
void ricerca_e_verifica_cliente(NodoAlbero* radice, const char* codice_fiscale) {
    NodoAlbero* trovato = ricerca_cliente(radice, codice_fiscale);
    if (trovato) {
        printf("Nome: %s\nCognome: %s\nCodice Fiscale: %s\nValido: %s\n",
               trovato->cliente.nome,
               trovato->cliente.cognome,
               trovato->cliente.codice_fiscale,
               abbonamento_valido(trovato->cliente) ? "SI" : "NO");
    } else {
        printf("Cliente non trovato\n");
    }
}


/**
 * Trova il nodo con il valore minimo nell'albero a partire da un nodo specificato.	
 * 
 * @param radice Puntatore alla radice dell'albero.
 * @return Puntatore al nodo con il valore minimo.
 */
static NodoAlbero* trova_minimo(NodoAlbero* nodo) {
    while (nodo->sx != NULL)
        nodo = nodo->sx;
    return nodo;
}

/**
 * Elimina un cliente dall'albero in base al codice fiscale.
 * 
 * @param radice Puntatore alla radice dell'albero.
 * @param codice_fiscale Codice fiscale del cliente da eliminare.
 * @return La nuova radice dell'albero dopo l'eliminazione.
 */
NodoAlbero* elimina_cliente(NodoAlbero* radice, const char* codice_fiscale) {
    if (radice == NULL)
        return NULL;
    int confronto = strcmp(codice_fiscale, radice->cliente.codice_fiscale);
    if (confronto < 0) {
        radice->sx = elimina_cliente(radice->sx, codice_fiscale);
    } else if (confronto > 0) {
        radice->dx = elimina_cliente(radice->dx, codice_fiscale);
    } else {
        if (radice->sx == NULL && radice->dx == NULL) {
            free(radice);
            return NULL;
        }
        if (radice->sx == NULL) {
            NodoAlbero* temp = radice->dx;
            free(radice);
            return temp;
        } else if (radice->dx == NULL) {
            NodoAlbero* temp = radice->sx;
            free(radice);
            return temp;
        }
        NodoAlbero* successore = trova_minimo(radice->dx);
        radice->cliente = successore->cliente;
        radice->dx = elimina_cliente(radice->dx, successore->cliente.codice_fiscale);
    }

    return radice;
}
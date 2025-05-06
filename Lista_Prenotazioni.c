#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista_Prenotazioni.h"

// Inizializza una lista vuota
Lista_Prenotazioni crea_lista_prenotazioni(){
    return NULL;
}

void aggiungi_prenotazione(Lista_Prenotazioni* lista, Prenotazione prenotazione){

    // Se la lezione è al numero massimo di partecipanti interromperà la creazione della prenotazione
    if(lezione_piena(*lista, prenotazione.lezione)){
        fprintf(stderr, "La lezione selezionata ha raggiunto il numero massimo di partecipanti. \n");
        return;
    }

    // Se un utente prova a prenotare più volte la stessa lezione e allo stesso orario, interromperà la creazione della prenotazione 
    if(controllo_conflitto_orario(*lista, prenotazione.lezione, prenotazione.nome_partecipante, prenotazione.cognome_partecipante)){
        fprintf(stderr, "Utente già prenotato.\n");
        return;
    } 

    // Alloca un nuovo nodo da aggiungere alla lista
    Nodo* nuovo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if(nuovo_nodo == NULL){
        fprintf(stderr, "Errore di allocazione memoria!!\n");
        exit(EXIT_FAILURE);
    }
    
    //Inizializza il nodo con la prenotazione da aggiungere
    nuovo_nodo->prenotazione = prenotazione;
    nuovo_nodo->next = NULL;
    
    // Se la lista è inizialmente vuota, inserisce il nuovo nodo come primo elemento
    if(lista == NULL){
        *lista = nuovo_nodo;
    } else{
        Nodo* nodo_corrente = *lista;
        while (nodo_corrente->next != NULL) // Altrimenti scorre la lista fino alla fine
        {
            nodo_corrente = nodo_corrente->next; 
        }
        
        nodo_corrente->next = nuovo_nodo; // Aggiunge il nodo alla fine della lista
        
    }
}

bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione){

    if(lezione == NULL || lista == NULL){
        
        fprintf(stderr, "Lezione non presente o lista prenotazioni vuota");
        return false; // Se la lezione e la lista non sono valide
    } 

    Nodo* nodo_corrente = *lista;
    Nodo* nodo_precedente = NULL;
    
    // Scorre la lista finoa lla fine
    while(nodo_corrente != NULL){

        // Controlla ID e data della prenotazione con quella della lezione indicata
        if(nodo_corrente->prenotazione.lezione.ID == lezione->ID && nodo_corrente->prenotazione.lezione.data == lezione->data){
            
            // Controlla se il primo nodo della lista è da eliminare
            if(nodo_precedente == NULL){
                *lista = nodo_corrente->next; // Aggiorna il puntatore alla testa della lista
            } else{
                nodo_precedente->next = nodo_corrente->next; // Altrimenti salta al nodo corrente
            }
            
            free(nodo_corrente);
            return true; // La prenotazione è stata cancellata
        }

        // Avanza al nodo successivo
        nodo_precedente = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
    }

    // Nessuna prenotazione trovata corrispondente alla lezione indicata
    return false;
}

// DA IMPLEMENTARE CON INTERFACCIA GRAFICA(DA DECIDERE)
void visualizza_prenotazioni(const Lista_Prenotazioni lista){

}

void libera_lista_prenotazioni(Lista_Prenotazioni* lista){
    
    Nodo* nodo_corrente;
    
    // Scorre fino alla fine della lista
    while(*lista != NULL){
        // Salva il puntatore al nodo corrente
        nodo_corrente = *lista;

        // Sposta la testa della lista al nodo successivo
        *lista = (*lista)->next;

        // Libera la memoria allocata per il nodo corrente
        free(nodo_corrente);
    }
}

int conteggia_prenotazioni( const Lista_Prenotazioni* lista, const Lezione* lezione){
    
    if (lista == NULL || lezione == NULL) {
        
        fprintf(stderr, "Errore: lezione o lista non validi. \n");
        exit(EXIT_FAILURE); // Se i puntatori non sono entrambi validi esce dal programma
    }

    // Inizializza a 0 il conteggio delle prenotazioni e associa a un nodo la testa della lista
    int conteggio = 0; 
    Nodo* corrente = *lista;

    // Scorre tutta la lista
    while (corrente != NULL) {
        if (corrente->prenotazione.lezione.ID == lezione->ID &&
            corrente->prenotazione.lezione.data == lezione->data) {
            conteggio++; // Se trova una prenotazione aggiorna conteggio
        }
        corrente = corrente->next; // Passa al nodo successivo
    }

    return conteggio;
}

bool lezione_piena(const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare){
    
    // Conteggia il numero di prenotazioni
    int prenotazioni = conteggia_prenotazioni(&lista, &lezione_da_analizzare);
    
    // Se la lezione è piena riporterà true altrimenti false
    if(prenotazioni >= lezione_da_analizzare.max_posti){
        return true;
    } else{
        return false;
    }
}

bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const char* nome, const char* cognome){

    // Associa  a un nodo la testa della lista e scorre la lista
    Nodo* nodo_corrente = lista;
    while(nodo_corrente != NULL){
        
        // Verifica se la data coincide con quella della nuova lezione
        if(lista->prenotazione.lezione.data == lezione.data){
            
            // Confronta nome e cognome del partecipante
            if(strcmp(lista->prenotazione.nome_partecipante, nome) == 0 && strcmp(lista->prenotazione.cognome_partecipante, cognome) == 0){
                
                return true; // Restituisce true se trova un conflitto
            }
        }

        nodo_corrente = nodo_corrente->next; // Passa al nodo successivo
    }

    return false;

}
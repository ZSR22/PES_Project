/* 
=============================================================================
 File: Lista_Prenotazioni.c
 Descrizione: Gestione delle prenotazioni tramite lista collegata
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/

#include "Lista_Prenotazioni.h"

/*
  crea_lista_prenotazioni

  Crea una nuova lista di prenotazioni vuota

  -Pre: Nessuna

  -Post: restituisce una lista inizializzata a NULL
 */
Lista_Prenotazioni crea_lista_prenotazioni(){
    return NULL;
}

/*
  aggiungi_prenotazione
  
  Aggiunge una prenotazione alla lista, controllando capienza e conflitti
  
  -Parametri:
    Lista_Prenotazioni* lista, Prenotazione prenotazione  

  -Pre: lista != NULL

  -Post: prenotazione aggiunta in coda alla lista
 */
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

    
    Nodo* nuovo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if(nuovo_nodo == NULL){
        fprintf(stderr, "Errore di allocazione memoria!!\n");
        return;
    }
    
    
    nuovo_nodo->prenotazione = prenotazione;
    nuovo_nodo->next = NULL;
    
    // Se la lista è inizialmente vuota, inserisce il nuovo nodo come primo elemento
    if(lista == NULL){
        *lista = nuovo_nodo;
    } else{
        Nodo* nodo_corrente = *lista;
        while (nodo_corrente->next != NULL) // Altrimenti scorre la lista e aggiunge il nodo in coda
        {
            nodo_corrente = nodo_corrente->next; 
        }
        
        nodo_corrente->next = nuovo_nodo; 
        
    }
}

/*
  disdici_prenotazione

  Rimuove una prenotazione dalla lista sulla base della lezione: ricercata per data e ID

  -Parametri:
    Lista_Prenotazioni* lista, const Lezione* lezione

  Pre: lista != NULL, lezione valida

  Post: riporta True se la prenotazione è stata trovata e rimossa altrimenti False se non è stata trovata oppure la lezione non è valida o la lista prenotazioni è vuota
 */
bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione){

    if(lezione == NULL || lista == NULL){
        
        fprintf(stderr, "Lezione non valida o lista prenotazioni vuota\n");
        return false; 
    }    
    Nodo* nodo_corrente = *lista;
    Nodo* nodo_precedente = NULL;
    
   
    while(nodo_corrente != NULL){

        
        if(nodo_corrente->prenotazione.lezione.ID == lezione->ID && nodo_corrente->prenotazione.lezione.data == lezione->data){
            
            // Controlla se il primo nodo della lista è da eliminare
            if(nodo_precedente == NULL){
                *lista = nodo_corrente->next; // Aggiorna il puntatore alla testa della lista
            } else{
                nodo_precedente->next = nodo_corrente->next; // Altrimenti salta al nodo corrente
            }
            
            free(nodo_corrente);
            return true;
        }    
        // Avanza al nodo successivo
        nodo_precedente = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
    }

    fprintf(stderr, "Prenotazione non trovata\n");
    return false;
}

/*
  visualizza_prenotazioni

  Stampa a video tutte le prenotazioni presenti nella lista

  -Parametri:
    const Lista_Prenotazioni lista

  -Pre: lista valida

  -Post: per ogni prenotazione vengono mostrati ID, nome, cognome, lezione e data, se la lista è vuota stamperà un messaggio di errore
 */
void visualizza_prenotazioni(const Lista_Prenotazioni lista){
    if(lista == NULL){
        fprintf(stderr, "La lista è vuota\n");
        return;
    }
    Nodo* nodo_corrente = lista;
    while (nodo_corrente != NULL)
    {
        visualizza_prenotazione(nodo_corrente->prenotazione);
        nodo_corrente = lista->next;
    }
    
}

/*
  libera_lista_prenotazioni

  Libera tutta la memoria allocata per la lista

  -Parametri:
    Lista_Prenotazioni* lista

  -Pre: lista != NULL

  -Post: lista vuota, memoria liberata
 */
void libera_lista_prenotazioni(Lista_Prenotazioni* lista){
    
    Nodo* nodo_corrente;
    
    
    while(*lista != NULL){
        
        nodo_corrente = *lista;
        *lista = (*lista)->next;
        free(nodo_corrente);
    }
}

/*
  conteggia_prenotazioni

  Conta il numero di prenotazioni per una lezione specifica: ricercata per data e ID

  -Parametri:
    const Lista_Prenotazioni* lista, const Lezione* lezione

  -Pre: lista e lezione validi

  -Post: ritorna il numero di prenotazioni trovate
 */
int conteggia_prenotazioni( const Lista_Prenotazioni* lista, const Lezione* lezione){
    
    if (lista == NULL || lezione == NULL) {
        
        fprintf(stderr, "Errore: lezione o lista non validi. \n");
        return -1; // Se i puntatori non sono entrambi validi riporterà -1 segnalando un errore
    }

    
    int conteggio = 0; 
    Nodo* corrente = *lista;

    
    while (corrente != NULL) {
        if (corrente->prenotazione.lezione.ID == lezione->ID &&
            corrente->prenotazione.lezione.data == lezione->data) {
            conteggio++; 
        }
        corrente = corrente->next; 
    }

    return conteggio;
}

/*
  lista_piena
  Verifica se una lezione ha raggiunto il numero massimo di prenotazioni

  -Parametri:
    const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare

  -Pre: lista valida, lezione esistente

  -Post: True se la lezione è al completo, altrimenti False
 */
bool lezione_piena(const Lista_Prenotazioni lista, const Lezione lezione_da_analizzare){
    
    
    int prenotazioni = conteggia_prenotazioni(&lista, &lezione_da_analizzare);
    
    
    if(prenotazioni >= lezione_da_analizzare.max_posti){
        return true;
    } else{
        return false;
    }
}
/*
  controllo_conflitto_orario

  Verifica se un partecipante ha già una lezione nello stesso orario

  -Parametri:
    const Lista_Prenotazioni lista, const Lezione lezione, const char* nome, const char* cognome

  -Pre: lista valida, lezione con data definita, nome e cognome non nulli

  -Post: True se esiste un conflitto, altrimenti False
 */
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const char* nome, const char* cognome){

    
    Nodo* nodo_corrente = lista;
    while(nodo_corrente != NULL){
        
        
        if(lista->prenotazione.lezione.data == lezione.data){
            
            
            if(strcmp(lista->prenotazione.nome_partecipante, nome) == 0 && strcmp(lista->prenotazione.cognome_partecipante, cognome) == 0){
                
                return true; 
        }

        nodo_corrente = nodo_corrente->next; 
    }

    return false;

}
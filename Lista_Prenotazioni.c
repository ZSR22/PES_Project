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
  
Crea una nuova lista di prenotazioni vuota

  

  @return riporta una lista vuota
 */
Lista_Prenotazioni crea_lista_prenotazioni(){
    return NULL;
}

/*
  
  
  Aggiunge una prenotazione alla lista, controllando capienza e conflitti
     
  
    @param Lista_Prenotazioni* lista 
    @param Prenotazione prenotazione  

  -Pre: lista != NULL

   @result prenotazione aggiunta in coda alla lista
 */
void aggiungi_prenotazione(Lista_Prenotazioni* lista, const Prenotazione prenotazione){

    
    if(lezione_piena(*lista, prenotazione.lezione)){
        fprintf(stderr, "La lezione selezionata ha raggiunto il numero massimo di partecipanti. \n");
        return;
    }

    
    if(controllo_conflitto_orario(*lista, prenotazione.lezione, prenotazione.partecipante)){
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
    
    
    if(lista == NULL){
        *lista = nuovo_nodo;
    } else{
        Nodo* nodo_corrente = *lista;
        while (nodo_corrente->next != NULL) 
        {
            nodo_corrente = nodo_corrente->next; 
        }
        
        nodo_corrente->next = nuovo_nodo; 
        
    }
}

/*

  Rimuove una prenotazione dalla lista: ricercata per data e ID


  @param Lista_Prenotazioni* lista
  @param Lezione* lezione

  Pre: lista != NULL, lezione valida

  @result riporta True se la prenotazione è stata trovata e rimossa, False se non è stata trovata oppure la lezione non è valida oppure la lista prenotazioni è vuota
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
            
            
            if(nodo_precedente == NULL){
                *lista = nodo_corrente->next; 
            } else{
                nodo_precedente->next = nodo_corrente->next; 
            }
            
            free(nodo_corrente);
            return true;
        }    
        
        nodo_precedente = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
    }

    fprintf(stderr, "Prenotazione non trovata\n");
    return false;
}

/*

  Stampa a video tutte le prenotazioni presenti nella lista

  
   @param Lista_Prenotazioni lista

  

  @result per ogni prenotazione vengono mostrati ID, nome, cognome, lezione e data, se la lista è vuota stamperà un messaggio di errore
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
        nodo_corrente = nodo_corrente->next;
    }
    
}

/*
  

  Libera tutta la memoria allocata per la lista

  
   @param Lista_Prenotazioni* lista

  -Pre: lista != NULL

  @result lista vuota, memoria liberata
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
  

  Conta il numero di prenotazioni per una lezione specifica: ricercata per data e ID

  
    @param Lista_Prenotazioni* lista
    @param Lezione* lezione

  

  @return ritorna la somma delle prenotazioni trovate
 */
int conteggia_prenotazioni( const Lista_Prenotazioni* lista, const Lezione* lezione){
    
    if (lista == NULL || lezione == NULL) {
        
        fprintf(stderr, "Errore: lezione o lista non validi. \n");
        return -1; 
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
  
  Verifica se una lezione ha raggiunto il numero massimo di prenotazioni

  
    @param Lista_Prenotazioni lista
    @param Lezione lezione_da_analizzare

  -Pre: lista valida, lezione esistente

  @return True se la lezione è al completo, altrimenti False
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


  Verifica se un partecipante ha già prenotato una lezione nello stesso orario

  
    @param Lista_Prenotazioni lista
    @param Lezione lezione
    @param Cliente partecipante

  -Pre: lista valida, lezione con data definita, nome e cognome non nulli

  @return True se esiste un conflitto, altrimenti False
 */
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante){

    
    Nodo* nodo_corrente = lista;
    while(nodo_corrente != NULL){
        
        
        if(nodo_corrente->prenotazione.lezione.data == lezione.data){
            
            
            if(strcmp(nodo_corrente->prenotazione.partecipante.nome, partecipante.nome) == 0 && 
            strcmp(nodo_corrente->prenotazione.partecipante.cognome, partecipante.cognome) == 0){
                
                return true; 
            }
        }


        nodo_corrente = nodo_corrente->next; 
    }

    return false;

}

/*
  

  Cerca una prenotazione confrontando prima data e id lezione, poi nome e cognome del partecipante

  
    @param Lista_Prenotazioni* lista
    @param Lezione lezione
    @param Cliente partecipante

  

  @return ritorna un puntatore alla struttura Prenotazione cercata
  se non è stata trovata restituisce NULL
 */
Prenotazione* trova_prenotazione(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante){

    if(lista == NULL || &lezione == NULL || &partecipante == NULL){return NULL;}
       
    
    
    Nodo* nodo_corrente = lista;

    while (nodo_corrente != NULL)
    {
        if(nodo_corrente->prenotazione.lezione.data == lezione.data 
            && nodo_corrente->prenotazione.lezione.ID == lezione.ID){

            if(strcmp(nodo_corrente->prenotazione.partecipante.nome, partecipante.nome) == 0 
            && strcmp(nodo_corrente->prenotazione.partecipante.cognome, partecipante.cognome)){
                
                return &nodo_corrente->prenotazione;
            }
            
        }

        nodo_corrente = nodo_corrente->next;
    }

    return NULL;
    
}
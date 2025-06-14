/* 
=============================================================================
 File: Lista_Prenotazioni.c
 Descrizione: Gestione delle prenotazioni tramite lista collegata
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Lista_Prenotazioni.h"

/*
  
Crea una nuova lista di prenotazioni vuota

  

  @return riporta una lista vuota
 */
Lista_Prenotazioni* crea_lista_prenotazioni(){
    
    Lista_Prenotazioni* lista = malloc(sizeof(Lista_Prenotazioni));
    *lista = NULL;
    return lista;
}

/*
  
  
  Aggiunge una prenotazione alla lista, controllando capienza e conflitti
     
  
    @param Lista_Prenotazioni* lista 
    @param Prenotazione prenotazione  

  -Pre: lista != NULL, prenotazione != NULL

   @result prenotazione aggiunta in coda alla lista
 */
bool aggiungi_prenotazione(Lista_Prenotazioni* lista, const Prenotazione prenotazione){

    
    if(lezione_piena(*lista, prenotazione.lezione)){
        fprintf(stderr, "La lezione selezionata ha raggiunto il numero massimo di partecipanti. \n");
        return false;
    }

    
    if(controllo_conflitto_orario(*lista, prenotazione.lezione, prenotazione.partecipante)){
        fprintf(stderr, "Utente già prenotato.\n");
        return false;
    } 

    
    NodoPrenotazione* nuovo_nodo = (NodoPrenotazione*)malloc(sizeof(NodoPrenotazione));
    if(nuovo_nodo == NULL){
        fprintf(stderr, "Errore di allocazione memoria!!\n");
        return false;
    }
    
    
    nuovo_nodo->prenotazione = prenotazione;
    nuovo_nodo->next = NULL;
    
    
    if(*lista == NULL){
        *lista = nuovo_nodo;
    } else{
        NodoPrenotazione* nodo_corrente = *lista;
        while (nodo_corrente->next != NULL) 
        {
            nodo_corrente = nodo_corrente->next; 
        }
        
        nodo_corrente->next = nuovo_nodo; 
        
    }

    return true;

}

/*

  Rimuove una prenotazione dalla lista: ricercata per data e ID


  @param Lista_Prenotazioni* lista
  @param Lezione* lezione

  Pre: lista != NULL, lezione != NULL

  @result riporta True se la prenotazione è stata trovata e rimossa, False se non è stata trovata oppure la lezione non è valida oppure la lista prenotazioni è vuota
 */
bool disdici_prenotazione(Lista_Prenotazioni* lista, const Lezione* lezione){
  
    NodoPrenotazione* nodo_corrente = *lista;
    NodoPrenotazione* nodo_precedente = NULL;
    
   
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

  
   @param Lista_Prenotazioni* lista

  

  @result per ogni prenotazione vengono mostrati ID, nome, cognome, lezione e data, se la lista è vuota stamperà un messaggio di errore
 */
void visualizza_prenotazioni(const Lista_Prenotazioni* lista){
    
    if(lista == NULL){
        fprintf(stderr, "La lista è vuota\n");
        return;
    }
    
    NodoPrenotazione* nodo_corrente = *lista;
    
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
    
    NodoPrenotazione* nodo_corrente;
    
    
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
    NodoPrenotazione* corrente = *lista;

    
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

  -Pre: lista != NULL, lezione != NULL

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

  -Pre: lista != NULL, lezione != NULL, partecipante != NULL

  @return True se esiste un conflitto, altrimenti False
 */
bool controllo_conflitto_orario(const Lista_Prenotazioni lista, const Lezione lezione, const Cliente partecipante){

    
    NodoPrenotazione* nodo_corrente = lista;
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

    if(lista == NULL){printf("Prenotazione non trovata\n"); return NULL;}
       
    NodoPrenotazione* nodo_corrente = lista;

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

/*
    Controlla se un cliente ha almeno una prenotazione attiva. 
    La funzione controlla se esiste almeno una prenotazione attiva di un partecipante confrontando il codice fiscale salvato in entrambi gli elementi

    @param Lista_Prenotazioni lista
    @param Cliente partecipante

    Pre: lista allocata, partecipante con elemento codice fiscale valido

    @return True se esiste almeno una prenotazione del partecipante, False se non viene trovata

*/
bool cliente_prenotato(const Lista_Prenotazioni lista, const Cliente partecipante){

    NodoPrenotazione* nodo_corrente = lista;

    while(nodo_corrente != NULL){
        if(strcmp(partecipante.codice_fiscale, nodo_corrente->prenotazione.partecipante.codice_fiscale) == 0){
            return true;
        }

        nodo_corrente = nodo_corrente->next;
    }

    return false;
}

/*
  
  Verifica se una lezione è stata prenotata almeno una volta
  
  @param Lista_Prenotazioni lista
  @param Lezione lezione: lezione da verificare

  -Pre: lezione deve avere ID valido

  @return true se almeno una prenotazione è associata alla lezione specificata, false altrimenti

*/
bool lezione_prenotata(const Lista_Prenotazioni lista, const Lezione lezione){

    NodoPrenotazione* nodo_corrente = lista;

    while (nodo_corrente != NULL){
    
        if(nodo_corrente->prenotazione.lezione.ID == lezione.ID){
            return true;
        }

       nodo_corrente = nodo_corrente->next;
        
    }


    return false;
    
}

/*
  Verifica la validità sintattica di un codice fiscale italiano.

  @param char* cf Puntatore a una stringa contenente il codice fiscale da validare.



  - Controlli effettuati:
    - Lunghezza esatta di 16 caratteri
    - Tutti i caratteri sono alfanumerici maiuscoli (A-Z, 0-9)
  
  @return
    true se il codice fiscale rispetta i requisiti sintattici, false altrimenti
*/
bool codice_fiscale_valido(const char* cf) {
    
    if (!cf || strlen(cf) != 16) return false;

    for (int i = 0; i < 16; i++) {
        if (!isalnum(cf[i]) || islower(cf[i])) return false;
    }

    return true;
}
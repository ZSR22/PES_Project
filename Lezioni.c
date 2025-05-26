/*
=============================================================================
// File: Lezioni.c
 Descrizione: Implementazione della gestione dinamica di un catalogo lezioni
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include  "Lezioni.h"


Catalogo_Lezioni catalogo;

/*
  

  Inizializza un array dinamico di strutture Lezione con capacità iniziale(4)

  
   @param Catalogo_Lezioni* catalogo

  -Pre: catalogo == NULL

  @result catalogo->lezione allocato, numero_lezioni = 0, capacity = CAPACITÀ_INIZIALE
 */
void inizializza_catalogo(Catalogo_Lezioni* catalogo){
    
    catalogo->capacità = CAPACITÀ_INIZIALE;
    catalogo->numero_lezioni = 0;
    catalogo->lezione = malloc(sizeof(Lezione) * catalogo->capacità);
    
}

/*
  
  
  Aggiunge una lezione al catalogo, ridimensionando se necessario tramite raddoppio esponenziale
  
  
  @param Catalogo_Lezioni* catalogo
  @param Lezione nuova_lezione

  -Pre: catalogo != NULL, nuova_lezione != NULL

  @result lezione inserita in coda, size incrementato, capacity raddoppiata se necessario
 */
void aggiungi_lezione(Catalogo_Lezioni* catalogo, const Lezione nuova_lezione){
    
    if(catalogo->numero_lezioni >= catalogo->capacità){
        size_t nuova_capacità = catalogo->capacità * 2;
        Lezione* temp = realloc(catalogo->lezione, nuova_capacità * sizeof(Lezione));
        if(temp == NULL){
            fprintf(stderr, "Errore di reallocazione memoria del catalogo lezioni\n");
            return;
        }

        catalogo->lezione = temp;
        catalogo->capacità = nuova_capacità;
    }

    catalogo->lezione[catalogo->numero_lezioni++] = nuova_lezione;
    

}

/*
  
  
  Rimuove una lezione dal catalogo, cercata usando ID e data, se opportuno ridimensiona la memoria tramite dimezzamento
  
  
   @param Catalogo_Lezioni* catalogo
   @param Lezione lezione_da_eliminare

  
  
  @result catalogo aggiornato, size decrementato, memoria ridotta se size < capacity/4
 */
void elimina_lezione(Catalogo_Lezioni* catalogo, const Lezione lezione_da_eliminare){

    if (catalogo == NULL || catalogo->lezione == NULL || catalogo->numero_lezioni == 0) {
        fprintf(stderr, "Catalogo vuoto o non inizializzato\n");
        return;
    }

    int indice = 0;
    bool lezione_trovata;
    
    for(int i = 0; i < catalogo->numero_lezioni; i++){
        if(catalogo->lezione[i].ID == lezione_da_eliminare.ID && catalogo->lezione[i].data == lezione_da_eliminare.data){
            indice = i;
            lezione_trovata = true;
            break;
        }
    }
    
    if(!lezione_trovata){
        fprintf(stderr, "Lezione non trovata\n");
        return;
    }
    
    for(int j = indice; j < catalogo->numero_lezioni - 1; j++){
        catalogo->lezione[j] = catalogo->lezione[j + 1];
    }
    
    catalogo->numero_lezioni--;
    memset(&catalogo->lezione[catalogo->numero_lezioni], 0, sizeof(Lezione));

    if(catalogo->numero_lezioni > 0 && catalogo->numero_lezioni < catalogo->capacità / 4){
        
        size_t nuova_capacità = catalogo->capacità / 2;
        Lezione* temp = realloc(catalogo->lezione, nuova_capacità * sizeof(Lezione));

        if(temp == NULL){
            fprintf(stderr, "Errore reallocazione memoria del catalogo lezioni\n");
            return;
        }
        catalogo->lezione = temp;
        catalogo->capacità = nuova_capacità;
    }
}

/*

  Libera tutta la memoria allocata per il catalogo lezioni

  @param Catalogo_Lezioni* catalogo

  -Pre: catalogo != NULL

  @result catalogo->lezione liberato, numero_lezioni e capacità azzerati

*/
void elimina_catalogo(Catalogo_Lezioni *catalogo){

    free(catalogo->lezione);
    catalogo->lezione = NULL;
    catalogo->numero_lezioni = 0;
    catalogo->capacità = 0;

}

/*
  

  Stampa a video tutte le lezioni presenti nel catalogo

  
    @param Catalogo_Lezioni catalogo

  

  @result per ogni lezione vengono mostrati ID, lezione, numero di posti e data, se il catalogo è vuoto stamperà un messaggio di errore
 */
void mostra_lezioni(const Catalogo_Lezioni catalogo){
    
    if(&catalogo == NULL){
        fprintf(stderr, "Catalogo Vuoto \n");
        return;
    }

    for(int i = 0; i < catalogo.numero_lezioni; i ++){

        Orario_Tm* data = converti_orario_in_struct_tm(catalogo.lezione[i].data);
        
        printf("ID:%u\n, lezione:%s\n, numero di posti: %d\n, data:%02d/%02d/%04d--%02d:%02d\n", catalogo.lezione[i].ID, catalogo.lezione[i].nome, catalogo.lezione[i].max_posti,
        data->tm_mday,
        data->tm_mon,
        data->tm_year,
        data->tm_hour,
        data->tm_min);

        printf("======================================");
    }
}
/*
  
  
  Cerca una lezione tramite ID e restituisce un puntatore alla struttura
  
  
   @param Catalogo_Lezioni* catalogo
   @param Lezione lezione

  Pre: id valido 
  
  @return restituisce un puntatore alla lezione, altrimenti NULL se la lezione non è presente
 */
const Lezione* trova_lezione(const Catalogo_Lezioni* catalogo, const unsigned int id){

    if (catalogo == NULL || catalogo->lezione == NULL || catalogo->numero_lezioni == 0) {
        return NULL;
    }

    for(int i = 0; i < catalogo->numero_lezioni; i++){
        if(catalogo->lezione[i].ID == id){
        
            return &catalogo->lezione[i];
        }
    }

    return NULL;
}

/*

  Verifica se esiste una lezione già pianificata nello stesso orario

  @param Catalogo_Lezioni* catalogo
  @param time_t orario -> orario da controllare

  -Pre: catalogo != NULL, orario valido

  @return true se esiste almeno una lezione con lo stesso orario, false altrimenti

*/
bool conflitto_orario_lezione(const Catalogo_Lezioni* catalogo, time_t orario){
    
    for(int i = 0; i < catalogo->numero_lezioni; i++){
        if(catalogo->lezione[i].data == orario){
            return true;
        }
    }

    return false;
}
/*
=============================================================================
// File: Lezioni.c
 Descrizione: Implementazione della gestione dinamica di un catalogo lezioni
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/

#include  "Lezioni.h"

Catalogo_Lezioni catalogo;

/*
  inizializza_catalogo

  Inizializza un array dinamico di strutture Lezione con capacità iniziale(4)

  -Parametri:
    Catalogo_Lezioni* catalogo

  -Pre: catalogo != NULL

  -Post: catalogo->lezione allocato, numero_lezioni = 0, capacity = CAPACITÀ_INIZIALE
 */
void inizializza_catalogo(Catalogo_Lezioni* catalogo){
    
    catalogo->capacità = CAPACITÀ_INIZIALE;
    catalogo->numero_lezioni = 0;
    catalogo->lezione = malloc(sizeof(Lezione) * catalogo->capacità);
    
}

/*
  aggiungi_lezione
  
  Aggiunge una lezione al catalogo, ridimensionando se necessario tramite il metodo del raddoppio esponenziale
  
  -Parametri:
    Catalogo_Lezioni* catalogo, const Lezione nuova_lezione

  -Pre: catalogo != NULL, catalogo->lezione allocato

  -Post: lezione inserita in coda, size incrementato, capacity raddoppiata se necessario
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
  elimina_lezione
  
  Rimuove una lezione dal catalogo dato il suo ID e la data, riducendo memoria se opportuno tramite dimezzamento
  
  -Parametri:
    Catalogo_Lezioni* catalogo, const Lezione lezione_da_eliminare

  -Pre: catalogo != NULL, catalogo->lezione != NULL, numero_lezioni > 0
  
  -Post: catalogo aggiornato, size decrementato, memory ridotta se size < capacity/4
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
  visualizza_lezioni

  Stampa a video tutte le lezioni presenti nel catalogo

  -Parametri:
    const Catalogo_Lezioni catalogo

  -Pre: catalogo valido

  -Post: per ogni lezione vengono mostrati ID, lezione, numero di posti e data, se il catalogo è vuoto stamperà un messaggio di errore
 */
void mostra_lezioni(const Catalogo_Lezioni catalogo){
    
    for(int i = 0; i < catalogo.numero_lezioni; i ++){

        Orario_Tm* data = converti_orario(catalogo.lezione[i].data);
        printf("ID:%Ud\n, lezione:%s\n, numero di posti: %d\n, data:%02d/%02d/%04d--%02d:%02d\n", catalogo.lezione[i].ID, catalogo.lezione[i].nome, catalogo.lezione[i].max_posti,
        data->tm_mday,
        data->tm_mon,
        data->tm_year,
        data->tm_hour,
        data->tm_min);

        printf("======================================");
    }
}
/*
  trova_lezione
  
  Cerca una lezione tramite ID e data e restituisce un puntatore alla struttura
  
  -Parametri:
    const Catalogo_Lezioni* catalogo, const Lezione lezione

  -Pre: catalogo != NULL 
  
  -Post: restituisce un puntatore alla lezione se trovata, altrimenti NULL se la lezione non è presente nel catalogo
 */
const Lezione* trova_lezione(const Catalogo_Lezioni* catalogo, const Lezione lezione){

    if (catalogo == NULL || catalogo->lezione == NULL || catalogo->numero_lezioni == 0) {
        return NULL;
    }

    for(int i = 0; i < catalogo->numero_lezioni; i++){
        if(catalogo->lezione[i].ID == lezione.ID && catalogo->lezione[i].data == lezione.data){
        
            return &catalogo->lezione[i];
        }
    }

    return NULL;
}
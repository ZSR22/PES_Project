#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "Persistenza_Dati.h"

/*

  Carica da file JSON l'elenco delle lezioni e le inserisce nel catalogo

  @param char* filepath

  -Pre: filepath valido, file in formato JSON esistente

  @return Catalogo_Lezioni popolato con i dati letti dal file
*/
Catalogo_Lezioni carica_catalogo_da_file(const char* filepath){

    Catalogo_Lezioni catalogo;
    inizializza_catalogo(&catalogo);

    FILE* file = fopen(filepath, "r");
    if(!file){return catalogo;}

    fseek(file, 0, SEEK_END);
    long int lunghezza = ftell(file);
    rewind(file);

    char* buffer = malloc(lunghezza +1);
    fread(buffer, 1, lunghezza, file);
    buffer[lunghezza] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(buffer);
    free(buffer);
    if(!root || !cJSON_IsArray(root)){
        cJSON_Delete(root);
        return catalogo;
    }

    int contatore_item = cJSON_GetArraySize(root);
    for (int i = 0; i < contatore_item; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);

        Lezione lezione;
        cJSON* id = cJSON_GetObjectItem(item, "ID");
        cJSON* nome = cJSON_GetObjectItem(item, "nome");
        cJSON* posti = cJSON_GetObjectItem(item, "max_posti");
        cJSON* data = cJSON_GetObjectItem(item, "data");

        if (cJSON_IsNumber(id)) {
            lezione.ID = (unsigned int)cJSON_GetNumberValue(id);
        }

        if (cJSON_IsString(nome)) {
            strncpy(lezione.nome, nome->valuestring, MAX_NOME);
        }

        if (cJSON_IsNumber(posti)) {
            lezione.max_posti = (int)cJSON_GetNumberValue(posti);
        }

        if (cJSON_IsNumber(data)) {
            lezione.data = (time_t)cJSON_GetNumberValue(data);
        }


        aggiungi_lezione(&catalogo, lezione);
    }
    
    cJSON_Delete(root);
    return catalogo;
}

/*

  Carica da file JSON la lista collegata delle prenotazioni

  @param char* filepath
  @param Lista_Prenotazioni* lista

  -Pre: lista != NULL, filepath valido

  @result lista popolata con le prenotazioni lette dal file
*/
void carica_prenotazioni_da_file(const char* filepath, Lista_Prenotazioni* lista){

    FILE* file = fopen(filepath, "r");
    if (!file){
        fprintf(stderr, "Errore apertura file!\n");
        return;
    } 

    fseek(file, 0, SEEK_END);
    long lunghezza = ftell(file);
    rewind(file);

    char* buffer = malloc(lunghezza + 1);
    fread(buffer, 1, lunghezza, file);
    buffer[lunghezza] = '\0';
    fclose(file);

    cJSON* root =cJSON_Parse(buffer);
    free(buffer);
    if(!root || !cJSON_IsArray(root)){ return;}

    int contatore_item = cJSON_GetArraySize(root);
    for(int i = 0; i < contatore_item; i++){

        cJSON* item =cJSON_GetArrayItem(root, i);
        Prenotazione prenotazione;

        cJSON* id = cJSON_GetObjectItem(item, "ID");
        cJSON* struttura_cliente = cJSON_GetObjectItem(item, "partecipante");
        cJSON* struttura_lezione = cJSON_GetObjectItem(item, "lezione");

        if(cJSON_IsNumber(id)){
            prenotazione.ID = (unsigned int)cJSON_GetNumberValue(id);
        }
        
        if(cJSON_IsObject(struttura_cliente)){
            
            cJSON* nome = cJSON_GetObjectItem(struttura_cliente, "nome");
            cJSON* cognome = cJSON_GetObjectItem(struttura_cliente, "cognome");

            if(cJSON_IsString(nome)){
                strncpy(prenotazione.partecipante.nome, nome->valuestring, LUNGHEZZA_MASSIMA);
            }
            if(cJSON_IsString(cognome)){
                strncpy(prenotazione.partecipante.cognome, cognome->valuestring, LUNGHEZZA_MASSIMA);
            }
        }

        if(cJSON_IsObject(struttura_lezione)){

            cJSON* id_lezione = cJSON_GetObjectItem(struttura_lezione, "ID");
            cJSON* nome_lezione = cJSON_GetObjectItem(struttura_lezione, "nome");
            cJSON* max_posti_lezione = cJSON_GetObjectItem(struttura_lezione, "max_posti");
            cJSON* data_lezione = cJSON_GetObjectItem(struttura_lezione, "data");

            if(cJSON_IsNumber(id_lezione)){ 
                prenotazione.lezione.ID = (unsigned int)cJSON_GetNumberValue(id_lezione);
            }
            if(cJSON_IsString(nome_lezione)){
                strncpy(prenotazione.lezione.nome, nome_lezione->valuestring, MAX_NOME);
            }
            if(cJSON_IsNumber(max_posti_lezione)){ 
                prenotazione.lezione.max_posti = (int)cJSON_GetNumberValue(max_posti_lezione);
            }
            if(cJSON_IsNumber(data_lezione)){ 
                prenotazione.lezione.data = (time_t)cJSON_GetNumberValue(data_lezione);
            }
        }

        aggiungi_prenotazione(lista, prenotazione);
    }

    cJSON_Delete(root);
}

/*

  Carica da file JSON l’albero degli abbonamenti

  @param char* filepath
  @param NodoAlbero** radice_BST

  -Pre: filepath valido, radice inizializzata a NULL

  @result albero aggiornato con tutti gli abbonamenti trovati nel file
*/
void carica_abbonamenti_da_file(const char* filepath, NodoAlbero** radice_BST){

    FILE* file = fopen(filepath, "r");
    if (!file){
        fprintf(stderr, "Errore apertura file!\n");
        return;
    } 

    fseek(file, 0, SEEK_END);
    long lunghezza = ftell(file);
    rewind(file);

    char* buffer = malloc(lunghezza + 1);
    fread(buffer, 1, lunghezza, file);
    buffer[lunghezza] = '\0';
    fclose(file);

    cJSON* root =cJSON_Parse(buffer);
    free(buffer);
    if(!root || !cJSON_IsArray(root)){ return;}

    int contatore_item = cJSON_GetArraySize(root);
    for(int i = 0; i < contatore_item; i++){
        
        cJSON* item = cJSON_GetArrayItem(root, i);
        Cliente cliente;

        cJSON* nome = cJSON_GetObjectItem(item, "nome");
        cJSON* cognome = cJSON_GetObjectItem(item, "cognome");
        cJSON* codice_fiscale = cJSON_GetObjectItem(item, "codice_fiscale");
        cJSON* data_nascita = cJSON_GetObjectItem(item, "data_di_nascita");
        cJSON* validità_abbonamento = cJSON_GetObjectItem(item, "attivo");
        cJSON* data_inizio = cJSON_GetObjectItem(item, "data_inizio_abbonamento");
        cJSON* durata = cJSON_GetObjectItem(item, "durata");
        cJSON* id_abbonamento = cJSON_GetObjectItem(item, "id_abbonamento");

        if(cJSON_IsString(nome)){
            strncpy(cliente.nome, nome->valuestring, sizeof(cliente.nome));
        }
        if(cJSON_IsString(cognome)){
            strncpy(cliente.cognome, cognome->valuestring, sizeof(cliente.cognome));
        }
        if(cJSON_IsString(codice_fiscale)){
            strncpy(cliente.codice_fiscale, codice_fiscale->valuestring, sizeof(cliente.codice_fiscale));
        }
        if(cJSON_IsString(data_nascita)){
            strncpy(cliente.data_nascita, data_nascita->valuestring, sizeof(cliente.data_nascita));
        }
        
        // Questa funzione andrebbe implementata ma va aggiunto un campo alla struttura Cliente
        /*
        if(cJSON_IsBool(validità_abbonamento)){
            cliente.valido = cJSON_IsTrue(validità_abbonamento;)
        }
        */

       if(cJSON_IsNumber(data_inizio)){
            cliente.data_inizio = (time_t)cJSON_GetNumberValue(data_inizio);
       }
       if(cJSON_IsNumber(durata)){
            cliente.durata = (int)cJSON_GetNumberValue(durata);
       }
       if(cJSON_IsNumber(id_abbonamento)){
            cliente.id_abbonamento = (unsigned int)cJSON_GetNumberValue(id_abbonamento);
       }

       *radice_BST = inserisci_cliente(radice_BST, cliente);
    }

    cJSON_Delete(root);
}
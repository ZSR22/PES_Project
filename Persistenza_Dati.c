/* 
=============================================================================
 File: Persistenza_Dati.c
 Descrizione: Implementazione delle funzioni per il salvataggio e il caricamento di dati persistenti
 Autore: Gianmarco Raimondi
 Data: 21/05/2025
 Versione: 1.0
=============================================================================
*/
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
    if(!file){fprintf(stderr, "Errore apertura file lezioni.json\n"); return catalogo;}

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
        fprintf(stderr, "Errore apertura file prenotazioni.json\n");
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
            
            cJSON* nome_p = cJSON_GetObjectItem(struttura_cliente, "nome");
            cJSON* cognome_p = cJSON_GetObjectItem(struttura_cliente, "cognome");
            cJSON* codice_fiscale_p = cJSON_GetObjectItem(item, "codice_fiscale");
            cJSON* data_nascita_p = cJSON_GetObjectItem(item, "data_di_nascita");
            cJSON* data_inizio_p = cJSON_GetObjectItem(item, "data_inizio_abbonamento");
            cJSON* durata_p = cJSON_GetObjectItem(item, "durata");
            cJSON* id_abbonamento_p = cJSON_GetObjectItem(item, "id_abbonamento");

            if(cJSON_IsString(nome_p)){
                strncpy(prenotazione.partecipante.nome, nome_p->valuestring, LUNGHEZZA_MASSIMA);
            }
            if(cJSON_IsString(cognome_p)){
                strncpy(prenotazione.partecipante.cognome, cognome_p->valuestring, LUNGHEZZA_MASSIMA);
            }
            if(cJSON_IsString(codice_fiscale_p)){
                strncpy(prenotazione.partecipante.codice_fiscale, codice_fiscale_p->valuestring, sizeof(prenotazione.partecipante.codice_fiscale));
            }
            if(cJSON_IsString(data_nascita_p)){
                strncpy(prenotazione.partecipante.data_nascita, data_nascita_p->valuestring, sizeof(prenotazione.partecipante.data_nascita));
            }
            if(cJSON_IsNumber(data_inizio_p)){
                prenotazione.partecipante.data_inizio = (time_t)cJSON_GetNumberValue(data_inizio_p);
            }
            if(cJSON_IsNumber(durata_p)){
                prenotazione.partecipante.durata = (int)cJSON_GetNumberValue(durata_p);
            }
            if(cJSON_IsNumber(id_abbonamento_p)){
                prenotazione.partecipante.id_abbonamento = (unsigned int)cJSON_GetNumberValue(id_abbonamento_p);
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

//Funzioni di salvataggio


/*

  Salva il catalogo delle lezioni su file JSON

  @param Catalogo_Lezioni* catalogo
  @param char* filepath

  -Pre: catalogo != NULL, filepath valido

  @return true se il salvataggio è avvenuto con successo, false altrimenti
*/
bool salva_catalogo_su_file(const Catalogo_Lezioni* catalogo, const char* filepath){

    cJSON* root = cJSON_CreateArray();

    for(int i = 0; i < catalogo->numero_lezioni; i++){
        Lezione lezione = catalogo->lezione[i];
        cJSON* struttura_lezione = cJSON_CreateObject();

        cJSON_AddNumberToObject(struttura_lezione, "ID", lezione.ID);
        cJSON_AddStringToObject(struttura_lezione, "nome", lezione.nome);
        cJSON_AddNumberToObject(struttura_lezione, "max_posti", lezione.max_posti);
        cJSON_AddNumberToObject(struttura_lezione, "data", (double)lezione.data);

        cJSON_AddItemToArray(root, struttura_lezione);
    }

    cJSON* stringa_json = cJSON_Print(root);
    FILE* file = fopen(PATH_FILE_LEZIONI, "w");
    if(!file){
        cJSON_Delete(root);
        free(stringa_json);
        fprintf(stderr, "Errore apertura file lezioni.json\n");
        return false;
    }

    fputs(stringa_json, file);
    fclose(file);
    free(stringa_json);
    cJSON_Delete(root);
    return true;
}

/*

  Salva la lista delle prenotazioni su file JSON

  @param Lista_Prenotazioni lista
  @param char* filepath

  -Pre: lista valida, filepath valido

  @return true se il salvataggio è avvenuto con successo, false altrimenti
*/
bool salva_prenotazioni_su_file(const Lista_Prenotazioni lista, const char* filepath){

    cJSON* root = cJSON_CreateArray();

    Lista_Prenotazioni lista_prenotazioni = lista;

    while(lista_prenotazioni != NULL){
        
        cJSON* prenotazione_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(prenotazione_json, "ID", lista_prenotazioni->prenotazione.ID);
        
        cJSON* partecipante_json = cJSON_CreateObject();
        cJSON_AddStringToObject(partecipante_json, "nome", lista_prenotazioni->prenotazione.partecipante.nome);
        cJSON_AddStringToObject(partecipante_json, "cognome", lista_prenotazioni->prenotazione.partecipante.cognome);
        cJSON_AddStringToObject(partecipante_json, "codice_fiscale", lista_prenotazioni->prenotazione.partecipante.codice_fiscale);
        cJSON_AddStringToObject(partecipante_json, "data_nascita", lista_prenotazioni->prenotazione.partecipante.data_nascita);
        cJSON_AddNumberToObject(partecipante_json, "durata", lista_prenotazioni->prenotazione.partecipante.durata);
        cJSON_AddNumberToObject(partecipante_json, "data_inizio", (double)lista_prenotazioni->prenotazione.partecipante.data_inizio);
        cJSON_AddNumberToObject(partecipante_json, "id_abbonamento", lista_prenotazioni->prenotazione.partecipante.id_abbonamento);

        cJSON_AddItemToArray(root, prenotazione_json);

        cJSON* lezione_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(lezione_json, "ID", lista_prenotazioni->prenotazione.lezione.ID);
        cJSON_AddStringToObject(lezione_json, "nome", lista_prenotazioni->prenotazione.lezione.nome);
        cJSON_AddNumberToObject(lezione_json, "max_posti", lista_prenotazioni->prenotazione.lezione.max_posti);
        cJSON_AddNumberToObject(lezione_json, "data", (double)lista_prenotazioni->prenotazione.lezione.data);

        cJSON_AddItemToArray(root, lezione_json);
        
        lista_prenotazioni = lista_prenotazioni->next;
    }

    cJSON* stringa_json = cJSON_Print(root);
    FILE* file = fopen(PATH_FILE_PRENOTAZIONI, "w");
    if(!file){
        fprintf(stderr, "Errore apertura file prenotazioni.json\n");
        cJSON_Delete(root);
        free(stringa_json);
        return false;
    }

    fputs(stringa_json, file);
    fclose(file);
    free(stringa_json);
    cJSON_Delete(root);
}

/*

  Salva l’albero degli abbonamenti su file JSON

  @param NodoAlbero* nodo
  @param char* filepath

  -Pre: nodo valido o NULL, filepath valido

  @return true se il salvataggio è avvenuto con successo, false altrimenti
*/
bool salva_abbonamenti_su_file(const NodoAlbero* nodo, const char* filepath){

    cJSON* root = cJSON_CreateArray();

    aggiung_clienti_array_json(nodo, root);

    cJSON* stringa_json = cJSON_Print(root);
    FILE* file = fopen(PATH_FILE_ABBONAMENTI, "w");
    if(!file){
        fprintf(stderr, "Errore apertura file clienti.json\n");
        cJSON_Delete(root);
        free(stringa_json);
        return false;
    }

    fputs(stringa_json, file);
    fclose(file);
    free(stringa_json);
    cJSON_Delete(root);
}

/*
  
  Inserisce ricorsivamente i clienti dell'albero nell'array JSON; la funzione ricorsiva visita in-order(simmetricamente) l'albero

  @param NodoAlbero* nodo
  @param cJSON* array_json

  -Pre: array_json != NULL, nodo può essere NULL

  @return I clienti vengono aggiunti all'array JSON.
*/
static void aggiung_clienti_array_json(const NodoAlbero* nodo, cJSON* array_json){

    if(nodo == NULL){
        return;
    }
    aggiung_clienti_array_json(nodo->sx, array_json);

    cJSON* cliente_json =cJSON_CreateObject();
    cJSON_AddStringToObject(cliente_json, "nome", nodo->cliente.nome);
    cJSON_AddStringToObject(cliente_json, "cognome", nodo->cliente.cognome);
    cJSON_AddStringToObject(cliente_json, "codice_fiscale", nodo->cliente.codice_fiscale);
    cJSON_AddStringToObject(cliente_json, "data_nascita", nodo->cliente.data_nascita);
    cJSON_AddNumberToObject(cliente_json, "data_inizio", (double)nodo->cliente.data_inizio);
    cJSON_AddNumberToObject(cliente_json, "durata", nodo->cliente.durata);
    cJSON_AddNumberToObject(cliente_json, "id_abbonamento", nodo->cliente.id_abbonamento);

    cJSON_AddItemToArray(array_json, cliente_json);

    aggiung_clienti_array_json(nodo->dx, array_json);
}
/* 
=============================================================================
 File: Utilities.c
 Descrizione: Implementazioni di funzioni ad alta visibilità
 Autore: Gianmarco Raimondi
 Data:  14/05/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Utilities.h"
#include "cJSON.h"
/*

Converte una variabile da tipo time_t in una struttura Tm adatta alla visualizzazione a video

@param time_t orario

Pre: orario valido

@return riporta un puntatore alla struttura Orario_Tm

*/
Orario_Tm* converti_orario_in_struct_tm(time_t orario){
    
    Orario_Tm* struttura_orario = localtime(&orario);
    struttura_orario->tm_mon += 1;
    struttura_orario->tm_year += 1900;
    return struttura_orario;
}

/*

  Converte una struttura Orario_Tm e una data in un valore time_t

  @param Orario_Tm* tm_orario
  @param int giorno
  @param int mese
  @param int anno
  @param int ora
  @param int minuto

  -Pre: tm_orario inizializzato, valori di data/ora validi

  @return valore time_t corrispondente alla data e ora specificata

*/
time_t converti_orario_in_time_t(Orario_Tm* tm_orario, int giorno, int mese, int anno, int ora, int minuto){
    
    memset(tm_orario, 0, sizeof(Orario_Tm));
    tm_orario->tm_mday = giorno;
    tm_orario->tm_mon = mese - 1;
    tm_orario->tm_year = anno - 1900;
    tm_orario->tm_hour = ora;
    tm_orario->tm_min = minuto;
    tm_orario->tm_sec = 0;
    tm_orario->tm_isdst = -1;

    

    return mktime(tm_orario);
}

/*

  Genera un ID univoco non presente nel file JSON

  @param char* filepath -> percorso del file JSON da controlllare

  -Pre: filepath valido o file non presente

  @return ID generato univocamente

*/
unsigned int genera_id_univoco(const char* filepath){
    
    FILE* file = fopen(filepath, "r");
    if(!file){
        return (unsigned int)time(NULL) ^ rand();
    }

    fseek(file, 0, SEEK_END);
    long int lunghezza = ftell(file);
    rewind(file);

    char* buffer = malloc(lunghezza + 1);
    fread(buffer, 1, lunghezza, file);
    buffer[lunghezza] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(buffer);
    free(buffer);

    if (!root || !cJSON_IsArray(root)) {
        cJSON_Delete(root);
        return (unsigned int)(time(NULL) ^ rand());
    }

    unsigned int id = time(NULL) ^ rand();
    bool univoco = false;

    while(!univoco){
        
        univoco = true;
        
        int contatore_item = cJSON_GetArraySize(root);
        for(int i = 0; i < contatore_item; i++){

            cJSON* item = cJSON_GetArrayItem(root, i);
            cJSON* id_item = cJSON_GetObjectItem(item, "ID");

            if(cJSON_IsNumber(id_item) && (unsigned int)cJSON_GetNumberValue(id_item) == id){
                univoco = false;
                break;
            }
        }
    }

    cJSON_Delete(root);

    return id;
}

/*

  Verifica se un file è vuoto o non esiste

  @param char* filepath → percorso del file da controllare

  -Pre: filepath valido

  @return true se il file è vuoto, false se esiste ed è vuoto o contiene elementi

*/
bool file_vuoto(char* filepath){

  FILE* file = fopen(filepath,"r");
  if(!file) return true;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fclose(file);

  if(size == 0){
    
    return false;

  }
  
  
  return false;

}
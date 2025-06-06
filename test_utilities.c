/* 
=============================================================================
 File: test_utilities.c
 Descrizione: Implemetazione delle funzioni di controllo e stampa per casi di test
 Autore: Gianmarco Raimondi
 Data: 21/05/2025
 Versione: 1.0
=============================================================================
*/
#include <string.h>
#include <stdlib.h>
#include "test_utilities.h"

/*

  Confronta due file di testo riga per riga

  @param char* file_output -> Percorso al file generato dal programma testato
  @param char* file_oracolo -> Percorso al file contenente l'output atteso (oracolo)

  -Pre: file_output != NULL, file_oracolo != NULL

  @return true se i file sono identici in contenuto e lunghezza, false altrimenti

*/
bool confronta_output(const char *file_output, const char *file_oracolo){

    FILE* output = fopen(file_output, "r");
    FILE* oracolo = fopen(file_oracolo, "r");

    if(!output || !oracolo) { return false;}

    char riga_output[512];
    char riga_oracolo[512];

    while(fgets(riga_output, sizeof(riga_output), output) && fgets(riga_oracolo, sizeof(riga_oracolo), oracolo)){

        riga_output[strcspn(riga_output, "\n")] = '\0';
        riga_oracolo[strcspn(riga_oracolo, "\n")] = '\0';

        if(strcmp(riga_output, riga_oracolo) != 0){
                
            fclose(output);
            fclose(oracolo);
                
            return false;

        }

            


    }

    if(!feof(output) || !feof(oracolo)){

        fclose(output);
        fclose(oracolo);
        fprintf(stderr, "ERRORE: i file hanno contenuti identici ma lunghezze diverse (uno contiene più righe)\n");
        return false;

    }

    return true;

}

/*

  Scrive un messaggio testuale all'interno di un file di log

  @param char* path -> Percorso del file in cui scrivere 
  @param char* messaggio -> Messaggio da registrare nel file

  -Pre: path != NULL, messaggio != NULL

  @return Scrive il messaggio su file, se il file non può essere aperto, stampa un errore su stderr

*/
void scrivi_log(const char* path, const char* messaggio){

    FILE* file = fopen(path, "w");
    if(!file){
        fprintf(stderr, "ERRORE: Apertura file di log fallita, percorso: %s\n", path);
        return;
    }

    fprintf(file, "%s\n", messaggio);
    fclose(file);

}

/*

  Stampa un messaggio colorato in verde per indicare il successo di un test

  @param int test_num -> Numero identificativo del test superato

  -Pre: test_num > 0

  @return stampa su stdout

*/
void stampa_ok(int test_num){

    printf("Test %d: [%s OK %s]\n", test_num, TEST_PASSATO, TEST_RESET);
}

/*

  Stampa un messaggio colorato in rosso per indicare il fallimento di un test, includendo l'atteso e l'ottenuto

  @param int test_num -> Numero identificativo del test fallito
  @param char* atteso -> Output atteso
  @param char* ottenuto -> Output effettivamente ottenuto dal test

  -Pre: test_num > 0, atteso != NULL, ottenuto != NULL

  @return stampa su stdout

*/
void stampa_fail(int test_num, const char *atteso, const char *ottenuto) {
    
  printf("Test %d: [%s FALLITO %s]\n", test_num, TEST_FALLITO, TEST_RESET);
  printf("Esito atteso: %s\nEsito ottenuto: %s\n\n", atteso, ottenuto);

}

/*

  Verifica la presenza di una riga nel file oracolo per il test corrente

  @param FILE* oracolo -> Puntatore al file oracolo già aperto in lettura
  @param int test_num -> Numero identificativo del test corrente

  -Pre: oracolo != NULL, test_num > 0

  @return true se una riga è presente (letta con successo), false se EOF o errore lettura

*/
bool riga_oracolo_presente(FILE *oracolo, int test_num){

    char buffer[512];
    if(!fgets(buffer, sizeof(buffer), oracolo)){

        fprintf(stderr, "ERRORE: Riga in oracolo non presente per test %d\n", test_num);
        return false;

    }
    
    return true;

}

/*

  Verifica che tutti i campi di un blocco siano presenti e non vuoti

  @param char** campi            Array di stringhe contenente i campi letti da input
  @param int numero_campi        Numero effettivo di campi da validare

  -Pre: campi != NULL, numero_campi >= 0

  @return true se tutti i campi sono non NULL e non vuoti, false altrimenti

*/
bool blocco_valido(char **campi, int numero_campi){

    for(int i = 0; i < numero_campi; i++){
        
        if(campi[i] == NULL || strlen(campi[i]) == 0){
            
            fprintf(stderr, "ERRORE: Campo %d mancante o vuoto nel blocco\n", i + 1);
            return false;

        }
    }

    return true;
}

/*

  Crea una copia dinamica della stringa fornita

  @param const char* stringa -> Puntatore alla stringa sorgente da duplicare

  -Pre: stringa != NULL

  @return Puntatore a una nuova stringa allocata dinamicamente contenente una copia identica di quella passata.
          Restituisce NULL in caso di fallimento dell’allocazione.

  -Nota: la memoria restituita deve essere liberata dal chiamante tramite free()

*/
char* duplica_stringa(const char* stringa){
    
    char* copia = malloc(strlen(stringa) + 1);
    if (copia) strcpy(copia, stringa);
    return copia;

}
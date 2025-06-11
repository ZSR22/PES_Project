/*
=====================================================
    File: test_clienti.c
    Descrizione: Implementazioni delle funzioni di test eseguiti su registrazione clienti
    Autore: Salvatore Zurino
    Data: 11/06/2025
    Versione: 1.0
=======================================================
*/
#include <string.h>
#include "test_clienti.h"
#include "test_utilities.h"
#include "header_sorgenti/Persistenza_Dati.h"

#define PATH_INPUT_CLIENTE_VALIDO "input/cliente_valido.txt"
#define PATH_INPUT_CLIENTE_DATI_MANCANTI "input/cliente_dati_mancanti.txt"
#define PATH_INPUT_CLIENTE_ABBONAMENTO_NON_VALIDO "input/cliente_abbonamento_non_valido.txt"
#define PATH_INPUT_CLIENTE_DUPLICATO "input/cliente_duplicato.txt"
 
#define PATH_ORACOLO_CLIENTE_VALIDO "oracoli/cliente_valido.txt"
#define PATH_ORACOLO_CLIENTE_DATI_MANCANTI "oracoli/cliente_dati_mancanti.txt"
#define PATH_ORACOLO_CLIENTE_ABBONAMENTO_NON_VALIDO "oracoli/cliente_abbonamento_non_valido.txt"
#define PATH_ORACOLO_CLIENTE_DUPLICATO "oracoli/cliente_duplicato.txt"

#define PATH_ESITO_CLIENTE_VALIDO "esiti/cliente_valido.log"
#define PATH_ESITO_CLIENTE_DATI_MANCANTI "esiti/cliente_dati_mancanti.log"
#define PATH_ESITO_CLIENTE_ABBONAMENTO_NON_VALIDO "esiti/cliente_abbonamento_non_valido.log"
#define PATH_ESITO_CLIENTE_DUPLICATO "esiti/cliente_duplicato.log"

#define NUM_CAMPI_CLIENTE 5

/*

  Esegue un test specifico di inserimento cliente confrontando l'esito con un oracolo.

  - Legge i campi da file di input, tenta l'inserimento, scrive l'esito su log
    e confronta con l'output atteso (oracolo). Stampa infine l’esito del test.

  @param int test_num -> Numero identificativo del test
  @param char* input_path -> Percorso al file contenente i dati del cliente
  @param char* esito_path -> Percorso del file log generato dal test
  @param char* oracolo_path -> Percorso al file oracolo con l’esito atteso
  @param NodoAlbero** radice -> Puntatore alla radice dell’albero clienti
  @param char* messaggio_successo -> Messaggio log per esito positivo
  @param char* messaggio_fallimento -> Messaggio log per esito negativo

  -Pre: input_path, oracolo_path, radice != NULL

  @result stampa a console l’esito e scrive log su file

*/
static void esegui_test_cliente(
    int test_num,
    const char* input_path,
    const char* esito_path,
    const char* oracolo_path,
    NodoAlbero** radice,
    const char* messaggio_successo,
    const char* messaggio_fallimento
) {
    FILE* file_input = fopen(input_path, "r");
    if (file_input == NULL) {
        stampa_fail(test_num, "file input aperto correttamente", "fallita apertura file input");
        return;
    }

    char buffer[128];
    char* campi[NUM_CAMPI_CLIENTE];
    for (int i = 0; i < 5; i++) {
        if (fgets(buffer, sizeof(buffer), file_input) == NULL) {
            fclose(file_input);
            scrivi_log(esito_path, messaggio_fallimento);
            if (confronta_output(esito_path, oracolo_path)) {
                stampa_ok(test_num);
            } else {
                stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
            }
            
            return;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        campi[i] = duplica_stringa(buffer);
    }

    fclose(file_input);

    Cliente nuovo_cliente;
    strncpy(nuovo_cliente.nome, campi[0], sizeof(nuovo_cliente.nome));
    strncpy(nuovo_cliente.cognome, campi[1], sizeof(nuovo_cliente.cognome));
    strncpy(nuovo_cliente.codice_fiscale, campi[2], sizeof(nuovo_cliente.codice_fiscale));
    nuovo_cliente.durata = atoi(campi[3]);
    strncpy(nuovo_cliente.data_nascita, campi[4], sizeof(nuovo_cliente.data_nascita));
    nuovo_cliente.data_inizio = time(NULL);
    
    if (!abbonamento_valido(nuovo_cliente)){
        
        scrivi_log(esito_path, messaggio_fallimento);
        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }
        for (int i = 0; i < NUM_CAMPI_CLIENTE; i++) {
            free(campi[i]);
        }
        
        return;

    } 

    bool successo = false;
    NodoAlbero* cliente_trovato = ricerca_cliente(*radice, nuovo_cliente.codice_fiscale);
    if(cliente_trovato == NULL){

        NodoAlbero* nodo = inserisci_cliente(*radice, nuovo_cliente);
        if (nodo != NULL) {
            *radice = nodo;
            successo = true;
        }

        if (successo) {
            scrivi_log(esito_path, messaggio_successo);
        } else {
            scrivi_log(esito_path, messaggio_fallimento);
        }

        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }


        for (int i = 0; i < NUM_CAMPI_CLIENTE; i++) {
            free(campi[i]);
        }

    } else{

        scrivi_log(esito_path, messaggio_fallimento);
        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }
        
        for (int i = 0; i < NUM_CAMPI_CLIENTE; i++) {
            free(campi[i]);
        }
        
    }
    
    
}

/*

  Verifica l’inserimento corretto di un cliente con campi completi e validi.

  - Legge i dati da file e verifica che l’inserimento avvenga con successo

  @param NodoAlbero** radice -> Puntatore alla radice dell’albero clienti

  -Pre: radice != NULL

  @result stampa a console l’esito e scrive log su file

*/
static void test_cliente_valido(NodoAlbero** radice){

    esegui_test_cliente(
        1,
        PATH_INPUT_CLIENTE_VALIDO,
        PATH_ESITO_CLIENTE_VALIDO,
        PATH_ORACOLO_CLIENTE_VALIDO,
        radice,
        "Cliente registrato correttamente",
        "Inserimento cliente fallito"
    );

}

/*

  Verifica che un cliente con dati mancanti non venga inserito.

  - Legge un blocco cliente incompleto e si attende fallimento dell'inserimento

  @param NodoAlbero** radice -> Puntatore alla radice dell’albero clienti

  -Pre: radice != NULL

  @result stampa a console l’esito e scrive log su file

*/
static void test_cliente_dati_mancanti(NodoAlbero** radice){

    esegui_test_cliente(
        2,
        PATH_INPUT_CLIENTE_DATI_MANCANTI,
        PATH_ESITO_CLIENTE_DATI_MANCANTI,
        PATH_ORACOLO_CLIENTE_DATI_MANCANTI,
        radice,
        "Cliente registrato correttamente",
        "Campo mancante nel file input"
    );
}

/*

  Verifica che un cliente con durata abbonamento nulla o negativa venga rifiutato.

  - Simula inserimento con durata invalida e verifica comportamento corretto

  @param NodoAlbero** radice -> Puntatore alla radice dell’albero clienti

  -Pre: radice != NULL

  @result stampa a console l’esito e scrive log su file

*/
static void test_abbonamento_non_valido(NodoAlbero** radice) {

    esegui_test_cliente(
        3,
        PATH_INPUT_CLIENTE_ABBONAMENTO_NON_VALIDO,
        PATH_ESITO_CLIENTE_ABBONAMENTO_NON_VALIDO,
        PATH_ORACOLO_CLIENTE_ABBONAMENTO_NON_VALIDO,
        radice,
        "Cliente registrato correttamente",
        "Durata abbonamento non valido"
    );
}

/*

  Verifica che un cliente con codice fiscale già registrato non venga reinserito.

  - Tenta un secondo inserimento con CF duplicato e si attende fallimento

  @param NodoAlbero** radice -> Puntatore alla radice dell’albero clienti

  -Pre: radice != NULL

  @result stampa a console l’esito e scrive log su file

*/
static void test_cliente_duplicato(NodoAlbero** radice) {                  

    esegui_test_cliente(
        4,
        PATH_INPUT_CLIENTE_DUPLICATO,
        PATH_ESITO_CLIENTE_DUPLICATO,
        PATH_ORACOLO_CLIENTE_DUPLICATO,
        radice,
        "Cliente registrato correttamente",
        "Cliente già esistente"
    );
}

/*

  Avvia l’esecuzione di tutti i test relativi alla gestione dei clienti.

  - Esegue in sequenza tutti i test richiamati al suo interno, validando i casi previsti

  @param NodoAlbero** radice -> Puntatore alla radice dell’albero dei clienti

  -Pre: radice != NULL

  @result stampa a console l’esito di ciascun test e scrive log su file

*/
void avvia_test_clienti(NodoAlbero** radice) {

    printf("\n--- TEST CLIENTI ---\n\n");

    test_cliente_valido(radice);
    test_cliente_dati_mancanti(radice);
    test_abbonamento_non_valido(radice);
    test_cliente_duplicato(radice);

}

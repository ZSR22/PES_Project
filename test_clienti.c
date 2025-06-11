/*
=====================================================
    File: test_clienti.c
    Descrizione: Funzione per testare la gestione dei clienti
    Autore: Salvatore Zurino
    Data: 10/06/2025
    Versione: 1.2
=======================================================

*/
/* File con funzioni per testare la gestione dei clienti */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "test_clienti.h"
#include "header_sorgenti/abbonamenti.h"
#include "header_sorgenti/Prenotazioni.h"
#include "header_sorgenti/Utilities.h"
#include "header_sorgenti/Catalogo_Lezioni.h"

 #define path_input_clienti "input/clienti.txt"
 #define path_oracolo_clienti "oracoli/clienti.txt"
 #define PATH_FILE_ABBONAMENTI "persistenza/clienti.json"
 #define MAX_CF 16

 /*

  Esegue un test generico di inserimento clienti leggendo input da file,
  tentando di aggiungere il cliente e confrontando l’output con un oracolo.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell’albero clienti
    @return stampa esito del test e scrive log

*/
static void test_inserimento_clienti() {
    FILE* input = fopen(path_input_clienti, "r");
    FILE* oracolo = fopen(path_oracolo_clienti, "r");
    if (input == NULL) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }
    assert(input != NULL && oracolo != NULL);
    NodoAlbero* radice = NULL;
    int cont = 0;

    do {
        Cliente c;
        fgets(c.nome, sizeof(c.nome), input);
        c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input);
        c.cognome[strcspn(c.cognome, "\n")] = '\0';

        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input);
        c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input);
        c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        if (nodo_valido != NULL) {
            radice = nodo_valido;
            bool cliente_salvato_su_file = salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
            char expected_result[16];
            if (fgets(expected_result, sizeof(expected_result), oracolo) != NULL) {
                expected_result[strcspn(expected_result, "\n")] = '\0';
                if ((cliente_salvato_su_file && strcmp(expected_result, "1") == 0) ||
                    (!cliente_salvato_su_file && strcmp(expected_result, "0") == 0)) {
                    printf("TC salvataggio cliente==>ok\n");
                } else {
                    printf("TC salvataggio cliente==>fail\n");
                }
            } else {
                printf("Errore lettura oracolo\n");
            }
        }
        cont++;
    } while (cont < 3);
    cont = 0;
    fclose(input);
    fclose(oracolo);
}
/*

  Esegue un test generico di ricerca clienti leggendo input da file,
  tentando di trovare il cliente e confrontando l’output con un oracolo.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell'albero clienti
    @return stampa esito del test e scrive log
    
*/
static void test_ricerca_clienti() {
    FILE* input = fopen(path_input_clienti, "r");
    FILE* oracolo = fopen(path_oracolo_clienti, "r");
    if (input == NULL) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }
    assert(input != NULL && oracolo != NULL);
    NodoAlbero* radice = NULL;
        char codice_fiscale[MAX_CF];
        fgets(codice_fiscale, sizeof(codice_fiscale), input);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
        char output_atteso[100];
        fgets(output_atteso, sizeof(output_atteso), oracolo);
        output_atteso[strcspn(output_atteso, "\n")] = '\0';

        if (nodo_trovato != NULL && strcmp(nodo_trovato->cliente.nome, output_atteso) == 0) {
            printf("TC ricerca cliente==>OK\n");
        } else {
            printf("TC ricerca cliente==>fail\n");
        }
    fclose(input);
    fclose(oracolo);
}
 /*

  Esegue un test generico di verifica dell'abbonamento valido leggendo input da file,
  tentando di trovare il cliente e confrontando l’output con un oracolo.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell'albero clienti
    @return stampa esito del test e scrive log

*/
static void test_abbonamento_valido() {
    FILE* input = fopen(path_input_clienti, "r");
    FILE* oracolo = fopen(path_oracolo_clienti, "r");
    if (input == NULL) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }
    assert(input != NULL);
    NodoAlbero* radice = NULL;

    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    NodoAlbero* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
    if (nodo_trovato != NULL) {
        char expected_result[16];
        fgets(expected_result, sizeof(expected_result), oracolo);
        expected_result[strcspn(expected_result, "\n")] = '\0';

        bool abbonamento = abbonamento_valido(nodo_trovato->cliente);
        if ((abbonamento && strcmp(expected_result, "1") == 0) ||
            (!abbonamento && strcmp(expected_result, "0") == 0)) {
            printf("Abbonamento valido==>ok\n");
        } else {
            printf("Abbonamento non valido==>fail\n");
        }
    } else {
        printf("Cliente non trovato==>fail\n");
    }

    fclose(input);
    fclose(oracolo);
}
 /*

  Esegue un test generico di eliminazione clienti leggendo input da file,
  tentando di eliminare il cliente e confrontando l’output con un oracolo.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell'albero clienti
    @return stampa esito del test e scrive log
*/
static void test_eliminazione_clienti() {                  
    FILE* input = fopen(path_input_clienti, "r");
    FILE* oracolo = fopen(path_oracolo_clienti, "r");
    if (input == NULL) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }
    assert(input != NULL && oracolo != NULL);
    NodoAlbero* radice = NULL;
    int c = 0;

    do {
        char codice_fiscale[MAX_CF];
        fgets(codice_fiscale, sizeof(codice_fiscale), input);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';
        NodoAlbero* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
        if (nodo_trovato != NULL) {
            radice = elimina_cliente(radice, nodo_trovato->cliente.codice_fiscale);
            bool cliente_eliminato_su_file = salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
            char expected_result[16];
            if (fgets(expected_result, sizeof(expected_result), oracolo) != NULL) {
                expected_result[strcspn(expected_result, "\n")] = '\0';
                if ((cliente_eliminato_su_file && strcmp(expected_result, "1") == 0) ||
                    (!cliente_eliminato_su_file && strcmp(expected_result, "0") == 0)) {
                    printf("TC eliminazione cliente==>ok\n");
                } else {
                    printf("TC eliminazione cliente==>fail\n");
                }
            } else {
                printf("Errore lettura oracolo\n");
            }
        } else {
            printf("Cliente non trovato==>ok\n");
        }
    } while (c < 2);
    fclose(input);
    fclose(oracolo);
}
 /*

  Esegue un test generico di visualizzazione clienti leggendo input da file,
  tentando di visualizzare i clienti e confrontando l’output con un oracolo.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell'albero clienti
    @return stampa esito del test e scrive log
*/
static void test_visualizzazione_clienti() {
    FILE* input = fopen(path_input_clienti, "r");
    if (input == NULL) {
        perror("Errore apertura file input");
        exit(EXIT_FAILURE);
    }
    assert(input != NULL);
    NodoAlbero* radice = NULL;

    printf("Visualizzazione clienti:\n");
    visualizza_clienti(radice);

    fclose(input);
}
 /*

  Esegue un test generico di caricamento clienti da file,
  tentando di caricare i clienti e verificando se la radice dell'albero non è NULL.
    @param int test_num -> Numero identificativo del test (per stampa e log)
    @param const char* input_path -> Percorso al file di input contenente i campi del test
    @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test
    @param const char* oracolo_path -> Percorso al file oracolo con output atteso
    @param NodoAlbero* radice -> Radice dell'albero clienti
    @return stampa esito del test e scrive log
*/
static void test_caricamento_clienti() {
    NodoAlbero* radice = NULL;
    carica_abbonamenti_da_file(PATH_FILE_ABBONAMENTI, &radice);
    if (radice != NULL) {
        printf("TC caricamento clienti==>ok\n");
    } else {
        printf("TC caricamento clienti==>fail\n");
    }
}

void test_clienti() {
    printf("Inizio test gestione clienti...\n");
    
    test_inserimento_clienti();
    test_ricerca_clienti();
    test_abbonamento_valido();
    test_visualizzazione_clienti();
    test_caricamento_clienti();
    test_eliminazione_clienti();

    printf("Test gestione clienti completati.\n");
}

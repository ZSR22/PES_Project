/* 
=============================================================================
 File: test_report.c
 Descrizione: Implementazioni delle funzioni di test eseguiti su generazione report
 Autore: Gianmarco Raimondi
 Data: 10/06/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdbool.h>
#include "test_report.h"
#include "test_utilities.h"
#include "header_sorgenti/report.h"

#define PATH_ORACOLO_REPORT_STANDARD     "oracoli/report_standard.txt"
#define PATH_ORACOLO_REPORT_ESISTENTE "oracoli/report_esistente.txt"

#define PATH_ESITO_REPORT_STANDARD       "esiti/report_standard.log"
#define PATH_ESITO_REPORT_ESISTENTE   "esiti/report_esistente.log"

/*

  Esegue un test generico di report tenta di creare il report e confornta l'esito con l'oracolo.

  @param int test_num -> Numero identificativo del test (per stampa e log)

  @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test

  @param const char* oracolo_path -> Percorso al file oracolo con output atteso

  @param Catalogo_Lezioni* catalogo -> Catalogo delle lezioni disponibili

  @param Lista_Prenotazioni* lista -> Lista delle prenotazioni attuali

  @param const char* messaggio_successo -> Messaggio da scrivere in caso di successo

  @param const char* messaggio_fallimento -> Messaggio da scrivere in caso di fallimento

  -Pre: la lista e il catalogo devono essere validi e inizializzati

  @return stampa esito del test e scrive log

*/
static void esegui_test_report(
    int test_num,
    const char* esito_path,
    const char* oracolo_path,
    Catalogo_Lezioni* catalogo,
    Lista_Prenotazioni* lista,
    const char* messaggio_successo,
    const char* messaggio_fallimento
) {
  FILE* file_esito = fopen(esito_path, "w");
    if (!file_esito) {
        stampa_fail(test_num, messaggio_successo, "Errore apertura file di log\n");
        return;
    }

    // Temporaneamente reindirizza stdout e stderr su log
    FILE* stdout_backup = stdout;
    FILE* stderr_backup = stderr;
    stdout = file_esito;
    stderr = file_esito;

    bool successo = genera_report_mensile(*lista, catalogo);

    
    fflush(file_esito);
    fclose(file_esito);
    stdout = stdout_backup;
    stderr = stderr_backup;

   if(successo){
        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }
    } else{
        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }
   }

}

/*

  Verifica che il report venga generato e il risultato ottenuto mostri informazioni complete.

  @param Catalogo_Lezioni* catalogo -> Catalogo delle lezioni disponibili

  @param Lista_Prenotazioni* lista -> Lista delle prenotazioni attuali

  -Scrive l’esito in: esiti/report_standard.log

  -Confronta il risultato con: oracolo/report_standard.txt

  -Pre: lista, catalogo != NULL

  @return stampa il risultato del test a console e registra l’esito nel file log

*/
static void test_report_standard(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {

    esegui_test_report(
        1,
        PATH_ESITO_REPORT_STANDARD,
        PATH_ORACOLO_REPORT_STANDARD,
        catalogo,
        lista,
        "Report generato correttamente",
        "Report non generato"
    );

}

/*

  Verifica che il report non venga generato e il messaggio di errore venga visionato correttamente.

  @param Catalogo_Lezioni* catalogo -> Catalogo delle lezioni disponibili

  @param Lista_Prenotazioni* lista -> Lista delle prenotazioni attuali
  
  -Scrive l’esito in: esiti/report_esistente.log

  -Confronta il risultato con: oracolo/report_esistente.txt

  -Pre: lista, catalogo != NULL

  @return stampa il risultato del test a console e registra l’esito nel file log

*/
static void test_report_esistente(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {
    
    esegui_test_report(
        2,
        PATH_ESITO_REPORT_ESISTENTE,
        PATH_ORACOLO_REPORT_ESISTENTE,
        catalogo,
        lista,
        "Il report sul mese attuale è stato già generato",
        "Report generato correttamente"
    );

}

/*

  Avvia l’esecuzione di tutti i test relativi alla generazione del report.

  - Esegue in sequenza tutti i test richiamati al suo interno

  @param Lista_Prenotazioni* lista -> Puntatore alla lista delle prenotazioni attuale

  @param Catalogo_Lezioni* catalogo -> Puntatore al catalogo delle lezioni disponibili

  -Pre: lista, catalogo != NULL

  @result stampa a console l’esito di ciascun test e scrive log su file

*/
void avvia_test_report(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {
    printf("\n--- TEST REPORT ---\n");

    test_report_standard(catalogo, lista);
    test_report_esistente(catalogo, lista);

}
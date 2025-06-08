#include <stdio.h>
#include <stdbool.h>
#include "test_report.h"
#include "test_utilities.h"
#include "header_sorgenti/report.h"

#define PATH_ORACOLO_REPORT_STANDARD     "test/oracoli/report_standard.txt"
#define PATH_ORACOLO_REPORT_ZERO_CLIENTI "test/oracoli/report_zero_clienti.txt"
#define PATH_ORACOLO_REPORT_ZERO_LEZIONI "test/oracoli/report_zero_lezioni.txt"

#define PATH_ESITO_REPORT_STANDARD       "test/esiti/report_standard.log"
#define PATH_ESITO_REPORT_ZERO_CLIENTI   "test/esiti/report_zero_clienti.log"
#define PATH_ESITO_REPORT_ZERO_LEZIONI   "test/esiti/report_zero_lezioni.log"


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
        fprintf(stderr, "Errore apertura file di log\n");
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

    if (!successo) {
        stampa_fail(test_num, messaggio_successo, "Errore generazione report");
        return;
    }

    if (confronta_output(esito_path, oracolo_path)) {
        stampa_ok(test_num);
    } else {
        stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
    }

}
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

static void test_report_zero_clienti(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {
    
    esegui_test_report(
        2,
        PATH_ESITO_REPORT_ZERO_CLIENTI,
        PATH_ORACOLO_REPORT_ZERO_CLIENTI,
        catalogo,
        lista,
        "Report generato correttamente",
        "Report non generato"
    );

}

static void test_report_zero_lezioni(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {
    
    esegui_test_report(
        3,
        PATH_ESITO_REPORT_ZERO_LEZIONI,
        PATH_ORACOLO_REPORT_ZERO_LEZIONI,
        catalogo,
        lista,
        "Report generato correttamente",
        "Report non generato"
    );

}

void avvia_test_report(Catalogo_Lezioni* catalogo, Lista_Prenotazioni* lista) {
    printf("\n--- TEST REPORT ---\n");
    test_report_standard(catalogo, lista);
    test_report_zero_clienti(catalogo, lista);
    test_report_zero_lezioni(catalogo, lista);
}
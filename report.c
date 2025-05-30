/*
=============================================================================
// File: report.c
 Descrizione: Implementazione della generazione di report mensili e salvataggio su file
 Autore: Salvatore Zurino
 Data: 29/05/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"
#include "abbonamenti.h"
#include "Prenotazione.h"
#include "Persistenza_Dati.h"
#include "lezioni.h"
#include "utils.h"
#include "clienti.h"

/**
 * Genera un report mensile delle prenotazioni e delle lezioni disponibili.
 * 
 * Questa funzione stampa un report mensile che include il numero totale di prenotazioni,
 * le lezioni disponibili e le prenotazioni effettuate. Inoltre, salva il report su un file.
 *
 * @param lista Puntatore alla lista delle prenotazioni.
 * @param catalogo Puntatore al catalogo delle lezioni.
 * * Precondizione:
 * - La lista delle prenotazioni e il catalogo delle lezioni non devono essere NULL.
 * * side effects:
 * - Stampa il report mensile sulla console.
 * - Salva il report su un file specificato da PATH_FILE_REPORT.
 * - Se la lista delle prenotazioni o il catalogo delle lezioni sono NULL, stampa un messaggio di errore.
 */
void genera_report_mensile(Lista_Prenotazioni* lista, Catalogo_Lezioni* catalogo) {
    if (lista == NULL || catalogo == NULL) {
        printf("Nessuna prenotazione o lezione disponibile per generare il report.\n");
        return;
    }

    printf("\n==== REPORT MENSILE ====\n");
    printf("Numero totale di prenotazioni: %d\n", lista->lunghezza);
    printf("Lezioni disponibili:\n");
    for (int i = 0; i < catalogo->numero_lezioni; i++) {
        Lezione* lezione = &catalogo->lezioni[i];
        printf("ID: %u, Nome: %s, Max Posti: %d\n", lezione->ID, lezione->nome, lezione->max_posti);
    }
    printf("===========================\n");
    printf("Prenotazioni effettuate:\n");
    for (int i = 0; i < lista->lunghezza; i++) {
        Prenotazione* prenotazione = &lista->prenotazioni[i];
        printf("ID: %u, Lezione: %s, Partecipante: %s %s\n",
               prenotazione->ID,
               prenotazione->lezione.nome,
               prenotazione->partecipante.nome,
               prenotazione->partecipante.cognome);
    }
    printf("===========================\n");
    printf("Report generato con successo.\n");
    salva_report_su_file(lista, catalogo, PATH_FILE_REPORT);
    printf("Report salvato in %s\n", PATH_FILE_REPORT);
}
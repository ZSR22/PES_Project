/*
=============================================================================
// File: report.c
 Descrizione: Implementazione della generazione di report mensili e salvataggio su file
 Autore: Salvatore Zurino && Gianmarco Raimondi
 Data: 29/05/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"
#include "Persistenza_Dati.h"
#include "Utilities.h"


/*
   Genera un report mensile delle prenotazioni e delle lezioni più frequentate.
   
   Stampa il report su console e ne salva una versione in formato JSON su file.
 
   @param lista Puntatore alla lista delle prenotazioni.
   @param catalogo* Puntatore al catalogo delle lezioni.
   
    Precondizione:
   - La lista delle prenotazioni e il catalogo delle lezioni != NULL.
    
   side effects:
    - Stampa il report mensile sulla console.
    - Alloca memoria dinamica per il conteggio delle prenotazioni per lezione poi liberata al termine.
    - Chiama salva_report_su_file per salvare il report su file JSON.
    - Se il report mensile è stato precendentemente generato, stamperà a video un avviso.

 */
void genera_report_mensile(const Lista_Prenotazioni lista, const Catalogo_Lezioni* catalogo) {
    
    if (lista == NULL || catalogo == NULL) {
        fprintf(stderr, "Errore: lista o catalogo vuoti.\n");
        return;
    }

    time_t ora_corrente = time(NULL);
    Orario_Tm* orario_tm = converti_orario_in_struct_tm(ora_corrente);

    if(report_esistente(orario_tm)){
        
        printf("Il report sul mese attuale è stato già generato\n");
        return;

    }

    int num_prenotazioni = 0;
    int* conteggio_lezioni = calloc(catalogo->numero_lezioni, sizeof(int));
    if (conteggio_lezioni == NULL) {
        fprintf(stderr, "Errore di allocazione memoria per conteggio lezioni.\n");
        return;
    }

    // Conta prenotazioni totali e frequenza per ogni lezione
    NodoPrenotazione* corrente = lista;
    while (corrente != NULL) {
        num_prenotazioni++;

        for (int i = 0; i < catalogo->numero_lezioni; i++) {
            if (catalogo->lezione[i].ID == corrente->prenotazione.lezione.ID) {
                conteggio_lezioni[i]++;
                break;
            }
        }

        corrente = corrente->next;
    }

    // Determina il massimo numero di prenotazioni tra le lezioni
    int max_prenotazioni = 0;
    for (int i = 0; i < catalogo->numero_lezioni; i++) {
        if (conteggio_lezioni[i] > max_prenotazioni) {
            max_prenotazioni = conteggio_lezioni[i];
        }
    }

    // Stampa il report
    printf("\n===== REPORT MENSILE =====\n");
    printf("Totale prenotazioni effettuate: %d\n", num_prenotazioni);

    if (max_prenotazioni > 0) {
        printf("\nLezioni più frequentate (%d prenotazioni):\n", max_prenotazioni);
        for (int i = 0; i < catalogo->numero_lezioni; i++) {
            if (conteggio_lezioni[i] == max_prenotazioni) {
                printf("- %s (ID: %u)\n",
                       catalogo->lezione[i].nome,
                       catalogo->lezione[i].ID);
            }
        }
    } else {
        printf("\nNessuna lezione ha ancora prenotazioni.\n");
    }

    char nome_file[64];
    snprintf(nome_file, sizeof(nome_file), "archivio_report/Report_%04d_%02d.json", orario_tm->tm_year, orario_tm->tm_mon);

    if(salva_report_su_file(catalogo, conteggio_lezioni, num_prenotazioni, nome_file, orario_tm)){
        printf("Report salvato su file: %s\n", nome_file);
    }

    printf("===========================\n");


    free(conteggio_lezioni);
}
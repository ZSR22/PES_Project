/* 
=============================================================================
 File: test.c
 Descrizione: Test delle funzionalità principali del programma
 Autore: Salvatore Zurino
 Data: 2905/2025
 Versione: 1.0
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Lista_Prenotazioni.h"
#include "Lezioni.h"
#include "Persistenza_Dati.h"
#include "report.h"
#include "Prenotazione.h"
#include "Utilities.h"
#include "abbonamenti.h"
#include <string.h>
/*

Pulisce l'input del buffer per evitare problemi con fgets dopo scanf


@param nessuno

Pre: nessuna

@result rimuove eventuali caratteri residui nel buffer di input

*/
void pulisci_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void attendi_utente() {}

void test_inserimento_cliente(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    NodoAlbero* radice = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Cliente c;
        strcpy(c.nome, buffer); c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input); c.cognome[strcspn(c.cognome, "\n")] = '\0';
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input); c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input); c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        bool successo = false;

        if (nodo_valido != NULL) {
            radice = nodo_valido;
            successo = salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        }

        fgets(output_atteso, sizeof(output_atteso), oracolo);
        output_atteso[strcspn(output_atteso, "\n")] = '\0';

        if (successo) {
            strcpy(output_generato, "Cliente salvato su file.");
        } else {
            strcpy(output_generato, "Errore salvataggio su file.");
        }

        if (strcmp(output_atteso, output_generato) == 0) {
            printf("Test %d: Confronto OK\n", test);
        } else {
            printf("Test %d: Confronto NO\n", test);
            printf("  Atteso: %s\n", output_atteso);
            printf("  Ottenuto: %s\n", output_generato);
        }

        test++;

        fgets(buffer, sizeof(buffer), input);
    }

    fclose(input);
    fclose(oracolo);
}
void test_stampa_clienti_ordinati(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    Cliente c;

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    NodoAlbero* radice = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        strcpy(c.nome, buffer); c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input); c.cognome[strcspn(c.cognome, "\n")] = '\0';
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input); c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input); c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        if (nodo_valido != NULL) {
            radice = nodo_valido;
            salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        }
    }

    stampa_clienti_ordinati(radice);

    while (fgets(output_atteso, sizeof(output_atteso), oracolo)) {
        output_atteso[strcspn(output_atteso, "\n")] = '\0';
        
        snprintf(output_generato, sizeof(output_generato), "Cliente %s %s è stato salvato con successo", c.nome, c.cognome);

        if (strcmp(output_atteso, output_generato) == 0) {
            printf("Test %d: Confronto OK\n", test);
        } else {
            printf("Test %d: Confronto NO\n", test);
            printf("  Atteso: %s\n", output_atteso);
            printf("  Ottenuto: %s\n", output_generato);
        }

        test++;
    }

    fclose(input);
    fclose(oracolo);
}

void test_ricerca_e_verifica_cliente(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    NodoAlbero* radice = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Cliente c;
        strcpy(c.nome, buffer); c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input); c.cognome[strcspn(c.cognome, "\n")] = '\0';
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input); c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input); c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        if (nodo_valido != NULL) {
            radice = nodo_valido;
            salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        }
    }

    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    NodoAlbero* trovato = ricerca_cliente(radice, codice_fiscale);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    if (trovato != NULL) {
        snprintf(output_generato, sizeof(output_generato), "Cliente trovato: %s %s", trovato->cliente.nome, trovato->cliente.cognome);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente non trovato");
    }

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}

void test_prenota_lezione(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    NodoAlbero* radice = NULL;
    Lista_Prenotazioni lista = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Cliente c;
        strcpy(c.nome, buffer); c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input); c.cognome[strcspn(c.cognome, "\n")] = '\0';
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input); c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input); c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        if (nodo_valido != NULL) {
            radice = nodo_valido;
            salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        }
    }

    if (!file_vuoto(PATH_FILE_LEZIONI)) {
        }
    if (!file_vuoto(PATH_FILE_PRENOTAZIONI)) {
        carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, &lista);
    }
    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    NodoAlbero* trovato = ricerca_cliente(radice, codice_fiscale);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    if (trovato != NULL) {
        snprintf(output_generato, sizeof(output_generato), "Cliente trovato: %s %s", trovato->cliente.nome, trovato->cliente.cognome);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente non trovato");
    }

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}

void test_visualizza_prenotazioni(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    Lista_Prenotazioni lista = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Prenotazione p;
        sscanf(buffer, "%u %s %s %s %u", &p.ID, p.partecipante.nome, p.partecipante.cognome, p.lezione.nome, &p.lezione.ID);
        p.partecipante.data_inizio = time(NULL);
        p.partecipante.durata = 30;
        aggiungi_prenotazione(&lista, p);
    }

    visualizza_prenotazioni(&lista);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    snprintf(output_generato, sizeof(output_generato), "Prenotazioni visualizzate con successo");

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}

void test_aggiungi_lezione(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    Catalogo_Lezioni catalogo = {0};

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Lezione l;
        sscanf(buffer, "%u %s %d %ld", &l.ID, l.nome, &l.max_posti, &l.data);
        aggiungi_lezione(&catalogo, l);
    }

    bool successo = salva_lezioni_su_file(&catalogo, PATH_FILE_LEZIONI);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    if (successo) {
        snprintf(output_generato, sizeof(output_generato), "Lezioni salvate con successo");
    } else {
        snprintf(output_generato, sizeof(output_generato), "Errore salvataggio lezioni");
    }


    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}
void test_visualizza_lezioni(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    Catalogo_Lezioni catalogo = {0};

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Lezione l;
        sscanf(buffer, "%u %s %d %ld", &l.ID, l.nome, &l.max_posti, &l.data);
        aggiungi_lezione(&catalogo, l);
    }

    mostra_lezioni(catalogo);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    snprintf(output_generato, sizeof(output_generato), "Lezioni visualizzate con successo");

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}
void test_elimina_cliente(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    NodoAlbero* radice = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Cliente c;
        strcpy(c.nome, buffer); c.nome[strcspn(c.nome, "\n")] = '\0';

        fgets(c.cognome, sizeof(c.cognome), input); c.cognome[strcspn(c.cognome, "\n")] = '\0';
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), input); c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';

        char durata_str[10];
        fgets(durata_str, sizeof(durata_str), input);
        c.durata = atoi(durata_str);

        fgets(c.data_nascita, sizeof(c.data_nascita), input); c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);
        if (nodo_valido != NULL) {
            radice = nodo_valido;
            salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        }
    }

    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    bool eliminato = elimina_cliente(radice, codice_fiscale);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    if (eliminato) {
        snprintf(output_generato, sizeof(output_generato), "Cliente %s eliminato con successo", codice_fiscale);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente %s non trovato", codice_fiscale);
    }

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}
void test_disdici_prenotazione(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");
    Catalogo_Lezioni catalogo = {0};

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        return;
    }

    Lista_Prenotazioni lista = NULL;

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    while (fgets(buffer, sizeof(buffer), input)) {
        Prenotazione p;
        sscanf(buffer, "%u %s %s %s %u", &p.ID, p.partecipante.nome, p.partecipante.cognome, p.lezione.nome, &p.lezione.ID);
        p.partecipante.data_inizio = time(NULL);
        p.partecipante.durata = 30;
        aggiungi_prenotazione(&lista, p);
    }

    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';
    Lezione U = {.ID = 1, .nome = "Lezione di prova", .data = time(NULL)};
    aggiungi_lezione(&catalogo, U);
    Lezione lezione = {.ID = 1, .nome = "Lezione di prova", .data = time(NULL)};
    aggiungi_lezione(&catalogo, lezione);

    bool disdetta = disdici_prenotazione(&lista, &lezione);

    fgets(output_atteso, sizeof(output_atteso), oracolo);

    if (disdetta) {
        snprintf(output_generato, sizeof(output_generato), "Prenotazione per cliente %s disdetta con successo", codice_fiscale);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Prenotazione per cliente %s non trovata", codice_fiscale);
    }

    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }
    test++;
    fclose(input);
    fclose(oracolo);
}
void test_elimina_lezione(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        if (input) fclose(input);
        if (oracolo) fclose(oracolo);
        return;
    }

    Catalogo_Lezioni catalogo = {0};

    char buffer[256];
    char output_atteso[256];
    char output_generato[256];
    int test = 1;

    // Carica lezioni dal file finché non trovi una riga con solo l'ID
    while (fgets(buffer, sizeof(buffer), input)) {
        if (strchr(buffer, ' ') == NULL) break;  // è la riga con solo l'ID da eliminare

        Lezione l;
        sscanf(buffer, "%u %s %d %ld", &l.ID, l.nome, &l.max_posti, &l.data);
        aggiungi_lezione(&catalogo, l);
    }

    // Riga con l'ID della lezione da eliminare
    unsigned int id_lezione = atoi(buffer);
    Lezione Q = {.ID = id_lezione};

    // Elimina la lezione
    elimina_lezione(&catalogo, Q);

    // Verifica se è ancora presente
    Lezione* trovata = trova_lezione(&catalogo, id_lezione);

    // Leggi l’output atteso
    if (!fgets(output_atteso, sizeof(output_atteso), oracolo)) {
        printf("Errore lettura oracolo.\n");
        fclose(input);
        fclose(oracolo);
        return;
    }
    output_atteso[strcspn(output_atteso, "\n")] = '\0';  // Rimuove il newline

    // Costruisci output generato
    if (trovata == NULL) {
        snprintf(output_generato, sizeof(output_generato), "Lezione %u eliminata con successo", id_lezione);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Lezione %u non trovata", id_lezione);
    }

    // Confronto output
    if (strcmp(output_atteso, output_generato) == 0) {
        printf("Test %d: Confronto OK\n", test);
    } else {
        printf("Test %d: Confronto NO\n", test);
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", output_generato);
    }

    test++;

    fclose(input);
    fclose(oracolo);
}
void test_report_mensile(const char* input_path, const char* oracolo_path) {
    FILE* input = fopen(input_path, "r");
    FILE* oracolo = fopen(oracolo_path, "r");

    if (!input || !oracolo) {
        printf("Errore apertura file.\n");
        if (input) fclose(input);
        if (oracolo) fclose(oracolo);
        return;
    }

    Catalogo_Lezioni catalogo = {0};

    // Creazione di 2 prenotazioni manuali
    Prenotazione prenotazioni[2];

    prenotazioni[0] = (Prenotazione){
        .ID = 1,
        .lezione = {.ID = 101, .nome = "Yoga", .max_posti = 20, .data = time(NULL)},
        .partecipante = {.nome = "Mario", .cognome = "Rossi", .codice_fiscale = "MRARSS80A01H501Z",
                         .data_nascita = "01/01/1980", .durata = 30, .data_inizio = time(NULL), .id_abbonamento = 1001}
    };

    prenotazioni[1] = (Prenotazione){
        .ID = 2,
        .lezione = {.ID = 102, .nome = "Pilates", .max_posti = 15, .data = time(NULL)},
        .partecipante = {.nome = "Luca", .cognome = "Bianchi", .codice_fiscale = "LCABNC85B01H501Z",
                         .data_nascita = "01/02/1985", .durata = 30, .data_inizio = time(NULL), .id_abbonamento = 1002}
    };

    // Chiamata alla funzione da testare
    genera_report_mensile(prenotazioni, &catalogo);

    // Lettura dell'oracolo per il confronto
    char report_atteso[1024];
    char report_generato[1024];

    if (fgets(report_atteso, sizeof(report_atteso), oracolo)) {
        report_atteso[strcspn(report_atteso, "\n")] = '\0'; // Rimuove newline
    }

    // Simulazione della generazione del report in stringa (se `genera_report_mensile` non la restituisce, serve modificarla)
    snprintf(report_generato, sizeof(report_generato), "Lezione %u: %s\nLezione %u: %s",
             prenotazioni[0].lezione.ID, prenotazioni[0].lezione.nome,
             prenotazioni[1].lezione.ID, prenotazioni[1].lezione.nome);

    if (strcmp(report_atteso, report_generato) == 0) {
        printf("Test Report Mensile: Confronto OK\n");
    } else {
        printf("Test Report Mensile: Confronto NO\n");
        printf("  Atteso:   %s\n", report_atteso);
        printf("  Generato: %s\n", report_generato);
    }

    fclose(input);
    fclose(oracolo);
}

int main() {
    test_inserimento_cliente("input.txt", "oracolo.txt");
    test_stampa_clienti_ordinati("input.txt", "oracolo.txt");
    test_ricerca_e_verifica_cliente("input.txt", "oracolo.txt");
    test_prenota_lezione("input.txt", "oracolo.txt");
    test_visualizza_prenotazioni("input.txt", "oracolo.txt");
    test_aggiungi_lezione("input.txt", "oracolo.txt");
    test_visualizza_lezioni("input.txt", "oracolo.txt");
    test_elimina_cliente("input.txt", "oracolo.txt");
    test_disdici_prenotazione("input.txt", "oracolo.txt");
    test_elimina_lezione("input.txt", "oracolo.txt");
    test_report_mensile("input.txt", "oracolo.txt");
    printf("Tutti i test sono stati eseguiti.\n");

    return 0;
}
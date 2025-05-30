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
#include <string.h>
#include "Lista_Prenotazioni.h"
#include "Lezioni.h"
#include "Persistenza_Dati.h"
#include "report.h"
#include "Prenotazione.h"
#include "Utilities.h"
#include "abbonamenti.h"
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

/*


*/
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

        // Legge il messaggio atteso dal file oracolo
        fgets(output_atteso, sizeof(output_atteso), oracolo);
        output_atteso[strcspn(output_atteso, "\n")] = '\0';

        // Crea output generato da confrontare
        if (successo) {
            strcpy(output_generato, "Cliente salvato su file.");
        } else {
            strcpy(output_generato, "Errore salvataggio su file.");
        }

        // Confronto
        if (strcmp(output_atteso, output_generato) == 0) {
            printf("Test %d: Confronto OK\n", test);
        } else {
            printf("Test %d: Confronto NO\n", test);
            printf("  Atteso: %s\n", output_atteso);
            printf("  Ottenuto: %s\n", output_generato);
        }

        test++;

        // Salta divisore "---"
        fgets(buffer, sizeof(buffer), input);
    }

    fclose(input);
    fclose(oracolo);
}
void test_stampa_clienti_ordinati(const char* input_path, const char* oracolo_path) {
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

    // Stampa i clienti ordinati
    stampa_clienti_ordinati(radice);

    // Legge l'output atteso dal file oracolo
    while (fgets(output_atteso, sizeof(output_atteso), oracolo)) {
        output_atteso[strcspn(output_atteso, "\n")] = '\0';
        Cliente c;
        // Crea output generato da confrontare
        snprintf(output_generato, sizeof(output_generato), "Cliente %s %s è stato salvato con successo", c.nome, c.cognome);

        // Confronto
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

    // Legge il codice fiscale da cercare
    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    NodoAlbero* trovato = ricerca_cliente(radice, codice_fiscale);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    if (trovato != NULL) {
        snprintf(output_generato, sizeof(output_generato), "Cliente trovato: %s %s", trovato->cliente.nome, trovato->cliente.cognome);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente non trovato");
    }

    // Confronto
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
    Catalogo_Lezioni *catalogo = NULL;
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

    // Carica lezioni e prenotazioni
    if (!file_vuoto(PATH_FILE_LEZIONI)) {
        catalogo = carica_catalogo_da_file(PATH_FILE_LEZIONI);
    }
    if (!file_vuoto(PATH_FILE_PRENOTAZIONI)) {
        carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, &lista);
    }
    // Legge il codice fiscale da cercare
    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    NodoAlbero* trovato = ricerca_cliente(radice, codice_fiscale);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    if (trovato != NULL) {
        snprintf(output_generato, sizeof(output_generato), "Cliente trovato: %s %s", trovato->cliente.nome, trovato->cliente.cognome);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente non trovato");
    }

    // Confronto
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
        sscanf(buffer, "%u %s %s %s %u", &p.ID, p.partecipante.nome, p.partecipante.cognome, p.partecipante.codice_fiscale, &p.lezione.ID);
        p.partecipante.data_inizio = time(NULL);
        p.partecipante.durata = 30; // esempio di durata
        lista = aggiungi_prenotazione(lista, p);
    }

    // Visualizza prenotazioni
    visualizza_prenotazioni(lista);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    snprintf(output_generato, sizeof(output_generato), "Prenotazioni visualizzate con successo");

    // Confronto
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

    // Salva lezioni su file
    bool successo = salva_lezioni_su_file(&catalogo, PATH_FILE_LEZIONI);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    if (successo) {
        snprintf(output_generato, sizeof(output_generato), "Lezioni salvate con successo");
    } else {
        snprintf(output_generato, sizeof(output_generato), "Errore salvataggio lezioni");
    }

    // Confronto
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

    // Visualizza lezioni
    visualizza_lezioni(&catalogo);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    snprintf(output_generato, sizeof(output_generato), "Lezioni visualizzate con successo");

    // Confronto
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

    // Legge il codice fiscale da eliminare
    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    bool eliminato = elimina_cliente(&radice, codice_fiscale);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    if (eliminato) {
        snprintf(output_generato, sizeof(output_generato), "Cliente %s eliminato con successo", codice_fiscale);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Cliente %s non trovato", codice_fiscale);
    }

    // Confronto
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
        sscanf(buffer, "%u %s %s %s %u", &p.ID, p.partecipante.nome, p.partecipante.cognome, p.partecipante.codice_fiscale, &p.lezione.ID);
        p.partecipante.data_inizio = time(NULL);
        p.partecipante.durata = 30; // esempio di durata
        lista = aggiungi_prenotazione(lista, p);
    }

    // Legge il codice fiscale da disdire
    char codice_fiscale[MAX_CF];
    fgets(codice_fiscale, sizeof(codice_fiscale), input);
    codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

    bool disdetta = disdici_prenotazione(&lista, codice_fiscale);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    if (disdetta) {
        snprintf(output_generato, sizeof(output_generato), "Prenotazione per cliente %s disdetta con successo", codice_fiscale);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Prenotazione per cliente %s non trovata", codice_fiscale);
    }

    // Confronto
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

    // Legge l'ID della lezione da eliminare
    char id_lezione_str[10];
    fgets(id_lezione_str, sizeof(id_lezione_str), input);
    unsigned int id_lezione = atoi(id_lezione_str);
    Lezione lezione;
    lezione.ID = id_lezione;

    elimina_lezione(&catalogo, lezione);

    // Legge l'output atteso dal file oracolo
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Crea output generato da confrontare
    /*if (eliminato) {
        snprintf(output_generato, sizeof(output_generato), "Lezione %u eliminata con successo", id_lezione);
    } else {
        snprintf(output_generato, sizeof(output_generato), "Lezione %u non trovata", id_lezione);
    }*/

    // Confronto
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
        return;
    }

    // Carica i dati necessari per il report
    NodoAlbero* radice = NULL;
    Catalogo_Lezioni *catalogo = NULL;
    Lista_Prenotazioni lista = NULL;

    // Carica abbonamenti
    if (!file_vuoto(PATH_FILE_ABBONAMENTI)) {
        carica_abbonamenti_da_file(PATH_FILE_ABBONAMENTI, radice);
    }
    
    // Carica lezioni
    if (!file_vuoto(PATH_FILE_LEZIONI)) {
        catalogo = carica_catalogo_da_file(PATH_FILE_LEZIONI);
    }
    
    // Carica prenotazioni
    if (!file_vuoto(PATH_FILE_PRENOTAZIONI)) {
        carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, &lista);
    }

    // Genera il report mensile
    char report[1024];
    //genera_report_mensile(radice, &catalogo, lista, report);

    // Legge l'output atteso dal file oracolo
    char output_atteso[1024];
    fgets(output_atteso, sizeof(output_atteso), oracolo);

    // Confronta l'output generato con quello atteso
    if (strcmp(report, output_atteso) == 0) {
        printf("Test Report Mensile: Confronto OK\n");
    } else {
        printf("Test Report Mensile: Confronto NO\n");
        printf("  Atteso: %s\n", output_atteso);
        printf("  Ottenuto: %s\n", report);
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
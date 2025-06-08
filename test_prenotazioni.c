/* 
=============================================================================
 File: test_prenotazioni.h
 Descrizione: Implementazioni delle funzioni di test eseguiti su registrazione di prenotazione
 Autore: Gianmarco Raimondi
 Data: 06/06/2025
 Versione: 1.0
=============================================================================
*/
#include <string.h>
#include "test_prenotazioni.h"
#include "test_utilities.h"
#include "header_sorgenti/Persistenza_Dati.h"

#define PATH_INPUT_PRENOTAZIONE_CLIENTE_REGISTRATO   "input/prenotazione_cliente.txt"
#define PATH_INPUT_CLIENTE_INESISTENTE "input/prenotazione_cliente_inesistente.txt"
#define PATH_INPUT_PRENOTAZIONE_LEZIONE_PIENA "input/prenotazione_lezione_piena.txt"
#define PATH_INPUT_PRENOTAZIONE_ORARI_SOVRAPPOSTI "input/prenotazione_orario_sovrapposto.txt"
#define PATH_INPUT_PRENOTAZIONE_ID_INVALIDO "input/prenotazione_id_invalido.txt"
#define PATH_INPUT_PRENOTAZIONE_DUPLICATA "input/prenotazione_duplicata.txt"
#define PATH_INPUT_CF_MALFORMATO "input/prenotazione_cf_malformato.txt"
#define PATH_INPUT_LEZIONE_PASSATA "input/prenotazione_lezione_passata.txt"

#define PATH_ORACOLO_PRENOTAZIONE_CLIENTE_REGISTRATO "oracoli/prenotazione_cliente.txt"
#define PATH_ORACOLO_CLIENTE_INESISTENTE "oracoli/prenotazione_cliente_inesistente.txt"
#define PATH_ORACOLO_PRENOTAZIONE_LEZIONE_PIENA "oracoli/prenotazione_lezione_piena.txt"
#define PATH_ORACOLO_PRENOTAZIONE_ORARI_SOVRAPPOSTI "oracoli/prenotazione_orario_sovrapposto.txt"
#define PATH_ORACOLO_PRENOTAZIONE_ID_INVALIDO "oracoli/prenotazione_id_invalido.txt"
#define PATH_ORACOLO_PRENOTAZIONE_DUPLICATA "oracoli/prenotazione_duplicata.txt"
#define PATH_ORACOLO_CF_MALFORMATO "oracoli/prenotazione_cf_malformato.txt"
#define PATH_ORACOLO_LEZIONE_PASSATA "oracoli/prenotazione_lezione_passata.txt"

#define PATH_ESITO_PRENOTAZIONE_CLIENTE_REGISTRATO   "esiti/prenotazione_cliente.log"
#define PATH_ESITO_CLIENTE_INESISTENTE "esiti/prenotazione_cliente_inesistente.log"
#define PATH_ESITO_PRENOTAZIONE_LEZIONE_PIENA "esiti/prenotazione_lezione_piena.log"
#define PATH_ESITO_PRENOTAZIONE_ORARI_SOVRAPPOSTI "esiti/prenotazione_orario_sovrapposto.log"
#define PATH_ESITO_PRENOTAZIONE_ID_INVALIDO "esiti/prenotazione_id_invalido.log"
#define PATH_ESITO_PRENOTAZIONE_DUPLICATA "esiti/prenotazione_duplicata.log"
#define PATH_ESITO_CF_MALFORMATO "esiti/prenotazione_cf_malformato.log"
#define PATH_ESITO_LEZIONE_PASSATA "esiti/prenotazione_lezione_passata.log"

#define NUM_CAMPI_PRENOTAZIONE 2

/*

  Esegue un test generico di prenotazione leggendo input da file,
  tentando di aggiungere la prenotazione e confrontando l’output con un oracolo.

  @param int test_num -> Numero identificativo del test (per stampa e log)

  @param const char* input_path -> Percorso al file di input contenente i campi del test

  @param const char* esito_path -> Percorso al file in cui scrivere l’esito del test

  @param const char* oracolo_path -> Percorso al file oracolo con output atteso

  @param Lista_Prenotazioni* lista -> Lista delle prenotazioni attuali

  @param NodoAlbero* radice -> Radice dell’albero clienti

  @param Catalogo_Lezioni* catalogo -> Catalogo delle lezioni disponibili

  @param const char* messaggio_successo -> Messaggio da scrivere in caso di successo

  @param const char* messaggio_fallimento -> Messaggio da scrivere in caso di fallimento

  -Pre: i file di input e oracolo devono esistere e contenere i campi necessari

  -Pre: la lista, l’albero e il catalogo devono essere validi e inizializzati

  @return stampa esito del test e scrive log
*/
static void esegui_test_prenotazione(
    int test_num,
    const char* input_path,
    const char* esito_path,
    const char* oracolo_path,
    Lista_Prenotazioni* lista,
    NodoAlbero* radice,
    Catalogo_Lezioni* catalogo,
    const char* messaggio_successo,
    const char* messaggio_fallimento
) {

    FILE* file_input = fopen(input_path, "r");
    if (!file_input) {
        perror("Errore apertura file input");
        stampa_fail(test_num, "file input presente", "impossibile aprire file");
        return;
    }

    char* campi[NUM_CAMPI_PRENOTAZIONE] = { NULL };
    char buffer[256];
    bool errore_input = false;

    for (int i = 0; i < NUM_CAMPI_PRENOTAZIONE; i++) {
        if (fgets(buffer, sizeof(buffer), file_input) == NULL) {
            stampa_fail(test_num, "campi presenti", "campo mancante nel file input");
            errore_input = true;
            break;
        }

        buffer[strcspn(buffer, "\r\n")] = '\0';
        campi[i] = duplica_stringa(buffer);
    }

    fclose(file_input);

    if (errore_input) {
        for (int i = 0; i < NUM_CAMPI_PRENOTAZIONE; i++) {
            if (campi[i]) free(campi[i]);
        }
        return;
    }

    if (!blocco_valido(campi, NUM_CAMPI_PRENOTAZIONE)) {
        stampa_fail(test_num, "campi validi", "campi nulli o vuoti");
        for (int i = 0; i < NUM_CAMPI_PRENOTAZIONE; i++) {
            free(campi[i]);
        }
        return;
    }

    const char* codice_fiscale = campi[0];
    unsigned int id_lezione = (unsigned int) strtoul(campi[1], NULL, 10);

    NodoAlbero* cliente_trovato = ricerca_cliente(radice, codice_fiscale);
    Lezione* lezione_trovata = trova_lezione(catalogo, id_lezione);
    if(!codice_fiscale_valido(codice_fiscale)){
        scrivi_log(esito_path, "Codice fiscale non valido");
    } else if (!cliente_trovato) {
        scrivi_log(esito_path, "Codice fiscale cliente non trovato");
    } else if (!lezione_trovata) {
        scrivi_log(esito_path, "ID lezione non trovato");
    } else {
        
        Prenotazione nuova;
        nuova.ID = genera_id_univoco(PATH_FILE_PRENOTAZIONI);
        nuova.partecipante = cliente_trovato->cliente;
        nuova.lezione = *lezione_trovata;

        bool esito = true;
        if (controllo_conflitto_orario(*lista, nuova.lezione, cliente_trovato->cliente)) {
            scrivi_log(esito_path, "Prenotazione già registrata");
            esito = false;
        } else if (lezione_piena(*lista, *lezione_trovata)) {
            scrivi_log(esito_path, "Lezione piena");
            esito = false;
        }
        if(esito){
            if (aggiungi_prenotazione(lista, nuova)) {
                scrivi_log(esito_path, messaggio_successo); 
            } else {
                scrivi_log(esito_path, "Prenotazione non registrata");
            }
        }
        
        
    }

    FILE* oracolo = fopen(oracolo_path, "r");
    if (!oracolo) {
        stampa_fail(test_num, "file oracolo presente", "file oracolo mancante");
    } else {
        fclose(oracolo);
        if (confronta_output(esito_path, oracolo_path)) {
            stampa_ok(test_num);
        } else {
            stampa_fail(test_num, messaggio_successo, messaggio_fallimento);
        }
    }

    for (int i = 0; i < NUM_CAMPI_PRENOTAZIONE; i++) {
        free(campi[i]);
        campi[i] = NULL;
    }

}

/*

  Verifica che una prenotazione effettuata da un cliente registrato
  venga accettata correttamente dal sistema.

  -Usa come input il file: input/prenotazione_cliente_registrato.txt

  -Scrive l’esito in: esiti/prenotazione_cliente_registrato.log

  -Confronta il risultato con: oracolo/prenotazione_cliente_registrato.txt

  -Pre: lista, radice, catalogo != NULL

  @return stampa il risultato del test a console e registra l’esito nel file log

*/
static void test_prenotazione_cliente_registrato(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo){

    esegui_test_prenotazione(
        1,
        PATH_INPUT_PRENOTAZIONE_CLIENTE_REGISTRATO,
        PATH_ESITO_PRENOTAZIONE_CLIENTE_REGISTRATO,
        PATH_ORACOLO_PRENOTAZIONE_CLIENTE_REGISTRATO,
        lista, radice, catalogo,
        "Prenotazione registrata correttamente",
        "Prenotazione non registrata"
    );   
    
}

/*

  Verifica che la prenotazione con codice fiscale cliente inesistente
  venga gestita correttamente dal sistema

  -Usa come input il file: input/prenotazione_cliente_inesistente.txt

  -Scrive l’esito in: esiti/prenotazione_cliente_inesistente.log

  -Confronta il risultato con: oracolo/prenotazione_cliente_inesistente.txt

  -Pre: radice != NULL

  @return stampa il risultato del test a console e registra l’esito nel file log

*/
static void test_prenotazione_cliente_inesistente(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo){

    esegui_test_prenotazione(
        2,
        PATH_INPUT_CLIENTE_INESISTENTE,
        PATH_ESITO_CLIENTE_INESISTENTE,
        PATH_ORACOLO_CLIENTE_INESISTENTE,
        lista, radice, catalogo,
        "Codice fiscale cliente non trovato",
        "Codice fiscale cliente trovato"
    );

}

/*

  Verifica che una prenotazione per una lezione piena venga correttamente
  rifiutata dal sistema.

  -Usa come input il file: input/prenotazione_lezione_piena.txt
  
  -Scrive l’esito in: esiti/prenotazione_lezione_piena.log
  
  -Confronta il risultato con: oracolo/prenotazione_lezione_piena.txt

  -Pre: i file input e oracolo devono esistere e contenere due righe (CF e ID lezione)
  @return stampa il risultato del test a console e registra l’esito nel file log

*/
static void test_prenotazione_lezione_piena(Lista_Prenotazioni *lista, NodoAlbero* radice, Catalogo_Lezioni *catalogo){

    esegui_test_prenotazione(
        3,
        PATH_INPUT_PRENOTAZIONE_LEZIONE_PIENA,
        PATH_ESITO_PRENOTAZIONE_LEZIONE_PIENA,
        PATH_ORACOLO_PRENOTAZIONE_LEZIONE_PIENA,
        lista, radice, catalogo,
        "Lezione piena",
        "Prenotazione accettata"
    );

}

/*

  Verifica che una prenotazione con ID lezione non esistente
  venga correttamente rifiutata dal sistema.

  - Usa input: input/prenotazione_id_invalido.txt

  - Scrive esito in: esiti/prenotazione_id_invalido.log

  - Confronta con oracolo: oracolo/prenotazione_id_invalido.txt

  @pre il file input contiene codice fiscale e un ID non presente nel catalogo
  
  @return stampa l’esito del test a console e registra il risultato nel log

*/
static void test_prenotazione_id_lezione_non_valido(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo) {
    esegui_test_prenotazione(
        4,
        PATH_INPUT_PRENOTAZIONE_ID_INVALIDO,
        PATH_ESITO_PRENOTAZIONE_ID_INVALIDO,
        PATH_ORACOLO_PRENOTAZIONE_ID_INVALIDO,
        lista, radice, catalogo,
        "ID lezione non trovato",
        "Prenotazione accettata"
    );
}

/*

  Verifica che una prenotazione duplicata per la stessa lezione
  venga correttamente rifiutata dal sistema.

  - Usa input: input/prenotazione_duplicata.txt

  - Scrive esito in: esiti/prenotazione_duplicata.log

  - Confronta con oracolo: oracolo/prenotazione_duplicata.txt

  @pre il cliente è già prenotato per la stessa lezione
  @return stampa l’esito del test a console e registra il risultato nel log

*/
static void test_prenotazione_duplicata(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo) {
    esegui_test_prenotazione(
        5,
        PATH_INPUT_PRENOTAZIONE_DUPLICATA,
        PATH_ESITO_PRENOTAZIONE_DUPLICATA,
        PATH_ORACOLO_PRENOTAZIONE_DUPLICATA,
        lista, radice, catalogo,
        "Prenotazione già registrata",
        "Prenotazione accettata"
    );
}

/*

  Verifica che una prenotazione con codice fiscale malformato (es. vuoto o troppo corto)
  venga bloccata come input non valido.

  - Usa input: input/prenotazione_cf_malformato.txt

  - Scrive esito in: esiti/prenotazione_cf_malformato.log

  - Confronta con oracolo: oracolo/prenotazione_cf_malformato.txt

  @pre il codice fiscale nel file è vuoto o malformato

  @return stampa l’esito del test a console e registra il risultato nel log

*/
static void test_prenotazione_codice_fiscale_malformato(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo) {
    esegui_test_prenotazione(
        6,
        PATH_INPUT_CF_MALFORMATO,
        PATH_ESITO_CF_MALFORMATO,
        PATH_ORACOLO_CF_MALFORMATO,
        lista, radice, catalogo,
        "Codice fiscale non valido",
        "Prenotazione accettata"
    );
}

/*
  
Verifica che una prenotazione per una lezione con data già superata
  venga rifiutata dal sistema.

  - Usa input: input/prenotazione_lezione_passata.txt

  - Scrive esito in: esiti/prenotazione_lezione_passata.log

  - Confronta con oracolo: oracolo/prenotazione_lezione_passata.txt

  @pre il file contiene una lezione con data antecedente alla data corrente
  
  @return stampa l’esito del test a console e registra il risultato nel log

*/
static void test_prenotazione_lezione_passata(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo) {
    esegui_test_prenotazione(
        7,
        PATH_INPUT_LEZIONE_PASSATA,
        PATH_ESITO_LEZIONE_PASSATA,
        PATH_ORACOLO_LEZIONE_PASSATA,
        lista, radice, catalogo,
        "Lezione non disponibile (data scaduta)",
        "Prenotazione accettata"
    );
}
/*

  Avvia l’esecuzione di tutti i test relativi alla gestione delle prenotazioni.

  - Esegue in sequenza tutti i test richiamati al suo interno

  @param Lista_Prenotazioni* lista -> Puntatore alla lista delle prenotazioni attuale
  @param NodoAlbero* radice -> Puntatore alla radice dell’albero dei clienti
  @param Catalogo_Lezioni* catalogo -> Puntatore al catalogo delle lezioni disponibili

  -Pre: tutte le strutture devono essere inizializzate

  @result stampa a console l’esito di ciascun test e logga su file

*/
void avvia_test_prenotazioni(Lista_Prenotazioni *lista, NodoAlbero *radice, Catalogo_Lezioni *catalogo){

    printf("\n--- TEST PRENOTAZIONI ---\n\n");

    test_prenotazione_cliente_registrato(lista, radice, catalogo);
    test_prenotazione_cliente_inesistente(lista, radice, catalogo);
    test_prenotazione_lezione_piena(lista, radice, catalogo);
    test_prenotazione_id_lezione_non_valido(lista, radice, catalogo);
    test_prenotazione_duplicata(lista, radice, catalogo);
    test_prenotazione_codice_fiscale_malformato(lista, radice, catalogo);
    test_prenotazione_lezione_passata(lista, radice, catalogo);

}

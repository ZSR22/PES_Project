#  Checklist Implementazione Completa - Suite di Testing PES_Project

---

##  Core Utilities (test_utils.c/h)

- [X] Aggiungere funzione: `confronta_output(const char* file1, const char* file2);`
- [X] Aggiungere funzione: `scrivi_log(const char* path, const char* messaggio);`
- [X] Aggiungere funzione: `stampa_ok(int test_num);`
- [X] Aggiungere funzione: `stampa_fail(int test_num, const char* atteso, const char* ottenuto);`
- [X] Aggiungere macro ANSI per output colorato (verde/rosso)
- [X] Funzione: `riga_oracolo_presente(FILE* oracolo, int test_num);`
- [X] Funzione: `valida_blocco_cliente(char** campi, int numero_campi);`
- [ ] Eventuali funzioni analoghe per prenotazioni e report -> Opzionale

---

##  test_clienti.c

- [ ] Implementare test: cliente valido
- [ ] Implementare test: cliente con dati mancanti
- [ ] Implementare test: abbonamento con durata zero
- [ ] Validare input con `valida_blocco()`
- [ ] Gestione output con `scrivi_log()` e confronto con oracolo
- [ ] Stampa esito con colori in console

---

##  test_prenotazioni.c

- [X] Test prenotazione con cliente registrato
- [X] Test prenotazione con cliente non esistente
- [X] Test prenotazione con lezione piena o orario sovrapposto

---

##  test_report.c

- [ ] Test generazione report corretto
- [ ] Test report con 0 clienti o lezioni
- [ ] Confronto file completo output vs oracolo (`confronta_file_completo()`)
- [ ] Eventuale `valida_blocco_report(...)`

---

##  test_main.c

- [ ] Eseguire: `test_clienti()`, `test_prenotazioni()`, `test_report()`
- [ ] Contatori: `ok`, `fail`, `totali`
- [ ] Stampare riepilogo finale dei test
- [ ] Restituire `exit(1)` se `fail > 0`

---

##  Makefile

- [ ] Target `make test`: compila ed esegue la suite
- [ ] Target `make clean`: pulisce `.o`, `test_suite`, `esiti/*.log`
- [ ] Eventuale clean avanzata per file temporanei

---

## input/ e oracolo/

- [ ] Creare file di input per test clienti
- [ ] Creare file oracolo corrispondente
- [ ] Idem per prenotazioni e report

---

##  Extra (facoltativi)

- [ ] Test con oracolo mancante -> verifica fallback/error log
- [ ] Test con input incompleto -> verifica blocco cliente
- [ ] Documentare ogni funzione in Report


# Guida per l'Implementazione dei Test sull'Area Clienti – Progetto SGP

##  Obiettivo

Questa guida descrive come strutturare e implementare i test per la gestione dei clienti (inserimento, validazione, errori) in modo coerente con l'architettura dei test sulle prenotazioni.

---

##  Struttura dei File

Tutti i test e file associati devono seguire questa struttura:

```
test/
├── test_clienti.c
├── test_clienti.h
├── input/
│   └── cliente_valido.txt
├── oracolo/
│   └── cliente_valido.txt
├── esiti/
│   └── cliente_valido.log
```

---

##  Tipi di test da verificare

| Test # | Descrizione                          | Output atteso                      |
| ------ | ------------------------------------ | ---------------------------------- |
| 1      | Inserimento cliente con campi validi | "Cliente registrato correttamente" |
| 2      | Cliente con dati mancanti            | "Dati cliente incompleti"          |
| 3      | Durata abbonamento nulla o negativa  | "Durata abbonamento non valida"    |
| 4      | Codice fiscale già registrato        | "Codice fiscale già registrato"    |

---

##  Struttura di ogni test

Ogni test deve:

1. Leggere i campi da un file input/‘’.txt
2. Validare il numero e la correttezza dei campi (blocco\_valido)
3. Simulare l'inserimento del cliente (o l'errore)
4. Scrivere l'esito nel file .log tramite scrivi\_log()
5. Confrontare il file di log con il relativo oracolo tramite confronta\_oracolo()
6. Stampare l'esito con stampa*ok / stampa\_*fail

---

##  Funzione Core (opzionale)

Se i test condividono molto codice, puoi creare una funzione statica:

```c
static void esegui_test_cliente(
    int test_num,
    const char* input_path,
    const char* esito_path,
    const char* oracolo_path,
    const char* messaggio_successo,
    const char* messaggio_fallimento
);
```

La logica è identica a \`esegui\_*test\_*prenotazione()\`.

---

##   Funzione aggregata

Tutti i test devono essere invocati da una funzione aggregata:

```c
void avvia_test_clienti(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);
```

Questa funzione va richiamata dal main della suite di test (test\_main.c)

---

##  Checklist per ogni test

* Cliente valido
* Cliente con dati mancanti (dividi per elemento inserito)
* Cliente con durata abbonamento 0

---

##  Pulizia

Assicurati di:

* Liberare memoria allocata&#x20;
* Chiudere file aperti
* Gestire eventuali errori (file mancanti, campi nulli)

---

##  Conclusione

Segui questo schema per mantenere coerenza, riusabilità e leggibilità nella suite di test. Se hai dubbi, confronta con test\_prenotazioni.c che funge da modello di riferimento.

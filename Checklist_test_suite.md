#  Checklist Implementazione Completa - Suite di Testing PES_Project

---

##  Core Utilities (test_utils.c/h)

- [ ] Aggiungere funzione: `confronta_output(const char* file1, const char* file2);`
- [ ] Aggiungere funzione: `scrivi_log(const char* path, const char* messaggio);`
- [ ] Aggiungere funzione: `stampa_ok(int test_num);`
- [ ] Aggiungere funzione: `stampa_fail(int test_num, const char* atteso, const char* ottenuto);`
- [ ] Aggiungere macro ANSI per output colorato (verde/rosso)
- [ ] Funzione: `riga_oracolo_presente(FILE* oracolo, int test_num);`
- [ ] Funzione: `valida_blocco_cliente(char** campi, int numero_campi);`
- [ ] Eventuali funzioni analoghe per prenotazioni e report

---

##  test_clienti.c

- [ ] Implementare test: cliente valido
- [ ] Implementare test: cliente con dati mancanti
- [ ] Implementare test: abbonamento con durata zero
- [ ] Validare input con `valida_blocco_cliente()`
- [ ] Gestione output con `scrivi_log()` e confronto con oracolo
- [ ] Stampa esito con colori in console

---

##  test_prenotazioni.c

- [ ] Test prenotazione con cliente registrato
- [ ] Test prenotazione con cliente non esistente
- [ ] Test prenotazione con lezione piena o orario sovrapposto
- [ ] Creare `valida_blocco_prenotazione(...)` se necessario

---

##  test_report.c

- [ ] Test generazione report corretto
- [ ] Test report con 0 clienti o lezioni
- [ ] Confronto file completo output vs oracolo (`confronta_file_completo()`)
- [ ] Eventuale `valida_blocco_report(...)`

---

##  test_runner.c

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
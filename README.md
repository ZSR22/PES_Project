# SGP – Sistema di Gestione Palestra

## Descrizione

Il progetto **SGP** è un'applicazione sviluppata in linguaggio C per la gestione informatizzata di una palestra. Il sistema consente di:
- Registrare e gestire clienti e abbonamenti
- Gestire le prenotazioni alle lezioni
- Generare report mensili delle attività svolte (output in formato JSON)

L'interfaccia è interamente a riga di comando (CLI) ed è pensata per l'utilizzo in piccoli/medi contesti gestionali.

---

## Informazioni Autori

**Gianmarco Raimondi**  
**Salvatore Zurino**  
Corso di Laurea in Informatica  
Università degli Studi di Salerno  
Corso: *Programmazione e Strutture Dati*  
Data: Giugno 2025

---

## Struttura del Repository

Il progetto è suddiviso su due branch distinti:

- **`main`**: contiene il codice di produzione. I file sorgenti sono collocati direttamente nella root del progetto.
- **`test`**: ospita la suite automatizzata di test unitari, organizzata per moduli e corredata da file di input, oracolo e log.

Entrambi i branch includono un Makefile specifico:

| Branch  | Obiettivo             | Eseguibile | Comando Make       |
|---------|-----------------------|------------|--------------------|
| `main`  | Applicazione reale    | `SGP`      | `make`, `make run` |
| `test`  | Testing automatizzato | `SGP_TEST` | `make test`        |

---

## Compilazione ed Esecuzione

### Produzione

```bash
make        # Compila tutti i sorgenti
make run    # Compila ed esegue l'applicazione CLI
```

### Testing

```bash
make test   # Compila ed esegue la suite di test
make clean  # Pulisce eseguibili, oggetti e log
```

---

## Testing e Validazione

La suite di test verifica tre macro-componenti:

1. **Gestione Clienti**
   - Inserimento, validazione, duplicati
2. **Prenotazioni**
   - Correttezza dati, clienti inesistenti, orari e disponibilità
3. **Report**
   - Generazione mensile, struttura JSON, coerenza dati

Ogni test salva un log in `esiti/` e confronta l'output con l’oracolo corrispondente.

---

## Obiettivi Didattici

Il progetto ha lo scopo di applicare i concetti fondamentali di:

- Gestione dinamica della memoria in C
- Strutture dati complesse (liste, alberi binari di ricerca)
- Modularità e suddivisione del codice
- Testing automatizzato con confronto su oracolo

## Funzionalità Implementate

-  Registrazione clienti e abbonamenti
-  Verifica validità abbonamenti
-  Prenotazione lezioni (con controllo lezioni piene e doppie prenotazioni)
-  Generazione report mensile in formato JSON
-  Suite di test automatizzata per ogni modulo

---

## Licenza e Destinazione d'Uso

Progetto sviluppato a scopo didattico nell’ambito del corso universitario *Programmazione e Strutture Dati*.  
**Non destinato alla distribuzione o all’utilizzo in produzione.**
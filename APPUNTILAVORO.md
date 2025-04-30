# Gestione Abbonamenti – Progetto Palestra

## Struttura Cliente
- ID
- Nome
- Cognome
- Durata (giorni)
- Timestamp attivazione

## Funzionalità da implementare
- Inserimento cliente 
- Verifica validità abbonamento
- Stampa ordinata clienti

## ADT scelto: Albero binario(tabella hash) per clienti DA RIVEDERE
- inserimento e ricerca
- Necessario per accessi rapidi via ID


## Gestione prenotazioni ADT scelto: Lista
- implementare tramite lista un calendario
- la ricerca si farà prima per orario poi per id

## Struttura Prenotazione
- unsigned int ID
-  char nome_lezione
-  char nome_partecipante
-  char cognome_partecipante
-  char ora

## Struttura Lezione
- unsigned char ID
- char nome
- char num_max_partecipanti
- char orario


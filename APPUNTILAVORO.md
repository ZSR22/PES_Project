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


## Gestione prenotazioni ADT scelto: Lista Concatenata
- implementare tramite lista un calendario
- la ricerca si farà prima per orario poi per id



## Struttura Prenotazione
- unsigned int ID
-  Lezione lezione
-  char nome_partecipante
-  char cognome_partecipante
  
## Gestione Lezioni Disponibili ADT scelto: Array statico(Catalogo_Lezioni) contenente strutture Lezione(Disposto a cambiamenti)
  
  Gestione di un catalogo di lezioni, relative funzioni di creazione del catalogo, inserimento lezione, eliminazione catalogo ed eliminazione lezione, e ricerca lezione
  
## Struttura Lezione
- unsigned int ID
- char nome
- int num_max_partecipanti
- time_t orario

## Struttura Catalogo_Lezioni
- Lezione lezione[MAX_LEZIONI]
- int numero_lezioni

## Interfaccia Utente

Va approfondita, scelta, progettata e implementata una interfaccia grafica adeguata per la visualizzazione dei dati e l'interazione con l'utente.


 1. Interfaccia a Linea di Comando (CLI)

 Vantaggi:
	•	Semplice da implementare con scanf, printf, e menu testuali.
	•	Portabilità: funziona su qualsiasi terminale senza necessità di librerie esterne.
	•	Prestazioni elevate: minimo uso di risorse.
	•	Ottima per debugging e sviluppo rapido.

 Svantaggi:
	•	Poco intuitiva per utenti non tecnici.
	•	Nessuna componente visiva (grafici, calendari).
	•	Poco scalabile se il progetto cresce.


 2. Interfaccia Grafica con GTK (GIMP Toolkit)

 Vantaggi:
	•	Nativa per Linux, ma compatibile anche con Windows e macOS.
	•	Interfaccia moderna con finestre, pulsanti, tabelle, ecc.
	•	Adatta se vuoi costruire un’app standalone con un look professionale.
	•	Libreria C, quindi facile da integrare nel tuo attuale progetto in C.

 Svantaggi:
	•	Richiede tempo e curva di apprendimento.
	•	Aggiunge dipendenze e necessita di setup (es. installazione GTK).
	•	Debug più complesso rispetto alla CLI.

Inoltre il Makefile per la versione CLI è più semplice rispetto a una con GTK, poiché GTK ha delle dipendenze esterne. Per quanto riguarda la compilazione: CLI make compila e crea un eseguibile; riguardo GTK devi avere GTK installato e usare pkg-config per ottenere le configurazioni corrette. Eventualmente va scritto uno script di installazione delle dipendenze.



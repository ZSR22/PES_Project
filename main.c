/*
=====================================================
    File: main.c
    Descrizione: Punto d'ingresso del programma SGP, gestisce l'interfaccia principale e l'avvio del sistema
    Autore: Gianmarco Raimondi && Salvatore Zurino
    Data: 21/05/2025
    Versione: 1.0
=====================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <console/Main_Console.h>
#include <gui/Gui_Home.h>
#include "abbonamenti.h"
#include "Lezioni.h"
#include "Lista_Prenotazioni.h"
#include "Persistenza_Dati.h"


/*
  ALL'AVVIO:
   - Controllare esistenza di file JSON (lezioni.json, prenotazioni.json)
   - Se esistono: caricare i dati e popolare le strutture dati
   - Se non esistono: crearli vuoti
 
  DURANTE L'ESECUZIONE:
     - Ogni modifica alle strutture dati deve aggiornare il file JSON corrispondente

*/



/*

Funzione principale del programma che gestisce l'interazione con l'utente e le operazioni di gestione della palestra


@param nessuno

Pre: nessuna

@result gestisce l'interazione con l'utente, le operazioni di inserimento, ricerca, prenotazione e visualizzazione dei clienti, lezioni e prenotazioni

*/
int main(int argc, char* argv[]){
  
  NodoAlbero* radice = NULL;
  Catalogo_Lezioni* catalogo = NULL;
  Lista_Prenotazioni *lista = crea_lista_prenotazioni();

  if(!file_vuoto(PATH_FILE_ABBONAMENTI)){
    carica_abbonamenti_da_file(PATH_FILE_ABBONAMENTI, &radice);
  }

  if(!file_vuoto(PATH_FILE_LEZIONI)){
    catalogo = carica_catalogo_da_file(PATH_FILE_LEZIONI);
  }

  if(!file_vuoto(PATH_FILE_PRENOTAZIONI)){
    carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, lista);
  }

  if(argc > 1 && strcmp(argv[1], "--console") == 0){
    avvia_console(radice, catalogo, lista);
  }
  else if(argc > 1 && strcmp(argv[1], "--gui") == 0){
    avvia_gui();
  } else {
    fprintf(stderr, "Modalità di visualizzazione sconosciuta!\n");
    return -1;
  }

}
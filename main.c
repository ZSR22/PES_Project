#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abbonamenti.h"
#include "Prenotazione.h"

#define MAX_PRENOTAZIONI 100

Nodo* radice = NULL;
Prenotazione prenotazioni[MAX_PRENOTAZIONI];
int num_prenotazioni = 0;

void menu(){
  printf("\n==== GESTIONE PALESTRA ====\n");
  printf("1. Inserisci cliente\n");
  printf("2. Visualizza clienti (ordinati)\n");
  printf("3. Verifica validità abbonamento\n");
  printf("4. Inserisci prenotazione\n");
  printf("5. Visualizza la lista delle prenotazioni\n");
  printf("0. Esci\n");
  printf("===========================\n");
  printf("Scegli un'opzione: ");
}

int main(){
  Nodo* radice = NULL;
  int scelta;
  char codice_fiscale[17];
  Cliente c;

  do{
    menu();
    scanf("%d", &scelta);
    getchar(); //serve a pulire il buffer

    switch (scelta)
    {
      case 1:
        printf("Inserisci nome: ");
        fgets(c.nome, sizeof(c.nome), stdin);
        c.nome[strcspn(c.nome,"\n")] = '\0';
        
        printf("Inserisci cognome: ");
        fgets(c.cognome, sizeof(c.cognome), stdin);
        c.cognome[strcspn(c.cognome, "\n")] = '\0';

        printf("Inserisci codice fiscale: ");
        fgets(c.codice_fiscale, sizeof(c.codice_fiscale), stdin);
        c.codice_fiscale[strcspn(c.codice_fiscale, "\n")] = '\0';      

        printf("Inserisci durata abbonamento (in giorni): ");
        scanf("%d", &c.durata);

        c.data_inizio = time(NULL); // data attuale

        radice = inserisci_cliente(radice, c);
        
        break;
      case 2:
        stampa_clienti_ordinati(radice);
        break;

      case 3:
        printf("Inserisci codice fiscale da cercare:");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        Nodo* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
        if (nodo_trovato != NULL) {
          Cliente* trovato = &(nodo_trovato->cliente);
          printf("Cliente trovato: %s %s\n", trovato->nome, trovato->cognome);
          printf("Abbonamento valido: %s\n", abbonamento_valido(*trovato) ? "SI" : "NO");
        } else {
          printf("Cliente non trovato.\n");
        }
        break;

      case 4:
        printf("Funzione prenotazione.\n");
        break;

      case 5:
        printf("Funzione visualizzazione prenotazioni non ancora implementata.\n");
        break;

      case 0:
        printf("Uscita in corso...\n");
        libera_clienti(radice);
        break;

      default:
        printf("Scelta non valida. Riprova.\n");
      }

    } while (scelta != 0);
    return 0;
}
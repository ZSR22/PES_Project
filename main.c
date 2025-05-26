#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abbonamenti.h"
#include "Prenotazione.h"
#include "Persistenza_Dati.h"


/*
 * ALL'AVVIO:
 * - Controllare esistenza di file JSON (lezioni.json, prenotazioni.json)
 * - Se esistono: caricare i dati e popolare le strutture dati
 * - Se non esistono: crearli vuoti
 *
 * DURANTE L'ESECUZIONE:
 * - Ogni modifica alle strutture dati deve aggiornare il file JSON corrispondente
 */


void menu(){
  printf("\n==== GESTIONE PALESTRA ====\n");
  printf("1. Inserisci cliente\n");
  printf("2. Visualizza clienti (ordinati)\n");
  printf("3. Verifica validità abbonamento\n");
  printf("4. Inserisci prenotazione\n");
  printf("5. Visualizza la lista delle prenotazioni\n");
  printf("6. Inserisci lezione\n");
  printf("7. Visualizza lezioni disponibili\n");
  printf("0. Esci\n");
  printf("===========================\n");
  printf("Scegli un'opzione: ");
}
    
int main(){
  
  NodoAlbero* radice = NULL;
  int scelta;
  char codice_fiscale[17];
  Catalogo_Lezioni catalogo;
  Lista_Prenotazioni* lista = crea_lista_prenotazioni();

  if(!file_vuoto(PATH_FILE_ABBONAMENTI)){
    carica_abbonamenti_da_file(PATH_FILE_ABBONAMENTI, radice);
  }

  if(!file_vuoto(PATH_FILE_LEZIONI)){
    catalogo = carica_catalogo_da_file(PATH_FILE_LEZIONI);
  }

  if(!file_vuoto(PATH_FILE_PRENOTAZIONI)){
    carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, lista);
  }

  do{
    menu();
    scanf("%d", &scelta);
    getchar(); 
    
    switch (scelta)
    {
      
      
      case 1:{
        Cliente c;
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
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        radice = inserisci_cliente(radice, c);

        bool cliente_salvato_su_file = salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
        if(cliente_salvato_su_file){
          printf("Cliente salvato su file.\n");
        } else{
          printf("Errore salvataggio su file.\n");
        }
        
        break;
      }
      
      
      
      
      case 2:{
        stampa_clienti_ordinati(radice);
        break;
      }
      
      
      
      
      case 3:{
        printf("Inserisci codice fiscale da cercare:");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
        if (nodo_trovato != NULL) {
          Cliente* trovato = &(nodo_trovato->cliente);
          printf("Cliente trovato: %s %s\n", trovato->nome, trovato->cognome);
          printf("Abbonamento valido: %s\n", abbonamento_valido(*trovato) ? "SI" : "NO");
        } else {
          printf("Cliente non trovato.\n");
        }
        break;

      } 
      
      
      
      case 4:{
        
        printf("Inserisci codice fiscale: ");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* cliente_trovato = ricerca_cliente(radice, codice_fiscale);
        if (cliente_trovato == NULL) {
          printf("Cliente non trovato.\n");
          break;
        }
        if (!abbonamento_valido(cliente_trovato->cliente)) {
          printf("Abbonamento non valido.\n");
          break;
        }
        
        mostra_lezioni(catalogo);

        unsigned int id_inserito;
        printf("Inserisci id lezione: ");
        scanf("%u", &id_inserito);
        getchar();

        Lezione* lezione_trovata = trova_lezione(&catalogo, id_inserito);
        if(lezione_trovata == NULL){
          printf("Lezione non trovata.\n");
          break;
        }

        Prenotazione nuova_prenotazione;
        nuova_prenotazione.ID = genera_id_univoco(PATH_FILE_PRENOTAZIONI);
        nuova_prenotazione.lezione = *lezione_trovata;
        nuova_prenotazione.partecipante = cliente_trovato->cliente;
        nuova_prenotazione.lezione = *lezione_trovata;

        aggiungi_prenotazione(lista, nuova_prenotazione);

        bool prenotazione_salvata_su_file = salva_prenotazioni_su_file(lista, PATH_FILE_PRENOTAZIONI);
        if(prenotazione_salvata_su_file){
          printf("Prenotazione salvata su file\n");
        } else{
          printf("Errore salvataggio su file.\n");
        }
        break;

      }
      
      
      
      
      case 5:{
        visualizza_prenotazioni(lista);
        break;

      }
      
      
      
      
      case 6:{
        Lezione nuova_lezione;
        char nome[MAX_NOME];
        int giorno, mese, anno , ora, minuto; 
        
        nuova_lezione.ID = genera_id_univoco(PATH_FILE_LEZIONI);
        
        printf("Inserisci il nome della lezione: ");
        fgets(nuova_lezione.nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = '\0';
        strncpy(nuova_lezione.nome, nome, MAX_NOME);

        printf("Inserisci il numero massimo di posti: ");
        scanf("%d", &nuova_lezione.max_posti);
        getchar();

        printf("Inserisci data e ora (gg mm aaaa hh mm): ");
        scanf("%d %d %d %d %d", &giorno, &mese, &anno, &ora, &minuto);
        getchar();

        Orario_Tm tm_orario;
        nuova_lezione.data = converti_orario_in_time_t(&tm_orario, giorno, mese, anno, ora, minuto);
        if(conflitto_orario_lezione(&catalogo, nuova_lezione.data)){
          printf("Esiste già una lezione a questo orario\n");
          break;
        }

        aggiungi_lezione(&catalogo, nuova_lezione);

        bool lezione_salvata_su_file = salva_lezioni_su_file(&catalogo, PATH_FILE_LEZIONI);
        if(lezione_salvata_su_file){
          printf("Lezione salvata su file\n");
        } else{
          printf("Errore salvataggio su file.\n");
        }
      
      
        break; 
      
      }
      
      
      
      
      
      case 7:{
        mostra_lezioni(catalogo);
        break;

      }
      
      
      
      
      
      case 0:{
        printf("Uscita in corso...\n");
        libera_clienti(radice);
        libera_lista_prenotazioni(lista);
        elimina_catalogo(&catalogo);
        break;

      }
      
      
      
      
      default:{
        printf("Scelta non valida. Riprova.\n");
      }

    } 
  } while (scelta != 0);

  return 0;


}
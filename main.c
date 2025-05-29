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

/*

Stampa a video il menu principale dell'applicazione


@param nessuna

Pre: nessuna

@result mostrerà su terminale il menu principale dell'applicazione

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
  printf("8. Elimina Cliente\n");
  printf("9. Elimina Prenotazione\n");
  printf("10. Elimina lezione\n");
  printf("11. Visualizza report mensile\n");
  printf("0. Esci\n");
  printf("===========================\n");
  printf("Scegli un'opzione: ");
}

/*

Pulisce l'input del buffer per evitare problemi con fgets dopo scanf


@param nessuno

Pre: nessuna

@result rimuove eventuali caratteri residui nel buffer di input

*/
void pulisci_input(){
    
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

}
/*

Attende l'input dell'utente per continuare l'esecuzione del programma


@param nessuno

Pre: nessuna

@result attende che l'utente prema INVIO per continuare
*/
void attendi_utente(){
  
  
  printf("\nPremi INVIO per continuare...");
  fflush(stdout);
  getchar();
  
  
}

/*

Funzione principale del programma che gestisce l'interazione con l'utente e le operazioni di gestione della palestra


@param nessuno

Pre: nessuna

@result gestisce l'interazione con l'utente, le operazioni di inserimento, ricerca, prenotazione e visualizzazione dei clienti, lezioni e prenotazioni

*/
int main(){
  
  NodoAlbero* radice = NULL;
  int scelta;
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

  do{
    menu();
    scanf("%d", &scelta);
    pulisci_input(); 
    
    switch (scelta){
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
        pulisci_input();

        printf("Inserisci data di nascita formato gg/mm/anno esempio -> 16/07/2001: ");
        fgets(c.data_nascita, sizeof(c.data_nascita), stdin);
        c.data_nascita[strcspn(c.data_nascita, "\n")] = '\0';

        pulisci_input();
        c.data_inizio = time(NULL);
        c.id_abbonamento = genera_id_univoco(PATH_FILE_ABBONAMENTI);

        NodoAlbero* nodo_valido = inserisci_cliente(radice, c);

        if(nodo_valido != NULL){
          radice = nodo_valido;

          bool cliente_salvato_su_file = salva_abbonamenti_su_file(radice, PATH_FILE_ABBONAMENTI);
          if(cliente_salvato_su_file){
  
            printf("Cliente salvato su file.\n");
            printf("===========================\n");
            attendi_utente();
            break;

          } else{
            printf("Errore salvataggio su file.\n");
            attendi_utente();
            break;
          }
        }

        attendi_utente();
        break;
      }
      
      
      
      
      case 2:{
        if(radice == NULL){
          
          fprintf(stderr, "\n");
          fprintf(stderr, "Nessun cliente trovato\n");
        } else{ 
          printf("===========================\n");
          printf("\n");
          stampa_clienti_ordinati(radice);
          printf("===========================\n");
          }
        
        attendi_utente();
        break;

      }
      
      
      
      
      case 3:{
        
        char codice_fiscale[MAX_CF];
        printf("Inserisci codice fiscale da cercare:");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';


        NodoAlbero* nodo_trovato = ricerca_cliente(radice, codice_fiscale);
        if (nodo_trovato != NULL) {
          Cliente* trovato = &(nodo_trovato->cliente);
          printf("===========================\n");
          printf("\n");
          printf("Cliente trovato: %s %s\n", trovato->nome, trovato->cognome);
          printf("Abbonamento valido: %s\n", abbonamento_valido(*trovato) ? "SI" : "NO");
        } else {
          printf("===========================\n");
          printf("\n");
          printf("Cliente non trovato.\n");
        }
        attendi_utente();
        break;

      } 
      
      
      
      case 4:{
        
        char codice_fiscale[MAX_CF];
        printf("Inserisci codice fiscale: ");
        fgets(codice_fiscale, MAX_CF, stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* cliente_trovato = ricerca_cliente(radice, codice_fiscale);
        if (cliente_trovato == NULL) {
          
          printf("\n");
          fprintf(stderr, "Cliente non trovato.\n");
          attendi_utente();
          break;

        }
        if (!abbonamento_valido(cliente_trovato->cliente)) {
          
          printf("\n");
          printf("Abbonamento non valido.\n");
          attendi_utente();
          break;

        }
        
        printf("\n");

        printf("Cliente trovato: %s %s", cliente_trovato->cliente.nome, cliente_trovato->cliente.cognome);
        printf("\n");
        printf("===========================\n");

        mostra_lezioni(*catalogo);

        unsigned int id_inserito;
        printf("\n");
        printf("Inserisci id lezione: ");
        scanf("%u", &id_inserito);
        pulisci_input();


        if(catalogo == NULL){
          printf("catalogo vuoto\n");
          attendi_utente();
          break;
        }

        Lezione* lezione_trovata = trova_lezione(catalogo, id_inserito);

        if(lezione_trovata == NULL){

          fprintf(stderr, "Lezione non trovata\n");

          attendi_utente();
          break;
        }
        

        Prenotazione nuova_prenotazione;
        nuova_prenotazione.ID = genera_id_univoco(PATH_FILE_PRENOTAZIONI);
        nuova_prenotazione.lezione = *lezione_trovata;
        nuova_prenotazione.partecipante = cliente_trovato->cliente;

        bool prenotazione_aggiunta = aggiungi_prenotazione(lista, nuova_prenotazione);

        if(prenotazione_aggiunta){

          lezione_trovata->max_posti--;
          bool prenotazione_salvata_su_file = salva_prenotazioni_su_file(*lista, PATH_FILE_PRENOTAZIONI);
          bool lezione_aggiornata = salva_lezioni_su_file(catalogo, PATH_FILE_LEZIONI);
          if(prenotazione_salvata_su_file && lezione_aggiornata){
            printf("\n");
            printf("Prenotazione salvata su file e lezione aggiornata\n");
          } else{
            printf("Errore salvataggio su file.\n");
          }
          
          

        }
        

        attendi_utente();
        break;

      }
      
      
      
      
      case 5:{
        
        printf("===========================\n");
        visualizza_prenotazioni(lista);
        attendi_utente();
        break;

      }
      
      
      
      
      case 6:{
        
        Lezione nuova_lezione;
        int giorno, mese, anno , ora, minuto; 
        
        nuova_lezione.ID = genera_id_univoco(PATH_FILE_LEZIONI);
        
        printf("Inserisci il nome della lezione: ");
        fgets(nuova_lezione.nome, MAX_NOME, stdin);
        nuova_lezione.nome[strcspn(nuova_lezione.nome, "\n")] = '\0';      

        printf("Inserisci il numero massimo di posti: ");
        scanf("%d", &nuova_lezione.max_posti);
        pulisci_input();

        printf("Inserisci data e ora (gg mm aaaa hh mm): ");
        scanf("%d %d %d %d %d", &giorno, &mese, &anno, &ora, &minuto);
        pulisci_input();

        Orario_Tm tm_orario;
        nuova_lezione.data = converti_orario_in_time_t(&tm_orario, giorno, mese, anno, ora, minuto);
        
        printf("\n");
        if(conflitto_orario_lezione(catalogo, nuova_lezione.data)){
          
          printf("\n");
          printf("Esiste già una lezione a questo orario\n");
          attendi_utente();
          break;
        }

        aggiungi_lezione(catalogo, nuova_lezione);

        bool lezione_salvata_su_file = salva_lezioni_su_file(catalogo, PATH_FILE_LEZIONI);
        if(lezione_salvata_su_file){
          printf("Lezione salvata con successo\n");
        } else{
          printf("Errore salvataggio su file.\n");
        }
      
        attendi_utente();
        break; 
      
      }
      
      
      
      
      
      case 7:{
        
        printf("\n");
        printf("===========================\n");
        mostra_lezioni(*catalogo);
        attendi_utente();
        break;

      }
      
      
      case 8: {
        
        char codice_fiscale[MAX_CF];

        printf("Inserisci il codice fiscale del cliente da eliminare: ");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* nodo_cliente_trovato = ricerca_cliente(radice, codice_fiscale);
        

        if(nodo_cliente_trovato != NULL){

          if(cliente_prenotato(*lista, nodo_cliente_trovato->cliente)){
            printf("Non puoi eliminare un cliente con prenotazione attiva\n");
            attendi_utente();
            break;
          }
          unsigned int id_cliente = nodo_cliente_trovato->cliente.id_abbonamento;
          radice = elimina_cliente(nodo_cliente_trovato, codice_fiscale);
          printf("Cliente eliminato\n");
          elimina_cliente_da_persistenza(id_cliente);
          
          
        } else{
          
          printf("Cliente non presente a sistema\n");
          
          
        }

        attendi_utente();
        break;
      }
      
      
      case 9: {
        
        char codice_fiscale[MAX_CF];
        unsigned int id_lezione;

        printf("Inserisci il codice fiscale del cliente: ");
        fgets(codice_fiscale, sizeof(codice_fiscale), stdin);
        codice_fiscale[strcspn(codice_fiscale, "\n")] = '\0';

        NodoAlbero* nodo_cliente_trovato = ricerca_cliente(radice, codice_fiscale);
        if (nodo_cliente_trovato == NULL) {
            printf("Cliente con codice fiscale %s non trovato.\n", codice_fiscale);
            attendi_utente();
            break;
        }
        
        printf("Inserisci l'ID della lezione prenotata: ");
        scanf("%u", &id_lezione);
        pulisci_input();

        Lezione* lezione_trovata = trova_lezione(catalogo, id_lezione);
        if(lezione_trovata == NULL){
          printf("Lezione con id: %u non presente a sistema\n", id_lezione);
          attendi_utente();
          break;
        }

        Prenotazione* prenotazione_trovata = trova_prenotazione(*lista, *lezione_trovata, nodo_cliente_trovato->cliente);

        if(prenotazione_trovata != NULL){
          
          unsigned int id_prenotazione_trovato = prenotazione_trovata->ID;
          bool prenotazione_eliminata = disdici_prenotazione(lista, lezione_trovata);
          
          
          if(prenotazione_eliminata){
            
            lezione_trovata->max_posti++;
            bool lezione_aggiornata = salva_lezioni_su_file(catalogo, PATH_FILE_LEZIONI);
            if(lezione_aggiornata){

              elimina_prenotazione_da_persistenza(id_prenotazione_trovato);
              printf("Prenotazione eliminata dalla persistenza\n");

            }
            
            
          } else{
            
            printf("Errore di eliminazione prenotazione\n");

          }
          

        }else{
          
          printf("Prenotazione non presente a sistema\n");

        }
        
        attendi_utente();
        break;

      }

      case 10: {
        
        int id_lezione;

        printf("Inserisci l'ID della lezione da eliminare: ");
        scanf("%d", &id_lezione);
        pulisci_input();

        Lezione* lezione_trovata = trova_lezione(catalogo, id_lezione);
        if (lezione_trovata != NULL) {
            
          unsigned int id_lezione_trovato = lezione_trovata->ID;

          
          if(lezione_prenotata(*lista, *lezione_trovata)){
            
            printf("La lezione ha dei partecipanti prenotati\n");
            attendi_utente();
            break;
          }
          elimina_lezione(catalogo, *lezione_trovata);
          printf("\n");
          elimina_lezione_da_persistenza(id_lezione_trovato);
          printf("\n");
          printf("Lezione eliminata con successo.\n");

        }else{
          
          printf("\n");
          printf("Lezione non trovata.\n");
        
        }

        attendi_utente();
        break;
        
      }
      case 11: {
               
        attendi_utente();
        break;
      }
      
      case 0:{
        
        printf("\n");
        printf("Arrivederci!\n");
        if (radice != NULL) libera_clienti(radice);
        if (lista != NULL) libera_lista_prenotazioni(lista);
        if (catalogo->lezione != NULL){ elimina_catalogo(catalogo);}
    
        attendi_utente();
        break;

      }
      
      
      default:{
        printf("Scelta non valida. Riprova.\n");
        attendi_utente();
      }

    } 
  } while (scelta != 0);

  return 0;


}
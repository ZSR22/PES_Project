#include <stdio.h>
#include "Prenotazione.h"
#include <time.h>

void visualizza_prenotazione(Prenotazione prenotazione){
    //Convertiamo time_t in una struttura con campi separati così da poterlo utilizzare nel formato italiano giorno/mese/anno ora:minuto
    struct tm* data = localtime(&prenotazione.lezione.data);
    printf("ID: %ud\n nome: %s\n Cognome: %s\n Lezione: %s\n Data e Ora: %02d/%02d/%04d--%02d:%02d\n", 
        prenotazione.ID, prenotazione.nome_partecipante, prenotazione.cognome_partecipante, prenotazione.lezione.nome, 
            data->tm_mday,
            data->tm_mon + 1,
            data->tm_year + 1900,
            data->tm_hour,
            data->tm_min);
}



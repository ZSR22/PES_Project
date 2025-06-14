/* 
=============================================================================
 File: Prenotazioni.c
 Descrizione: Implementazione per il controllo dell'item Prenotazione
 Autore: Gianmarco Raimondi
 Data: 06/05/2025
 Versione: 1.0
=============================================================================
*/
#include <time.h>
#include <stdio.h>
#include "Prenotazione.h"
/*

Stampa a video la prenotazione passata come parametro


@param Prenotazione prenotazione

Pre: prenotazione != NULL

@result mostrerà su terminale ID, Nome, Cognome, Lezione, Data e Ora

*/
void visualizza_prenotazione(Prenotazione prenotazione){
    
    //Convertire time_t in una struttura Tm è necessaria se si vuole visualizzare l'orario nel formato italiano ->  giorno/mese/anno ora:minuto
    Orario_Tm* data = converti_orario_in_struct_tm(prenotazione.lezione.data);
    
    printf("\nID: %u\n nome: %s\n Cognome: %s\n Lezione: %s\n Data e Ora: %02d/%02d/%04d--%02d:%02d\n", 
        prenotazione.ID, prenotazione.partecipante.nome, prenotazione.partecipante.cognome, prenotazione.lezione.nome, 
            data->tm_mday,
            data->tm_mon,
            data->tm_year,
            data->tm_hour,
            data->tm_min);
    
    printf("======================================");        
}



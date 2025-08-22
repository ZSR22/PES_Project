/* 
=============================================================================
 File: Descrittore.c
 Descrizione: Definizione delle variabili globali dei descrittori
 Autore: Gianmarco Raimondi
 Data: 22/08/2025
 Versione: 1.0
=============================================================================
*/
#include "Descrittore.h"
#include "Persistenza_Dati.h"

const Descrittore descrittore_clienti = {PATH_FILE_ABBONAMENTI, ID_ABBONAMENTO_JSON};
const Descrittore descrittore_lezioni = {PATH_FILE_LEZIONI, ID_LEZIONE_JSON};
const Descrittore descrittore_prenotazioni = {PATH_FILE_PRENOTAZIONI, ID_PRENOTAZIONE_JSON};
/* 
=============================================================================
 File: Utilities.h
 Descrizione: Definizioni di strutture e prototipi per funzioni ad alta visibilità
 Autore: Gianmarco Raimondi
 Data:  14/05/2025
 Versione: 1.0
=============================================================================
*/
#ifndef UTILITIES_H
#define UTILITIES_H
#include <time.h>

typedef struct tm Orario_Tm;

Orario_Tm* converti_orario(time_t orario);

#endif
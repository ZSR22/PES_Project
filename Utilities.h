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

Orario_Tm* converti_orario_in_struct_tm(time_t orario);
time_t converti_orario_in_time_t(Orario_Tm* tm_orario, int giorno, int mese, int anno, int ora, int minuto);
unsigned int genera_id_univoco(const char* filepath);
bool file_vuoto(char* filepath);

#endif
/* 
=============================================================================
 File: test_utilities.h
 Descrizione: Interfaccia per le funzioni di controllo e stampa per casi di test
 Autore: Gianmarco Raimondi
 Data: 06/06/2025
 Versione: 1.0
=============================================================================
*/
#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include <stdbool.h>
#include <stdio.h>

#define TEST_RESET "\x1b[0m"
#define TEST_PASSATO "\x1b[32m"
#define TEST_FALLITO "\x1b[31m"


bool confronta_output(const char* file_output, const char* file_oracolo);
void scrivi_log(const char* path, const char* messaggio);
void stampa_ok(int test_num);
void stampa_fail(int test_num, const char* atteso, const char* ottenuto);
bool riga_oracolo_presente(FILE* oracolo, int test_num);
bool blocco_valido(char** campi, int numero_campi);
char* duplica_stringa(const char* stringa);


#endif
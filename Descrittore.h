/* 
=============================================================================
 File: Descrittore.h
 Descrizione: Interfaccia e dichiarazioni dei descrittori degli elementi in persistenza
 Autore: Gianmarco Raimondi
 Data: 22/08/2025
 Versione: 1.0
=============================================================================
*/
#ifndef DESCRITTORE_H
#define DESCRITTORE_H
// Struttura contenente le informazioni di descrizione di un elemento in persistenza
typedef struct {
    const char* path; // path del file di persistenza .json
    const char* id_elemento; // stringa identificativa dell'elemento denominata nel .json
} Descrittore;

extern const Descrittore descrittore_clienti;
extern const Descrittore descrittore_prenotazioni;
extern const Descrittore descrittore_lezioni;
#endif
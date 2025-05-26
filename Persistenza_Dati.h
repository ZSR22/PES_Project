/* 
=============================================================================
 File: Persistenza_Dati.h
 Descrizione: Interfaccia per il salvataggio e caricamento dati persistenti
 Autore: Gianmarco Raimondi
 Data: 21/05/2025
 Versione: 1.0
=============================================================================
*/
#ifndef PERSISTENZA_DATI_H
#define PERSISTENZA_DATI_H

#include <stdbool.h>
#include "Lista_Prenotazioni.h"
#include "Lezioni.h"
#include "abbonamenti.h"

#define PATH_FILE_LEZIONI "persistenza_dati/Lezioni.json"
#define PATH_FILE_PRENOTAZIONI "persistenza_dati/Prenotazioni.json"
#define PATH_FILE_ABBONAMENTI "persistenza_dati/Clienti.json"



Catalogo_Lezioni carica_catalogo_da_file(const char* filepath);
void carica_prenotazioni_da_file(const char* filepath, Lista_Prenotazioni* lista);
void carica_abbonamenti_da_file(const char* filepath, NodoAlbero** radice_BST);


bool salva_lezioni_su_file(const Catalogo_Lezioni* catalogo, const char* filepath);
bool salva_prenotazioni_su_file(const Lista_Prenotazioni lista, const char* filepath);
bool salva_abbonamenti_su_file(const NodoAlbero* nodo, const char* filepath);







#endif
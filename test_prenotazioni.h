/* 
=============================================================================
 File: test_prenotazioni.h
 Descrizione: Interfaccia per le funzioni di test eseguiti su registrazione di prenotazione
 Autore: Gianmarco Raimondi
 Data: 06/06/2025
 Versione: 1.0
=============================================================================
*/
#ifndef TEST_PRENOTAZIONI_H
#define TEST_PRENOTAZIONI_H

#include "header_sorgenti/Lista_Prenotazioni.h"

// Test 1 – Verifica prenotazione con dati corretti

// Test 2 – Verifica prenotazione con cliente inesistente

// Test 3 – Verifica prenotazione con lezione piena

// Test 4 – Verifica prenotazione con orari sovvrapposti

// Test 5 – Lezione con ID non valido

// Test 6 – Prenotazione già effettuata per la stessa lezione

// Test 7 – Codice fiscale malformato (es. stringa vuota o troppo corta)

// Test 8 – Prenotazione per una lezione con data già superata

//Richiamata nel main, funzione di comunicazione con l'esterno
void avvia_test_prenotazioni(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

#endif
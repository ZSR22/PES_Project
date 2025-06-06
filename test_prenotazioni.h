#ifndef TEST_PRENOTAZIONI_H
#define TEST_PRENOTAZIONI_H

#include "header_sorgenti/Lista_Prenotazioni.h"

// Test 1 – Verifica prenotazione con dati corretti
void test_prenotazione_cliente_registrato(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 2 – Verifica prenotazione con cliente inesistente
void test_prenotazione_cliente_inesistente(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 3 – Verifica prenotazione con lezione piena
void test_prenotazione_lezione_piena(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 4 – Verifica prenotazione con orari sovvrapposti
void test_prenotazione_orari_sovrapposti(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 5 – Lezione con ID non valido
void test_prenotazione_id_lezione_non_valido(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 6 – Prenotazione già effettuata per la stessa lezione
void test_prenotazione_duplicata(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 7 – Codice fiscale malformato (es. stringa vuota o troppo corta)
void test_prenotazione_codice_fiscale_malformato(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

// Test 8 – Prenotazione per una lezione con data già superata
void test_prenotazione_lezione_passata(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

void avvia_test_prenotazioni(Lista_Prenotazioni* lista, NodoAlbero* radice, Catalogo_Lezioni* catalogo);

#endif
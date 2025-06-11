/*
=============================================================================
// File: report.h
 Descrizione: Header per la generazione di report mensili e salvataggio su file
 Autore: Salvatore Zurino
 Data: 29/05/2025
 Versione: 1.0
=============================================================================
*/

#ifndef REPORT_H
#define REPORT_H

#include "Lista_Prenotazioni.h"

void genera_report_mensile(const Lista_Prenotazioni lista, const Catalogo_Lezioni* catalogo);

#endif 
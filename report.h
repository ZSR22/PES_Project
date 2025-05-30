/*
=============================================================================
// File: report.h
 Descrizione: Header per la generazione di report mensili e salvataggio su file
 Autore: Salvatore Zurino
 Data: 29/05/2025
 Versione: 1.0
=============================================================================
*/
#include <stddef.h>
#include "Prenotazione.h"
#ifndef REPORT_H
#define REPORT_H

void genera_report_mensile(const Prenotazione* prenotazioni, Catalogo_Lezioni* catalogo);

#endif 
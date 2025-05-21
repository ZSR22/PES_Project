/* 
=============================================================================
 File: Utilities.c
 Descrizione: Implementazioni di funzioni ad alta visibilità
 Autore: Gianmarco Raimondi
 Data:  14/05/2025
 Versione: 1.0
=============================================================================
*/
#include "Utilities.h"
/*

Converte una variabile da tipo time_t in una struttura Tm adatta alla visualizzazione a video

@param time_t orario

@return riporta un puntatore alla struttura Orario_Tm

*/
Orario_Tm* converti_orario(time_t orario){
    
    Orario_Tm* struttura_orario = localtime(&orario);
    struttura_orario->tm_mon + 1;
    struttura_orario->tm_year + 1900;
    return struttura_orario;
}
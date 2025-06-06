#include "test_prenotazioni.h"
#include "test_clienti.h"
#include "test_report.h"
#include "header_sorgenti/Persistenza_Dati.h"

/*

  Punto di ingresso della suite di test per il progetto SGP.

  - Inizializza tutte le strutture dati condivise: - Albero dei clienti - Catalogo delle lezioni - Lista delle prenotazioni

  - Avvia in sequenza:
    - Test sull'area clienti
    - Test sulle prenotazioni
    - Test sui report

  - Al termine, libera tutta la memoria utilizzata

  @return 0 se l’esecuzione è terminata correttamente

*/
int main(void) {
    printf("\n== AVVIO SUITE DI TEST ==\n");

    Lista_Prenotazioni *lista = crea_lista_prenotazioni();
    NodoAlbero* radice = NULL;
    Catalogo_Lezioni *catalogo = carica_catalogo_da_file(PATH_FILE_LEZIONI);

    carica_prenotazioni_da_file(PATH_FILE_PRENOTAZIONI, lista);
   carica_abbonamenti_da_file(PATH_FILE_ABBONAMENTI, &radice);
    avvia_test_prenotazioni(lista, radice, catalogo);
    

    libera_lista_prenotazioni(lista);
    elimina_catalogo(catalogo);
    libera_clienti(radice);

    return 0;
}
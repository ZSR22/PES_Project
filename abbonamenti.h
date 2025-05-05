//abbonamenti.h

typedef struct Cliente {} Cliente;
typedef struct nodo {} Nodo;

Nodo* inserisci_cliente();
Cliente* cerca_cliente();
int abbonamento_valido();
void stampa_clienti_ordinati();
void libera_clienti();

#ifndef LEZIONI_H
#define LEZIONI_H
#include <time.h>

#define MAX_NOME 50
#define MAX_LEZIONI 100
typedef struct{
    unsigned int ID;
    char nome[MAX_NOME];
    int max_posti;
    time_t data;
} Lezione;

typedef struct{
    Lezione lezione[MAX_LEZIONI];
    int numero_lezioni;
} Catalogo_Lezioni;

void inizializza_catalogo(Catalogo_Lezioni* catalogo);
void aggiungi_lezione(Catalogo_Lezioni* catalogo, Lezione nuova_lezione);
void mostra_lezioni(const Catalogo_Lezioni* catalogo);
const Lezione* trova_lezione(const Catalogo_Lezioni* catalogo, const unsigned int id, const char* nome);
#endif
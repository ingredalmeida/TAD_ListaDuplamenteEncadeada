#include "TAD_Processo.h"

typedef struct celula{
    Processo *item;
    int prox, ante;
}Celula;

typedef struct lista{
    int primeiro, ultimo;
    int qtd_celulas_livres;
    int primeira_celula_livre;
    Celula **vetor;
}Lista;


void incializa_lista(Lista **lista, int N);

void celulas_livres(Celula **celula, int N);

void insere_lista(Lista **lista, Processo *item, int N);

void retira_primeiro_item(Lista **lista);

void imprime_vetor(Lista *lista);

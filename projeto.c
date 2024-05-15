#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"

struct elemento {
    struct carta dados;
    struct elemento *proximo;
};

struct head {
    struct elemento *primeiro;
    struct elemento *ultimo;
};

typedef struct elemento Elemento;

Lista *criarLista () {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    *lista = NULL;
    return lista;
}

int quantidade (Lista *lista) {
    if (lista == NULL) return 0;
    int qtd = 0;
    Elemento *aux = *lista;
    while (aux != NULL) {
        qtd++;
        aux = aux->proximo;
    }
    return qtd;
}

int inserirOrdenado (Lista *lista, struct carta novosdados) {
    if (lista == NULL) return 0;
    Elemento *novo = (Elemento *) malloc (sizeof(Elemento));
    if (novo == NULL) return 0;
    novo->dados = novosdados;
    if ((*lista) == NULL || novo->dados.numero < (*lista)->dados.numero) {
        novo->proximo = *lista;
        *lista = novo;
    } else {
        Elemento *aux = *lista;
        Elemento *ant = NULL;
        while (aux != NULL && novo->dados.numero > aux->dados.numero) {
            ant = aux;
            aux = aux->proximo;
        }
        if (aux == NULL) {
            ant->proximo = novo;
            novo->proximo = NULL;
        } else {
            novo->proximo = aux;
            ant->proximo = novo;
        }
    }
    return 1;
}

int acessarIndice (Lista *lista, int indice, struct carta *retorno) {
    if (lista == NULL) return 0;
    if ((*lista) == NULL) return 0;
    if (indice < 0 || indice >= quantidade(lista)) return 0;
    Elemento *aux = *lista;
    for (int i = 0; i<indice; i++) {
        aux = aux->proximo;
    }
    *retorno = aux->dados;
    return 1;
}

int removerIndice (Lista *lista, int indice) {
    if (lista == NULL) return 0;
    if ((*lista) == NULL) return 0;
    if (indice < 0 || indice >= quantidade(lista)) return 0;
    Elemento *aux = *lista;
    Elemento *ant = NULL;
    if (indice == 0) {
        *lista = aux->proximo;
        free(aux);
    } else {
        for (int i = 0; i<indice; i++) {
            ant = aux;
            aux = aux->proximo;
        }
        ant->proximo = aux->proximo;
        free(aux);
    }
    return 1;
}

int exibirLista (Lista *lista) {
    if (lista == NULL) return 0;
    if ((*lista) == NULL) return 0;
    Elemento *aux = *lista;
    Elemento *aux2 = *lista;
    do{
        while(aux != NULL){
            printf("  +------+\t");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf("  |      |\t");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf("  | %3d  |\t", aux->dados.numero);
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf("  |      |\t");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf("  +------+\t");
            aux = aux->proximo;
        }
        printf("\n");
    }while(aux != NULL);

    return 1;
}

int destruirLista (Lista *lista, int modo) {
    if (lista == NULL) return 0;
    if (quantidade(lista) == 0) return 0;
    int tamanho = quantidade(lista);
    for (int i = 0; i<tamanho; i++) {
        removerIndice(lista, 0);
    }
    if (modo == 1) {
        free(*lista);
        free(lista);
    }
    return 1;
}

//---------------------------------------------------------------------------

Pilha *criarPilha () {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    *pilha = NULL;
    return pilha;
}

int inserirPilha (Pilha *pilha, struct carta novosdados) {
    if (pilha == NULL) return 0;
    Elemento *novo = (Elemento *) malloc(sizeof(Elemento));
    if (novo == NULL) return 0;
    novo->dados = novosdados;
    novo->proximo = *pilha;
    *pilha = novo;
    return 1;
}

int removerPilha (Pilha *pilha, struct carta *retorno) {
    if (pilha == NULL) return 0;
    if (tamanhoPilha(pilha) == 0) return 0;
    Elemento *aux = *pilha;
    *retorno = (*pilha)->dados;
    *pilha = (*pilha)->proximo;
    free(aux);
    return 1;
}

void embaralhar (Pilha *pilha) {
    srand(time(NULL));
    int aleatorios[tamanhoPilha(pilha)];

    int igual;
    for (int i = 0; i<tamanhoPilha(pilha); i++) {
        do {
            aleatorios[i] = rand() % tamanhoPilha(pilha);
            igual = 0;
            for (int j = 0; j<i; j++) {
                if (aleatorios[i] == aleatorios[j]) {
                    igual = 1;
                }
            }
        } while (igual == 1);
    }

    struct carta suporte[tamanhoPilha(pilha)];

    int tamanho = tamanhoPilha(pilha);
    for (int i = 0; i<tamanho; i++) {
        removerPilha(pilha, &suporte[aleatorios[i]]);
    }
    for (int i = 0; i<tamanho; i++) {
        inserirPilha(pilha, suporte[i]);
    }
}

int tamanhoPilha (Pilha *pilha) {
    if (pilha == NULL) return 0;
    int qtd = 0;
    Elemento *aux = *pilha;
    while (aux != NULL) {
        qtd++;
        aux = aux->proximo;
    }
    return qtd;
}

int destruirPilha (Pilha *pilha, int modo) {
    if (pilha == NULL) return 0;
    if (tamanhoPilha(pilha) == 0) return 0;
    struct carta suporte;
    int tamanho = tamanhoPilha(pilha);
    for (int i = 0; i<tamanho; i++) {
        removerPilha(pilha, &suporte);
    }
    if (modo == 1) {
        free(*pilha);
        free(pilha);
    }
    return 1;
}

//---------------------------------------------------------------------------


Fila *criarFila () {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    return fila;
}

int inserirFila (Fila *fila, struct carta novosdados) {
    if (fila == NULL) return 0;
    Elemento *novo = (Elemento *) malloc(sizeof(Elemento));
    if (novo == NULL) return 0;
    novo->dados = novosdados;
    novo->proximo = NULL;
    if (tamanhoFila(fila) == 0) {
        fila->primeiro = novo;
        fila->ultimo = novo;
    } else {
        (fila->ultimo)->proximo = novo;
        fila->ultimo = novo;
    }
    return 1;
}

int removerFila (Fila *fila, struct carta *retorno) {
    if (fila == NULL) return 0;
    if (tamanhoFila(fila) == 0) return 0;
    *retorno = (fila->primeiro)->dados;
    Elemento *aux = fila->primeiro;
    fila->primeiro = (fila->primeiro)->proximo;
    free(aux);
    if (tamanhoFila(fila) == 1) {
        fila->ultimo = fila->primeiro;
    }
    return 1;
}

int acessarFila (Fila *fila, struct carta *retorno) {
    if (fila == NULL) return 0;
    if (tamanhoFila(fila) == 0) return 0;
    *retorno = (fila->ultimo)->dados;
    return 1;
}

int exibirFila (Fila *fila) {
    if (fila == NULL) return 0;
    if (tamanhoFila(fila) == 0) return 0;
    Elemento *aux = fila->primeiro;
    Elemento *aux2 = fila->primeiro;

    do{
        while(aux != NULL){
            printf(" +------+  ");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" |      |  ");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" | %3d  | ->", aux->dados.numero);
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" |      |  ");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" +------+  ");
            aux = aux->proximo;
        }
        printf("\n");
    }while(aux != NULL);

    return 1;
}

int tamanhoFila (Fila *fila) {
    if (fila == NULL) return 0;
    int qtd = 0;
    Elemento *aux = fila->primeiro;
    while (aux != NULL) {
        qtd++;
        aux = aux->proximo;
    }
    return qtd;
}

int destruirFila (Fila *fila, int modo) {
    if (fila == NULL) return 0;
    if (tamanhoFila(fila) == 0) return 0;
    struct carta suporte;
    int tamanho = tamanhoFila(fila);
    for (int i = 0; i<tamanho; i++) {
        removerFila(fila, &suporte);
    }
    if (modo == 1) {
        free(fila->primeiro);
        free(fila->ultimo);
        free(fila);
    }
    return 1;
}

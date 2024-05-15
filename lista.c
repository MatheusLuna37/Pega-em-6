#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"
#include "lista.h"

struct elemento {
    struct carta dados;
    struct elemento *proximo;
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
            printf(" +------+ ");
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            if(aux->dados.numero % 10 == 0){
                printf(" |");
                paint(3);
                printf("*  * *");
                reset();
                printf("| ");
            }
            else if(aux->dados.numero == 55){
                printf(" |");
                paint(1);
                printf("* ** *");
                reset();
                printf("| ");
            }
            else if(aux->dados.numero % 5 == 0){
                printf(" |");
                paint(4);
                printf("*    *");
                reset();
                printf("| ");
            }
            else if(aux->dados.numero % 11 == 0){
                printf(" |");
                paint(2);
                printf("*  * *");
                reset();
                printf("| ");
            }
            else{
                printf(" |   *  | ");
            }
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" | %3d  | ", aux->dados.numero);
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            if(aux->dados.numero == 55){
                printf(" |");
                paint(1);
                printf("*  * *");
                reset();
                printf("| ");
            }
            else if(aux->dados.numero % 11 == 0){
                printf(" |");
                paint(2);
                printf("*    *");
                reset();
                printf("| ");
            }
            else{
                printf(" |      | ");
            }
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" +------+ ");
            aux = aux->proximo;
        }
        printf("\n");
    }while(aux != NULL);

    return 1;
}

int destruirLista (Lista *lista, int modo) {
    if (lista == NULL) return 0;
    if (quantidade(lista) != 0) {
        int tamanho = quantidade(lista);
        for (int i = 0; i<tamanho; i++) {
            removerIndice(lista, 0);
        }
    }
    if (modo == 1) {
        free(lista);
    }
    return 1;
}

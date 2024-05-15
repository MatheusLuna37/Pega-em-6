#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"
#include "fila.h"

struct elemento {
    struct carta dados;
    struct elemento *proximo;
};

struct head {
    struct elemento *primeiro;
    struct elemento *ultimo;
};

typedef struct elemento Elemento;

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
            printf(" +------+   ");
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
                printf("|   ");
            }
            else if(aux->dados.numero == 55){
                printf(" |");
                paint(1);
                printf("* ** *");
                reset();
                printf("|   ");
            }
            else if(aux->dados.numero % 5 == 0){
                printf(" |");
                paint(4);
                printf("*    *");
                reset();
                printf("|   ");
            }

            else if(aux->dados.numero % 11 == 0){
                printf(" |");
                paint(2);
                printf("*  * *");
                reset();
                printf("|   ");
            }
            else{
                printf(" |   *  |   ");
            }
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
            if(aux->dados.numero == 55){
                printf(" |");
                paint(1);
                printf("*  * *");
                reset();
                printf("|   ");
            }
            else if(aux->dados.numero % 11 == 0){
                printf(" |");
                paint(2);
                printf("*    *");
                reset();
                printf("|   ");
            }
            else{
                printf(" |      |   ");
            }
            aux = aux->proximo;
        }
        printf("\n");
        aux = aux2;

        while(aux != NULL){
            printf(" +------+   ");
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
    if (tamanhoFila(fila) != 0) {
        struct carta suporte;
        int tamanho = tamanhoFila(fila);
        for (int i = 0; i<tamanho; i++) {
            removerFila(fila, &suporte);
        }
    }
    if (modo == 1) {
        free(fila);
    }
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projeto.h"
#include "pilha.h"

struct elemento {
    struct carta dados;
    struct elemento *proximo;
};

typedef struct elemento Elemento;

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
    if (tamanhoPilha(pilha) != 0) {
        struct carta suporte;
        int tamanho = tamanhoPilha(pilha);
        for (int i = 0; i<tamanho; i++) {
            removerPilha(pilha, &suporte);
        }
    }
    if (modo == 1) {
        free(pilha);
    }
    return 1;
}

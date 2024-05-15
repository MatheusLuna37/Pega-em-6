#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>
#include <unistd.h>
#include "functions.h"

int main(void) {
    config();

    Pilha *Baralho = criarPilha();                                                  // cria o baralho
    Lista *Mao = criarLista();                                                      // cria a mão
    Fila **Mesa = (Fila **) malloc(tamMesa*sizeof(Fila *));                               // cria a mesa e as listas
    for (int i = 0; i<tamMesa; i++) {
        Mesa[i] = criarFila();
    }

    int qtd_jogadores;
    int limite;

    inicializarMenu(&qtd_jogadores, &limite);

    struct aluno *Adversarios = defineAdversarios(qtd_jogadores);

    Lista **Colecoes = (Lista **) malloc(qtd_jogadores*sizeof(Lista *));            // cria as coleções e suas listas
    for (int i = 0; i<qtd_jogadores; i++) {
        Colecoes[i] = criarLista();
    }

    int fim = 0;
    int momento = 0;

    while (fim == 0) {
        if (momento % tamMao == 0) {                                                    // quando se está em rodadas múltiplas de 10, deve-se renovar a mesa e as mãos
            Sleep(1000);
            paint(1);
            printf(" Nova rodada iniciando...\n\n");                                 // embaralha e distribui as cartas
            reset();
            inicializarBaralho(Baralho);
            inicializarMesa(Mesa, Baralho);
            inicializarMao(Mao, Baralho);
            if (momento == 0) mostrarSituacao(Mesa, Colecoes, Mao, qtd_jogadores, 1, Adversarios);
            else mostrarSituacao(Mesa, Colecoes, Mao, qtd_jogadores, 0, Adversarios);
        }
        for (int i = 0; i<qtd_jogadores; i++) {                                     // verifica se alguém ultrapassou a pontuação limite
            if (pontuacao(Colecoes[i]) >= limite) fim = 1;
        }
        int min = limite;                                                           // determina o valor da menor pontuação dentre os jogadores
        if (fim == 1) {
            for (int i = 0; i<qtd_jogadores; i++) {
                if (pontuacao(Colecoes[i]) < min) {
                    min = pontuacao(Colecoes[i]);
                }
            }
            if (pontuacao(Colecoes[0]) == min) {
                clearScreen();
                Sleep(500);                                    // se a sua pontuação for a menor, você venceu
                mostrarVitoria();
            } else {
                clearScreen();
                Sleep(500);
                mostrarDerrota();
            }
            mostrarRanking(Colecoes, Adversarios, qtd_jogadores);
        } else {
            rodarTurno(Mao, Baralho, Mesa, Colecoes, qtd_jogadores, Adversarios);
            momento++;
        }
    }

    aniquilar(Baralho, Mao, Mesa, Colecoes, Adversarios, qtd_jogadores);

    return 0;
}

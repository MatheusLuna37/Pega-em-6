#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include "projeto.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include <windows.h>
#include <mmsystem.h>
#include <unistd.h>

const int tamMesa = 4;
const int tamMao = 10;
const int tamBaralho = 104;

struct aluno {
        char nome[20];
};
struct jogador_pontos {
        int jogador;
        int pontos;
    };

HANDLE wHnd;
HANDLE rHnd;

void red() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
}

void green() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
}

void yellow() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
}

void cyan() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
}

void reset() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}

void paint(int n){
    switch (n){
        case 1:
            red();
            break;
        case 2:
            green();
            break;
        case 3:
            yellow();
            break;
        case 4:
            cyan();
            break;
    }
}

void inicializarMesa (Fila **Mesa, Pilha *Baralho) {
    for (int i = 0; i<tamMesa; i++) {
        if (destruirFila(Mesa[i], 0));                                                          // reseta as filas da mesa
    }
    struct carta carta_da_mesa;
    for (int i = 0; i<tamMesa; i++) {                                                                 // distribui uma carta em cada fila da mesa
        removerPilha(Baralho, &carta_da_mesa);
        inserirFila(Mesa[i], carta_da_mesa);
    }
}

void inicializarBaralho (Pilha *Baralho) {
    if(destruirPilha(Baralho, 0));                                                              // reseta o baralho
    struct carta suporte;
    for (int i = 1; i <= tamBaralho; i++) {                                                            // define os números das cartas e respectivas quantidades de bois
        suporte.numero = i;
        if (i % 55 == 0) {
            suporte.bois = 7;
        } else if (i % 11 == 0) {
            suporte.bois = 5;
        } else if (i % 10 == 0) {
            suporte.bois = 3;
        } else if (i % 5 == 0) {
            suporte.bois = 2;
        } else {
            suporte.bois = 1;
        }
        suporte.jogador = 0;
        inserirPilha(Baralho, suporte);                                                         // adiciona cada carta no baralho
    }
    embaralhar(Baralho);
}

void playSong() {
    PlaySound("Sounds\\SFX\\blipSelect.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void configSong(int *musica) {
    Sleep(200);
    playSong();
    printf("   0 - DESATIVAR A MÚSICA.\n");
    Sleep(200);
    playSong();
    printf("   1 - MANTER A MÚSICA.\n");
    Sleep(200);
    playSong();
    printf("  Escolha uma das opções: ");
    scanf("%d", &musica);

    if(musica == 0){
        mciSendString("stop MUSIC", NULL, 0, NULL);
    }

    if((musica != 0) && (musica != 1)){
        do{
            paint(1);
            printf("\n  Digite uma opção válida!\n  -> ");
            scanf("%d", &musica);
            reset();
        }while((musica != 0) && (musica != 1));
    }
}

void options() {
    int escolha, voltar;

    do {
        printf("\n");
        Sleep(200);
        playSong();
        printf("   1 - JOGAR;\n");
        Sleep(200);
        playSong();
        printf("   2 - REGRAS;\n");
        Sleep(200);
        playSong();
        printf("   3 - CRÉDITOS.\n");
        Sleep(200);
        printf("  Escolha uma das opções: ");
        scanf("%d", &escolha);

        if (escolha == 1){
            paint(1);
            printf("\n  Opção Selecionada: Jogar\n\n");
            reset();
            Sleep(500);
        }
        else if (escolha == 2){
            paint(1);
            printf("\n  Opção Selecionada: Regras\n\n");
            reset();
            Sleep(1000);
            clearScreen();

            mostrarRegras();

            do{
                paint(1);
                printf("  Digite 0 para sair das regras e voltar para as opções: ");
                reset();
                fflush(stdin);
                scanf("%d", &voltar);
                } while (voltar != 0);
                printf("\n");
        }
        else if (escolha == 3){
            paint(1);
            printf("\n  Opção Selecionada: Créditos\n\n");
            reset();
            Sleep(1000);
            clearScreen();

            mostrarCreditos();

            do{
                paint(1);
                printf("  Digite 0 para sair dos créditos e voltar para as opções: ");
                reset();
                fflush(stdin);
                scanf("%d", &voltar);
            } while (voltar != 0);
            printf("\n");
        }
        else{
            paint(1);
            printf("\n  Digite uma opção válida!\n\n");
            reset();
        }
        Sleep(500);
        clearScreen();
        mostrarArte2();
    } while (escolha != 1);
}

struct aluno *defineAdversarios(int qtd_jogadores) {
    struct aluno *adversarios = (struct aluno *) malloc((qtd_jogadores-1)*sizeof(struct aluno));
    int aleatorios[qtd_jogadores-1];
    struct aluno Alex;
    struct aluno Andre;
    struct aluno Antonio;
    struct aluno ArthurL;
    struct aluno ArthurR;
    struct aluno Hudson;
    struct aluno Erick;
    struct aluno Guido;
    struct aluno Guilherme;
    struct aluno Henrique;
    struct aluno JV;
    struct aluno Luana;
    struct aluno MatheusBL;
    struct aluno Nerton;
    struct aluno Vitoria;
    struct aluno Roberto;
    strcpy(Alex.nome, "Alex");
    strcpy(Andre.nome, "Andre");
    strcpy(Antonio.nome, "Antonio");
    strcpy(ArthurL.nome, "Arthur L");
    strcpy(ArthurR.nome, "Arthur R");
    strcpy(Hudson.nome, "Hudson");
    strcpy(Erick.nome, "Erick");
    strcpy(Guido.nome, "Guido");
    strcpy(Guilherme.nome, "Guilherme");
    strcpy(Henrique.nome, "Henrique");
    strcpy(JV.nome, "JV");
    strcpy(Luana.nome, "Luana");
    strcpy(MatheusBL.nome, "Matheus BL");
    strcpy(Nerton.nome, "Nerton");
    strcpy(Vitoria.nome, "Vitoria");
    strcpy(Roberto.nome, "Roberto");
    struct aluno players[16] = {
        Alex,
        Andre,
        Antonio,
        ArthurL,
        ArthurR,
        Hudson,
        Erick,
        Guido,
        Guilherme,
        Henrique,
        JV,
        Luana,
        MatheusBL,
        Nerton,
        Vitoria,
        Roberto
    };

    srand(time(NULL));
    int igual;
    for (int i = 0; i<(qtd_jogadores-1); i++) {
        do {
            aleatorios[i] = rand() % 16;
            igual = 0;
            for (int j = 0; j<i; j++) {
                if (aleatorios[i] == aleatorios[j]) {
                    igual = 1;
                }
            }
        } while (igual == 1);
    }
    for (int i = 0; i<(qtd_jogadores-1); i++) {
        adversarios[i] = players[aleatorios[i]];
    }
    return adversarios;
}

void configGame (int *qtd_jogadores, int *limite) {
    paint(1);
    Sleep(200);
    printf("  Configurações de Jogo:\n\n");
    reset();
    printf("  Contra quantos bots deseja jogar? (de 1 a 9)\n  -> ");
    playSong();
    scanf("%d", qtd_jogadores);
    while (getchar() != '\n');
    while (*qtd_jogadores < 1 || *qtd_jogadores > 9) {
        paint(1);
        printf(" Quantidade inválida, digite novamente -> ");
        reset();
        scanf("%d", qtd_jogadores);
        while(getchar() != '\n');
    }
    printf("\n");
    (*qtd_jogadores)++;

    playSong();
    printf("  Que limite de pontuação será usado?\n  -> ");
    scanf("%d", limite);
    while (getchar() != '\n');
    while (*limite < 1) {
        paint(1);
        printf(" Limite inválido, digite novamente -> ");
        reset();
        scanf("%d", limite);
        while(getchar() != '\n');
    }
    printf("\n");
    clearScreen();
}

void inicializarMenu (int *qtd_jogadores, int *limite) {
    // menu inicial e pergunta ao jogador a quantidade de bots e limite de pontuação
    int musica;

    mciSendString("open Sounds\\SFX\\music.wav alias MUSIC", NULL, 0, NULL);
    mciSendString("play MUSIC", NULL, 0, NULL);
    mostrarArte1();
    Sleep(200);
    mostrarArte2();

    configSong(&musica);
    options();
    configGame(qtd_jogadores, limite);

    if(musica == 1){
        mciSendString("stop MUSIC", NULL, 0, NULL);
        mciSendString("open Sounds\\SFX\\music2.wav alias MUSIC2", NULL, 0, NULL);
        mciSendString("play MUSIC2", NULL, 0, NULL);
    }
}

void inicializarMao (Lista *Mao, Pilha *Baralho) {
    // mesma ideia dos outros inicializar
    if (destruirLista(Mao, 0));
    struct carta carta_da_mao;
    for (int i = 0; i<tamMao; i++) {
        removerPilha(Baralho, &carta_da_mao);
        carta_da_mao.jogador = 1;                                                               // indica que a carta pertence ao jogador 1: você
        inserirOrdenado(Mao, carta_da_mao);
    }
}

int pontuacao(Lista *lista) {
    // conta a pontuação de uma dada coleção
    struct carta suporte;
    int pont = 0;
    for (int i = 0; i<quantidade(lista); i++) {
        acessarIndice(lista, i, &suporte);
        pont += suporte.bois;
    }
    return pont;
}

void mostrarMesaEPontos(Fila **Mesa, Lista **Colecoes, int qtd_jogadores, int estatico, struct aluno *Adversarios) {
    for (int i = 0; i<tamMesa; i++) {
        if (!estatico) Sleep(100);
        exibirFila(Mesa[i]);
        printf("\n");
    }
    printf("\n");
    if (!estatico) Sleep(500);
    char name[20];
    int name_len;
    char espaco1[20];
    char espaco2[20];
    printf(" Pontuações:\n");
    for (int i = 0; i<qtd_jogadores; i++) {
        if (!estatico) Sleep(100);
        if (i == 0) printf("   Você:     ");
        else {
            strcpy(name, "");
            strcat(name, Adversarios[i-1].nome);
            strcat(name, ":");
            strcpy(espaco1, "");
            for (int j = 0; j<((13-strlen(name))/2)-1; j++) {
                strcat(espaco1, " ");
            }
            strcpy(espaco2, "");
            for (int j = 0; j<13-strlen(name)-((13-strlen(name))/2)+1; j++) {
                strcat(espaco2, " ");
            }
            printf("%s%s%s", espaco1, name, espaco2);
        }
    }
    printf("\n");
    for (int i = 0; i<qtd_jogadores; i++) {
        if (!estatico) Sleep(100);
        printf("    %2d       ", pontuacao(Colecoes[i]));
    }
    printf("\n\n");
}

void mostrarSituacao (Fila **Mesa, Lista **Colecoes, Lista *Mao, int qtd_jogadores, int noInicio, struct aluno *Adversarios) {
    // exibe as cartas da mesa, das mãos e coleções
    int estatico = 0;
    if (!noInicio) {
        int mostrar = 0;
        int invalido;
        do {
            invalido = 1;
            estatico = 1;
            if (mostrar == 0) {
                invalido = 0;
                estatico = 0;
            }
            mostrarMesaEPontos(Mesa, Colecoes, qtd_jogadores, estatico, Adversarios);
            if (mostrar != 0) {
                for (int i = 0; i<qtd_jogadores+1; i++) {
                    if (mostrar == i+1) {
                        if (i == 0) printf(" Sua coleção:\n");
                        else printf(" Coleção de %s:\n", Adversarios[i-1].nome);
                        if(exibirLista(Colecoes[i]));
                        printf("\n");
                        invalido = 0;
                        break;
                    }
                }
            }
            if (invalido == 1) {
                paint(1);
                printf(" Jogador inválido, tente novamente.\n\n");
                reset();
            }
            Sleep(500);
            playSong();
            printf(" Deseja ver a coleção de qual jogador? (0 para pular)\n -> ");
            scanf("%d", &mostrar);
            while(getchar() != '\n');
            printf("\n");
            clearScreen();
        } while (mostrar != 0);
    }
    mostrarMesaEPontos(Mesa, Colecoes, qtd_jogadores, estatico, Adversarios);
    Sleep(500);
    printf(" Mão:\n");
    Sleep(250);
    if(exibirLista(Mao));
    for(int i = 0; i<quantidade(Mao); i++) {
        Sleep(75);
        printf("    (%d)   ", i+1);
    }
    printf("\n\n");
}

void pegaFila (Fila **Mesa, Lista **Colecoes, struct carta *carta_do_turno, int fila_alvo) {
    struct carta carta_da_mesa;
    int tamanho = tamanhoFila(Mesa[fila_alvo]);
    for (int j = 0; j<(tamanho-1); j++) {                                               // removo as cartas antes existentes na fila para a coleção do jogador
        removerFila(Mesa[fila_alvo], &carta_da_mesa);
        inserirOrdenado(Colecoes[carta_do_turno->jogador-1], carta_da_mesa);
    }
}

void escolheFila (Fila **Mesa, Lista **Colecoes, struct carta *carta_do_turno, int *fila_alvo) {
    // tento fazer uma jogada responsável para pegar a fila com menor quantidade de bois e menos cartas
    struct carta carta_da_mesa;
    int minDif = tamBaralho;
    int minCartas = 6;
    int minBois = 28;
    int tamanho;
    int qtdBois;
    Lista *conta_bois = criarLista();
    for (int j = 0; j<tamMesa; j++) {
        tamanho = tamanhoFila(Mesa[j]);
        qtdBois = 0;
        for (int k = 0; k < tamanho; k++) {                                             // removo da fila atual e coloco numa lista, para poder acesar por índices
            removerFila(Mesa[j], &carta_da_mesa);
            inserirOrdenado(conta_bois, carta_da_mesa);
            qtdBois += carta_da_mesa.bois;                                              // conto a quantidade de bois na fila
        }
        for (int k = 0; k < tamanho; k++) {                                             // retorno as cartas da lista para a fila
            acessarIndice(conta_bois, 0, &carta_da_mesa);
            removerIndice(conta_bois, 0);
            inserirFila(Mesa[j], carta_da_mesa);
        }
        if (qtdBois < minBois || (qtdBois == minBois && tamanho < minCartas)) {            // verifico se a quantidade é menor ou se é igual com menos cartas
            *fila_alvo = j;                                                                 // guardo o índice da fila de interesse
            minBois = qtdBois;
            minCartas = tamanho;
        }
    }
    inserirFila(Mesa[*fila_alvo], *carta_do_turno);                                          // insiro a carta da vez na fila menos ruim, o que a faz encher
    if (destruirLista(conta_bois, 1));
}

void fazJogada(Fila **Mesa, Lista **Colecoes, struct carta *carta_do_turno) {
    struct carta carta_da_mesa;
    int fila_alvo = -1;
    int minDif = tamBaralho;
    for (int j = 0; j<tamMesa; j++) {                                                             // percorre cada fila da mesa, em busca da que tem a carta mais próxima da carta da vez
        acessarFila(Mesa[j], &carta_da_mesa);
        if (((carta_do_turno->numero - carta_da_mesa.numero) > 0) && ((carta_do_turno->numero - carta_da_mesa.numero) < minDif)) {
            // verifica se a carta da vez é maior que a da fila e se a diferença é menor que as anteriores
            minDif = carta_do_turno->numero - carta_da_mesa.numero;
            fila_alvo = j;
        }
    }
    if (fila_alvo != -1) {                                                                     // verifica se houve a menos uma fila com número menor que a carta da vez
        inserirFila(Mesa[fila_alvo], *carta_do_turno);                                          // insere na fila correta a carta da vez
        if (tamanhoFila(Mesa[fila_alvo]) == 6) {
            pegaFila(Mesa, Colecoes, carta_do_turno, fila_alvo);
        }
    } else {
        escolheFila(Mesa, Colecoes, carta_do_turno, &fila_alvo);
        pegaFila(Mesa, Colecoes, carta_do_turno, fila_alvo);
    }
}

void rodarTurno (Lista *Mao, Pilha *Baralho, Fila **Mesa, Lista **Colecoes, int qtd_jogadores, struct aluno *Adversarios) {
    srand(time(NULL));
    Lista *Turno = criarLista();                                                                // vai guardar as cartas do turno
    struct carta carta_jogada;
    int qual_carta;
    Sleep(500);
    playSong();

    printf(" Escolha qual carta da sua mão jogar...\n -> ");
    scanf("%d", &qual_carta);
    while(getchar() != '\n');
    while (qual_carta < 1 || qual_carta > quantidade(Mao)) {                                    // verifica se a carta escolhida é válida
        paint(1);
        printf(" Carta inválida, digite novamente...\n");
        reset();
        printf(" -> ");
        scanf("%d", &qual_carta);
        while(getchar() != '\n');
    }
    qual_carta--;                                                                               // corrige o índice da carta, pois o jogador vê de 1 a 10

    clearScreen();

    acessarIndice(Mao, qual_carta, &carta_jogada);
    removerIndice(Mao, qual_carta);
    inserirOrdenado(Turno, carta_jogada);

    struct carta carta_alheia;
    for (int i = 2; i<=qtd_jogadores; i++) {                                                    // retira do baralho as cartas dos demais jogadores (aleatório)
        removerPilha(Baralho, &carta_alheia);
        carta_alheia.jogador = i;                                                               // indica de quem é a carta
        inserirOrdenado(Turno, carta_alheia);
    }

    struct carta carta_do_turno;
    struct carta carta_da_mesa;

    for (int i = 0; i<qtd_jogadores; i++) {                                                     // adiciona a carta da vez no devido lugar
        acessarIndice(Turno, i, &carta_do_turno);

        printf(" Cartas do Turno:\n");
        exibirLista(Turno);

        fazJogada(Mesa, Colecoes, &carta_do_turno);

        if(i < qtd_jogadores-1) {
            printf("\n Após o %d:\n\n", carta_do_turno.numero);                                      // exibo a situação da mesa após adicionar a carta da vez no lugar correto
            for (int j = 0; j<tamMesa; j++) {
                exibirFila(Mesa[j]);
                printf("\n");
            }
            Sleep(1500);
            clearScreen();
        } else {
            Sleep(500);
            printf("\n Situação após o %d e fim do turno:\n\n", carta_do_turno.numero);
            mostrarSituacao(Mesa, Colecoes, Mao, qtd_jogadores, 0, Adversarios);
        }
    }
    if(destruirLista(Turno, 1));
}

void aniquilar (Pilha *Baralho, Lista *Mao, Fila **Mesa, Lista **Colecoes, struct aluno *Adversarios, int qtd_jogadores) {
    if (destruirPilha(Baralho, 1));
    if (destruirLista(Mao, 1));
    for (int i = 0; i<tamMesa; i++) {
        if (destruirFila(Mesa[i], 1));
    }
    free(Mesa);
    for (int i = 0; i<qtd_jogadores; i++) {
        if(destruirLista(Colecoes[i], 1));
    }
    free(Colecoes);
    free(Adversarios);
}

void config(){
    setlocale(LC_ALL, "Portuguese");
    SetConsoleTitle("PEGA EM 6");

    HWND consoleWindow = GetConsoleWindow();

    ShowWindow(consoleWindow, SW_MAXIMIZE); // maximiza a janela do console

    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi; // remove as barras de rolagem
    GetConsoleScreenBufferInfo(wHnd, &csbi);
    COORD bufferSize = { (SHORT)csbi.dwSize.X, (SHORT)csbi.dwSize.Y };
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    SetConsoleMode(wHnd, ENABLE_EXTENDED_FLAGS); // configura o modo do console para desativar as barras de rolagem
}

void clearScreen() {
    system("cls");
}

void mostrarArte1(){
    Sleep(500);

    for (int i = 0; i <3; i++) {
        reset();
        printf("\n\t\t\t\t\t    ____  _____    _   _      ____  _____ __  __          __     _____ _   _ ____   ___  \n");
        printf("\t\t\t\t\t   / ___|| ____|  | | / \\    | __ )| ____|  \\/  |         \\ \\   / /_ _| \\ | |  _ \\ / _ \\ \n");
        printf("\t\t\t\t\t   \\___ \\|  _| _  | |/ _ \\   |  _ \\|  _| | |\\/| |  _____   \\ \\ / / | ||  \\| | | | | | | |\n");
        printf("\t\t\t\t\t    ___) | |__| |_| / ___ \\  | |_) | |___| |  | | |_____|   \\ V /  | || |\\  | |_| | |_| |\n");
        printf("\t\t\t\t\t   |____/|_____\\___/_/   \\_\\ |____/|_____|_|  |_|            \\_/  |___|_| \\_|____/ \\___/ \n\n\n");

        // Braço levantado
        printf("\t\t\t\t\t\t\t\t              =     ,         =.\n");
        printf("\t\t\t\t\t\t\t\t            /'/    )\\,/,/(_   \\ \\\n");
        printf("\t\t\t\t\t\t\t\t           |  (  ,\\\\)\\//\\)\\/\\_)  |\n");
        printf("\t\t\t\t\t\t\t\t           \\   `\\\\\\/\\\\/\\\\///'   /\n");
        printf("\t\t\t\t\t\t\t\t  ,\"-~`._ `\"--'_   `\"\"\"`  _ `\\'\"~-,_\n");
        printf("\t\t\t\t\t\t\t\t   \\       `-.  '_`.      .'_` \\ ,-\"~`/\n");
        printf("\t\t\t\t\t\t\t\t    `.__.-'`/   (-\\        /-) |-.__,'\n");
        printf("\t\t\t\t\t\t\t\t      ||   |     \\O)  /^\\ (O/  |\n");
        printf("\t\t\t\t\t\t\t\t       - \  |         /   `\\    /\n");
        printf("\t\t\t\t\t\t\t\t          \  \\       /      `\\ /\n");
        printf("\t\t\t\t\t\t\t\t            \ `-.  /' .---.--.\\\n");
        printf("\t\t\t\t\t\t\t\t              \`~(, '()      ('\n");
        printf("\t\t\t\t\t\t\t\t                 \\\\   _,.-.,_)\n");
        printf("\t\t\t\t\t\t\t\t                 \ `\\'`      /\n");
        printf("\t\t\t\t\t\t\t\t                    `\"\"\"\"~\"`\n");
        printf("\t\t\t\t\t\t\t\t                 \n");
        printf("\t\t\t\t\t\t\t\t                \n\n");
        printf("\t\t\t\t\t\t         _    ___    ____  _____ ____    _      _____ __  __    __   _ \n");
        printf("\t\t\t\t\t\t        / \\  / _ \\  |  _ \\| ____/ ___|  / \\    | ____|  \\/  |  / /_ | |\n");
        printf("\t\t\t\t\t\t       / _ \\| | | | | |_) |  _|| |  _  / _ \\   |  _| | |\\/| | | '_ \\| |\n");
        printf("\t\t\t\t\t\t      / ___ \\ |_| | |  __/| |__| |_| |/ ___ \\  | |___| |  | | | (_) |_|\n");
        printf("\t\t\t\t\t\t      \\/   \\_\\___/  |_|   |_____|____/_/   \\_\\ |_____|_|  |_|  \\___/(_)\n");
        reset();
        printf("\n\n\t\t\t\t\t\t\t\t\t\t Carregando");

        for(int i=0;i<3;i++){
            printf(".");
            Sleep(300);
        }

        fflush(stdout); // Limpa o buffer de saída

        clearScreen();
        paint(1);
        printf("\n\t\t\t\t\t    ____  _____    _   _      ____  _____ __  __          __     _____ _   _ ____   ___  \n");
        printf("\t\t\t\t\t   / ___|| ____|  | | / \\    | __ )| ____|  \\/  |         \\ \\   / /_ _| \\ | |  _ \\ / _ \\ \n");
        printf("\t\t\t\t\t   \\___ \\|  _| _  | |/ _ \\   |  _ \\|  _| | |\\/| |  _____   \\ \\ / / | ||  \\| | | | | | | |\n");
        printf("\t\t\t\t\t    ___) | |__| |_| / ___ \\  | |_) | |___| |  | | |_____|   \\ V /  | || |\\  | |_| | |_| |\n");
        printf("\t\t\t\t\t   |____/|_____\\___/_/   \\_\\ |____/|_____|_|  |_|            \\_/  |___|_| \\_|____/ \\___/ \n\n\n");

        // Braço abaixado
        printf("\t\t\t\t\t\t\t\t              =     ,         =.\n");
        printf("\t\t\t\t\t\t\t\t            /'/    )\\,/,/(_   \\ \\\n");
        printf("\t\t\t\t\t\t\t\t           |  (  ,\\\\)\\//\\)\\/\\_)  |\n");
        printf("\t\t\t\t\t\t\t\t           \\   `\\\\\\/\\\\/\\\\///'   /\n");
        printf("\t\t\t\t\t\t\t\t   ,\"-~`._ `\"--'_   `\"\"\"`  _ `\\'\"~-,_\n");
        printf("\t\t\t\t\t\t\t\t   \\       `-.  '_`.      .'_` \\ ,-\"~`/\n");
        printf("\t\t\t\t\t\t\t\t    `.__.-'`/   (-\\        /-) |-.__,'\n");
        printf("\t\t\t\t\t\t\t\t      ||   |    \\./)  /^\\ (\\./  |\n");
        printf("\t\t\t\t\t\t\t\t       - \\ |         /   `\\    /\n");
        printf("\t\t\t\t\t\t\t\t          \\ \\       /      `\\ /\n");
        printf("\t\t\t\t\t\t\t\t            \\ `-.  /' .---.--.\\\n");
        printf("\t\t\t\t\t\t\t\t              `\\~(, '()      ('\n");
        printf("\t\t\t\t\t\t\t\t                 \\   _,.-.,_)\n");
        printf("\t\t\t\t\t\t\t\t                 \\ `\\'`      /\n");
        printf("\t\t\t\t\t\t\t\t                    `\"\"\"\"~\"`\n");
        printf("\t\t\t\t\t\t\t\t                 \n");
        printf("\t\t\t\t\t\t\t\t                \n\n");
        printf("\t\t\t\t\t\t         _    ___    ____  _____ ____    _      _____ __  __    __   _ \n");
        printf("\t\t\t\t\t\t        / \\  / _ \\  |  _ \\| ____/ ___|  / \\    | ____|  \\/  |  / /_ | |\n");
        printf("\t\t\t\t\t\t       / _ \\| | | | | |_) |  _|| |  _  / _ \\   |  _| | |\\/| | | '_ \\| |\n");
        printf("\t\t\t\t\t\t      / ___ \\ |_| | |  __/| |__| |_| |/ ___ \\  | |___| |  | | | (_) |_|\n");
        printf("\t\t\t\t\t\t      \\/   \\_\\___/  |_|   |_____|____/_/   \\_\\ |_____|_|  |_|  \\___/(_)\n");
        reset();
        printf("\n\n\t\t\t\t\t\t\t\t\t\t Carregando");

        for(int i=0;i<3;i++){
            printf(".");
            Sleep(300);
        }
        fflush(stdout);
        clearScreen();
    }
}

void mostrarArte2(){
    Sleep(500);
    printf("\n\t\t\t\t\t\t\t    ____  _____ ____    _      _____ __  __    __   _ \n");
    printf("\t\t\t\t\t\t\t   |  _ \\| ____/ ___|  / \\    | ____|  \\/  |  / /_ | |\n");
    printf("\t\t\t\t\t\t\t   | |_) |  _|| |  _  / _ \\   |  _| | |\\/| | | '_ \\| |\n");
    printf("\t\t\t\t\t\t\t   |  __/| |__| |_| |/ ___ \\  | |___| |  | | | (_) |_|\n");
    printf("\t\t\t\t\t\t\t   |_|   |_____\\____/_/   \\_\\ |_____|_|  |_|  \\___/(_)\n\n");
    Sleep(500);
    printf("\t\t\t\t\t\t\t\t              =     ,         =.\n");
    printf("\t\t\t\t\t\t\t\t            /'/    )\\,/,/(_   \\ \\\n");
    printf("\t\t\t\t\t\t\t\t           |  (  ,\\\\)\\//\\)\\/\\_)  |\n");
    printf("\t\t\t\t\t\t\t\t           \\   `\\\\\\/\\\\/\\\\///'   /\n");
    printf("\t\t\t\t\t\t\t\t  ,\"-~`._ `\"--'_   `\"\"\"`  _ `\\'\"~-,_\n");
    Sleep(500);
    printf("\t\t\t\t\t\t\t\t   \\       `-.  '_`.      .'_` \\ ,-\"~`/\n");
    printf("\t\t\t\t\t\t\t\t    `.__.-'`/   (-\\        /-) |-.__,'\n");
    printf("\t\t\t\t\t\t\t\t      ||   |     \\O)  /^\\ (O/  |\n");
    printf("\t\t\t\t\t\t\t\t       - \  |         /   `\\    /\n");
    printf("\t\t\t\t\t\t\t\t          \  \\       /      `\\ /\n");
    Sleep(500);
    printf("\t\t\t\t\t\t\t\t            \ `-.  /' .---.--.\\\n");
    printf("\t\t\t\t\t\t\t\t              \`~(, '()      ('\n");
    printf("\t\t\t\t\t\t\t\t                 \\\\   _,.-.,_)\n");
    printf("\t\t\t\t\t\t\t\t                 \ `\\'`      /\n");
    printf("\t\t\t\t\t\t\t\t                    `\"\"\"\"~\"`\n");
    Sleep(500);
    printf("\t\t\t\t\t\t\t\t                 \n");
    printf("\t\t\t\t\t\t\t\t                \n\n\n");
    reset();
}

void mostrarCreditos(){
    paint(1);
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t/\n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t   ____ ____ ____ ___  . ___ ____ ____\n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t   |    |__/ |___ |  \\ |  |  |  | [__  \n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t   |___ |  \\ |___ |__/ |  |  |__| ___]\n\n");
    reset();
    Sleep(500);
    paint(1);
    printf("\t\t\t\t\t\t\t\t\t     Desenvolvedores:\n");
    reset();
    printf("\t\t\t\t\t\t\t      Antonio Nunes, José Vitor e Matheus Bezerra\n\n");
    Sleep(500);
    paint(1);
    printf("\t\t\t\t\t\t\t\t\t   Idealizador do jogo:\n");
    reset();
    printf("\t\t\t\t\t\t\t\t\t     Wolfgang Kramer\n\n");
    Sleep(500);
    paint(1);
    printf("\t\t\t\t\t\t\t\t\t   Professor-orientador:\n");
    reset();
    printf("\t\t\t\t\t\t\t\t\t     Roberto Pinheiro\n\n\n\n");
}

void mostrarRegras(){
    paint(1);
    printf("\n\n\n\n\n\n\n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t        ____ ____ ____ ____ ____ ____ \n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t        |__/ |___ | __ |__/ |__| [__  \n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t        |  \\ |___ |__] |  \\ |  | ___]\n\n");
    reset();
}

void mostrarVitoria(){
    paint(2);
    printf("\n\n\t\t\t\t\t\t\t\t              =     ,         =.\n");
    printf("\t\t\t\t\t\t\t\t            /'/    )\\,/,/(_   \\ \\\n");
    printf("\t\t\t\t\t\t\t\t           |  (  ,\\\\)\\//\\)\\/\\_)  |\n");
    printf("\t\t\t\t\t\t\t\t           \\   `\\\\\\/\\\\/\\\\///'   /\n");
    printf("\t\t\t\t\t\t\t\t  ,\"-~`._ `\"--'_   `\"\"\"`  _ `\\'\"~-,_\n");
    printf("\t\t\t\t\t\t\t\t   \\       `-.  '_`.      .'_` \\ ,-\"~`/\n");
    printf("\t\t\t\t\t\t\t\t    `.__.-'`/   (-\\        /-) |-.__,'\n");
    printf("\t\t\t\t\t\t\t\t      ||   |     \\O)  /^\\ (O/  |\n");
    printf("\t\t\t\t\t\t\t\t       - \  |         /   `\\    /\n");
    printf("\t\t\t\t\t\t\t\t          \  \\       /      `\\ /\n");
    printf("\t\t\t\t\t\t\t\t            \ `-.  /' .---.--.\\\n");
    printf("\t\t\t\t\t\t\t\t              \`~(, '()      ('\n");
    printf("\t\t\t\t\t\t\t\t                 \\\\   _,.-.,_)\n");
    printf("\t\t\t\t\t\t\t\t                 \ `\\'`      /\n");
    printf("\t\t\t\t\t\t\t\t                    `\"\"\"\"~\"`\n");
    printf("\t\t\t\t\t\t\t\t         / \\ \n");
    printf("\t\t\t\t\t\t\t\t        (_^_)\n");
    printf("\t\t\t\t\t\t    __     _____   ____ _____  __     _______ _   _  ____ _____ _   _ _ \n");
    printf("\t\t\t\t\t\t    \\ \\   / / _ \\ / ___| ____| \\ \\   / / ____| \\ | |/ ___| ____| | | | |\n");
    printf("\t\t\t\t\t\t     \\ \\ / / | | | |   |  _|    \\ \\ / /|  _| |  \\| | |   |  _| | | | | |\n");
    printf("\t\t\t\t\t\t      \\ V /| |_| | |___| |___    \\ V / | |___| |\\  | |___| |___| |_| |_|\n");
    printf("\t\t\t\t\t\t       \\_/  \\___/ \\____|_____|    \\_/  |_____|_| \\_|\\____|_____|\____/(_)\n\n\n");
}

void mostrarDerrota(){
    paint(1);
    printf("\n\n\t\t\t\t\t\t\t\t                =     ,         =.\n");
    printf("\t\t\t\t\t\t\t\t              /'/    )\\,/,/(_   \\ \\\n");
    printf("\t\t\t\t\t\t\t\t             |  (  ,\\\\)\\//\\)\\/\\_)  |\n");
    printf("\t\t\t\t\t\t\t\t             \\   `\\\\\\/\\\\/\\\\///'   /\n");
    printf("\t\t\t\t\t\t\t\t     ,\"-~`._ `\"--'_   `\"\"\"`  _ `\\'\"~-,_\n");
    printf("\t\t\t\t\t\t\t\t     \\       `-.  '_`.      .'_` \\ ,-\"~`/\n");
    printf("\t\t\t\t\t\t\t\t      `.__.-'`/   (-\\        /-) |-.__,'\n");
    printf("\t\t\t\t\t\t\t\t        ||   |    \\./)  /^\\ (\\./  |\n");
    printf("\t\t\t\t\t\t\t\t         - \\ |         /   `\\    /\n");
    printf("\t\t\t\t\t\t\t\t            \\ \\       /      `\\ /\n");
    printf("\t\t\t\t\t\t\t\t              \\ `-.  /' .---.--.\\\n");
    printf("\t\t\t\t\t\t\t\t                `\\~(, '()      ('\n");
    printf("\t\t\t\t\t\t\t\t                   \\   _,.-.,_)\n");
    printf("\t\t\t\t\t\t\t\t                   \\ `\\'`      /\n");
    printf("\t\t\t\t\t\t\t\t                      `\"\"\"\"~\"`\n");
    printf("\t\t\t\t\t\t\t\t         / \\ \n");
    printf("\t\t\t\t\t\t\t\t        (_^_)\n");
    printf("\t\t\t\t\t\t    __     _____   ____ _____   ____  _____ ____  ____  _____ _   _ _ \n");
    printf("\t\t\t\t\t\t    \\ \\   / / _ \\ / ___| ____| |  _ \\| ____|  _ \\|  _ \\| ____| | | | |\n");
    printf("\t\t\t\t\t\t     \\ \\ / / | | | |   |  _|   | |_) |  _| | |_) | | | |  _| | | | | |\n");
    printf("\t\t\t\t\t\t      \\ V /| |_| | |___| |___  |  __/| |___|  _ <| |_| | |___| |_| |_|\n");
    printf("\t\t\t\t\t\t       \\_/  \\___/ \\____|_____| |_|   |_____|_| \\_\\____/|_____|\____/(_)\n\n\n");
}

void trocar (struct jogador_pontos *p1, struct jogador_pontos *p2) {
    struct jogador_pontos aux;
    aux.jogador = p1->jogador;
    aux.pontos = p1->pontos;
    p1->jogador = p2->jogador;
    p1->pontos = p2->pontos;
    p2->jogador = aux.jogador;
    p2->pontos = aux.pontos;
}

void mostrarRanking(Lista **Colecoes, struct aluno *Adversarios, int qtd_jogadores) {
    struct jogador_pontos jogadores[qtd_jogadores];

    for (int i = 0; i<qtd_jogadores; i++) {
        jogadores[i].jogador = i;
        jogadores[i].pontos = pontuacao(Colecoes[i]);
    }
    for (int i = 0; i<qtd_jogadores; i++) {
        for (int j = i; j<qtd_jogadores; j++) {
            if (jogadores[i].pontos > jogadores[j].pontos) {
                trocar(&jogadores[i], &jogadores[j]);
            }
        }
    }
    paint(1);
    printf("\t\t\t\t\t\t\t\t        ____ ____ _  _ _  _ _ _  _ ____ \n") ;
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t        |__/ |__| |\\ | |_/  | |\\ | | __ \n");
    Sleep(250);
    printf("\t\t\t\t\t\t\t\t        |  \\ |  | | \\| | \\_ | | \\| |__] \n\n");
    reset();
    for (int i  = 0; i < qtd_jogadores; i++) {
        if (jogadores[i].jogador == 0) {
            paint(2);
            printf("\t\t\t\t\t\t\t\t           Você:      %14d\n", pontuacao(Colecoes[0]));
            reset();
        } else {
            char name[20];
            strcpy(name, Adversarios[jogadores[i].jogador-1].nome);
            char espaco[20];
            strcpy(espaco, "");
            for (int j  = 0; j < 10-strlen(name); j++) {
                strcat(espaco, " ");
            }
            printf("\t\t\t\t\t\t\t\t           %s:%s%14d\n", name, espaco, pontuacao(Colecoes[jogadores[i].jogador]));
        }
    }
    printf("\n\n");
}

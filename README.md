# 🃏 Jogo Pega em 6 (Português)

## Descrição
Este projeto, desenvolvido como parte da disciplina "Laboratório de Algoritmos e Estruturas de Dados" ministrada pelo Professor Roberto Pinheiro na Universidade Federal do Cariri, é uma réplica do jogo de cartas Pega em 6 implementado na linguagem C. Matheus ficou responsável principalmente pelo backend do projeto, enquanto José Vitor e Antonio se dedicaram majoritariamente a toda interação visual no terminal com o usuário/jogador, apesar de todos os desenvolvedores terem participado ativamente em cada etapa de desenvolvimento.

## Tecnologia

[![Tecnologia](https://skillicons.dev/icons?i=c)](https://skillicons.dev)

## Instalação
Ao fazer o download dos arquivos do repositório em uma mesma pasta, abra o arquivo .cbp na IDE CodeBlocks. Dentro do ambiente do CodeBlocks, siga settings > compiler > linker settings > add e adicione "winmm" para habilitar a música durante o jogo.

## 📜 [Regras do Pega em 6](https://pt.wikipedia.org/wiki/6_Nimmt!)
Pega em 6 é um jogo de cartas jogado com um baralho de 104 cartas. Para regras detalhadas você pode consultar [este link](https://pt.wikipedia.org/wiki/6_Nimmt!), mas segue em resumo o funcionamento do jogo:

- 2 ou mais jogadores.
- Cartas possuem determinadas quantidades de "cabeças de touro", sendo estas escores negativos.
- O objetivo é evitar pegar cartas com cabeças de touro (chifres) jogando cartas sequencialmente em quatro fileiras.
- Cada fileira tem um máximo de cinco cartas. Quando a sexta carta é adicionada, o jogador deve pegar todas as cartas nessa fileira, exceto a última.
- A cada turno, cada jogador escolhe uma carta de sua mão (inicialmente com 10 cartas) para adicionar às fileiras.
- As cartas são adicionadas em ordem crescente. Cada carta entra na fila em que o último número é menor que o da carta da vez e o mais próximo possível dele entre todas as quatro fileiras.
- O jogador com menos cabeças de touro no final do jogo vence.

## Funcionalidades
- Escolha entre jogar com ou sem música de fundo.
- Personalize o número de jogadores-bot participantes da partida.
- Escolha o limite de pontos para o jogo.
- Redistribuição das cartas quando as mãos dos jogadores estiverem vazias, desde que o limite de pontos não tenha sido atingido ainda.
- Alterne a visibilidade da coleção de cada jogador durante as rodadas.
- Seleção de nomes aleatórios da turma para associação com jogadores-bot.
- Exibição de ranking final mostrando as pontuações individuais.

## Créditos
**Desenvolvedores:**
</br>

[<img src="https://github.com/matheusluna37.png" width="60px;">](https://github.com/matheusluna37)
[<img src="https://github.com/josevitordds.png" width="60px;">](https://github.com/josevitordds)
[<img src="https://github.com/antonionunesdev.png" width="60px;">](https://github.com/antonionunesdev)
</br>

**Professor Proponente:** [Roberto Pinheiro](mailto:roberto.hugo@ufca.edu.br)  
**Instituição:** [Universidade Federal do Cariri](https://www.ufca.edu.br)

## Suporte/Contato
Para suporte, entre em contato com Matheus Bezerra em matheus.bezerra@aluno.ufca.edu.br

## Agradecimentos
Ao nosso professor Roberto pela ótima proposta de projeto, instigando maior entedimento do conteúdo trabalhado em sala de aula, e aos meus colegas de equipe pela dedicação em deixar o projeto o melhor possível.

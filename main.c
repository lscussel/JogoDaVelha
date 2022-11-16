/*
    Aluno: Leonardo Scussel
    Data.: 12/11/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define tam 3

int verificarSeAlguemGanhou(int tabuleiro[][tam])
{
    int ganhador, i, j;

    ganhador = 0;
    // verificar ganhador nas linhas
    if (ganhador == 0) {
        i = 0;
        while (i < tam && ganhador == 0) {
            if (tabuleiro[i][0] != 0) {
                if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
                    ganhador = tabuleiro[i][0];
                }
            }
            i++;
        }
    }

    // verificar ganhador nas colunas
    if (ganhador == 0) {
        j = 0;
        while (j < tam && ganhador == 0) {
            if (tabuleiro[0][j] != 0) {
                if (tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j]) {
                    ganhador = tabuleiro[0][j];
                }
            }
            j++;
        }
    }

    //verificar ganhador na diagonal principal
    if (ganhador == 0) {
        if (tabuleiro[0][0] != 0) {
            if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
                ganhador = tabuleiro[0][0];
            }
        }
    }

    //verificar ganhador na diagonal secundaria
    if (ganhador == 0) {
        if (tabuleiro[0][2] != 0) {
            if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
                ganhador = tabuleiro[0][2];
            }
        }
    }

    return ganhador;
}

void receberCelula(int *linha, int *coluna)
{
    int entrada;

    do {
        printf("Digite um numero de 1 a 9 para jogar: ");
        fflush(stdin);
        scanf("%d", &entrada);
        if (entrada < 1 || entrada > 9)
            printf("Entrada invalida!! ");
    } while (entrada < 1 || entrada > 9);

    //ajustando entrada para posicoes de vetor/matriz especificas da linguagem(0 a 8)
    entrada--;
    *linha = entrada / 3;
    *coluna = entrada % 3;
}

void receberNome(char mensagem[50], char nome[])
{
    do {
        printf("%s", mensagem);
        fflush(stdin);
        gets(nome);

        if (strlen(nome) < 3) {
            printf("Entrada invalida!! Nome precisa conter no mínimo 3 caracteres.\n");
        }
    } while (strlen(nome) < 3);
}

void inicializarTabuleiro(int tabuleiro[][tam])
{
    int i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void imprimirTabuleiro(int tabuleiro[][tam], int jogador1, int jogador2)
{
    int i, j, posicao, k, l;
    char anotacao[tam];

    anotacao[0] = ' ';
    anotacao[1] = 'X';
    anotacao[2] = 'O';

    system("cls");
    printf("Jogador 1: %s, representado pelo simbolo [X]\n", jogador1);
    printf("Jogador 2: %s, representado pelo simbolo [O]\n", jogador2);
    printf("\n");

    posicao = 1;
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187);
    printf("\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187);
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            printf("%c %c ", 186, anotacao[tabuleiro[i][j]]);
        }
        printf("%c", 186);
        printf("\t\t");
        for (j = 0; j < tam; j++) {
            k = (posicao - 1) / 3;
            l = (posicao - 1) % 3;
            if (anotacao[tabuleiro[k][l]] == ' ')
                printf("%c %d ", 186, posicao);
            else
                printf("%c   ", 186);
            posicao++;
        }
        printf("%c\n", 186);
        if (i < tam - 1) {
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
            printf("\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);

        }
        else {
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188);
            printf("\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188);
        }
    }
    printf("\n\n");
}

void iniciarJogoDaVelha()
{
    int tabuleiro[tam][tam];
    char jogador1[50], jogador2[50];
    int rodada, jogadorVez, i, j, jaPreenchido, ganhador;
    char jogarNovamente;

    receberNome("Digite o nome do Jogador 1: ", jogador1);
    receberNome("Digite o nome do Jogador 2: ", jogador2);

    jogarNovamente = 'S';
    while (jogarNovamente == 'S' || jogarNovamente == 's') {
        inicializarTabuleiro(tabuleiro);

        rodada = 1;
        ganhador = 0;
        while (rodada <= 9 && ganhador == 0) {
            imprimirTabuleiro(tabuleiro, jogador1, jogador2);

            if (rodada % 2 == 1) {
                jogadorVez = 1;
                printf("Rodada do Jogador 1 (%s)\n", jogador1);
            }
            else {
                jogadorVez = 2;
                printf("Rodada do Jogador 2 (%s)\n", jogador2);
            }

            do {
                jaPreenchido = 0;
                receberCelula(&i, &j);

                if (tabuleiro[i][j] != 0) {
                    jaPreenchido++;
                    printf("Essa entrada ja foi assinalada anteriormente!!\n\n");
                } else {

                }
            } while (jaPreenchido == 1);

            tabuleiro[i][j] = jogadorVez;
            ganhador = verificarSeAlguemGanhou(tabuleiro);
            rodada++;
        }

        imprimirTabuleiro(tabuleiro, jogador1, jogador2);

        if (ganhador == 0)
            printf("Deu velha =\\");
        else {
            if (ganhador == 1)
                printf("Venceu a partida o jogador %d: %s", ganhador, jogador1);
            else
                printf("Venceu a partida o jogador %d: %s", ganhador, jogador2);
        }

        printf("\n\nJogar Novamente? Digite S para Sim ou qualquer outra tecla para sair: ");
        fflush(stdin);
        scanf("&d", jogarNovamente);
    }
}

int main()
{
    iniciarJogoDaVelha();

    printf("\n\nFim da partida\n");
    printf("Pressione enter para encerrar\n");
    getch();

    return 0;
}

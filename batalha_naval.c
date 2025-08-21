#include <stdio.h>
#include <stdlib.h>

#define TAM 5

void inicializaTabuleiro(char tab[TAM][TAM]) {
    for(int i=0; i<TAM; i++) {
        for(int j=0; j<TAM; j++) {
            tab[i][j] = '~'; // Água
        }
    }
}

void imprimeTabuleiro(char tab[TAM][TAM], int revelar) {
    printf("  ");
    for(int i=0; i<TAM; i++) printf("%d ", i);
    printf("\n");

    for(int i=0; i<TAM; i++) {
        printf("%d ", i);
        for(int j=0; j<TAM; j++) {
            if(revelar == 0 && tab[i][j] == 'N') {
                printf("~ "); // não revela os navios
            } else {
                printf("%c ", tab[i][j]);
            }
        }
        printf("\n");
    }
}

int verificaVitoria(char tab[TAM][TAM]) {
    for(int i=0; i<TAM; i++) {
        for(int j=0; j<TAM; j++) {
            if(tab[i][j] == 'N') return 0; // Ainda tem navios vivos
        }
    }
    return 1; // Todos navios afundados
}

void posicionaNavios(char tab[TAM][TAM]) {
    // Posiciona 3 navios fixos para simplicidade
    tab[1][1] = 'N';
    tab[2][3] = 'N';
    tab[4][0] = 'N';
}

int main() {
    char tabuleiro[TAM][TAM];
    int x, y;
    int tentativas = 10;

    inicializaTabuleiro(tabuleiro);
    posicionaNavios(tabuleiro);

    printf("Bem vindo ao Jogo de Batalha Naval!\n");
    printf("Tente acertar os navios no tabuleiro %dx%d.\n", TAM, TAM);
    printf("Você tem %d tentativas.\n", tentativas);

    while(tentativas > 0) {
        imprimeTabuleiro(tabuleiro, 0);

        printf("Digite a linha e coluna para atacar (ex: 2 3): ");
        scanf("%d %d", &x, &y);

        if(x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Coordenadas inválidas! Tente novamente.\n");
            continue;
        }

        if(tabuleiro[x][y] == 'N') {
            printf("Você acertou um navio!\n");
            tabuleiro[x][y] = 'X'; // Acertou
        } else if(tabuleiro[x][y] == '~') {
            printf("Água! Tente outra vez.\n");
            tabuleiro[x][y] = 'O'; // Errou
        } else {
            printf("Você já tentou essa posição antes.\n");
            continue;
        }

        if(verificaVitoria(tabuleiro)) {
            printf("Parabéns! Você afundou todos os navios!\n");
            imprimeTabuleiro(tabuleiro, 1);
            break;
        }

        tentativas--;
        printf("Tentativas restantes: %d\n", tentativas);
    }

    if(tentativas == 0) {
        printf("Suas tentativas acabaram. Você perdeu!\n");
        printf("Tabuleiro final:\n");
        imprimeTabuleiro(tabuleiro, 1);
    }

    return 0;
}

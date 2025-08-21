#include <stdio.h>
#include <stdlib.h>

#define TAM 5
#define NAVIOS 3
#define TENTATIVAS 10

void inicializaTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = '~'; // Água
        }
    }
}

void imprimeTabuleiro(char tab[TAM][TAM], int revelarNavios) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 'N' && !revelarNavios)
                printf("~ ");
            else
                printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

void posicionaNavios(char tab[TAM][TAM]) {
    // Posições fixas para navios (3 navios)
    tab[1][1] = 'N';
    tab[2][3] = 'N';
    tab[4][0] = 'N';
}

int verificaVitoria(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 'N') return 0; // Ainda tem navios não atingidos
        }
    }
    return 1; // Todos navios afundados
}

int main() {
    char tabuleiro[TAM][TAM];
    int tentativasRestantes = TENTATIVAS;
    int linha, coluna;

    inicializaTabuleiro(tabuleiro);
    posicionaNavios(tabuleiro);

    printf("=== Bem-vindo ao Desafio Jogo de Batalha Naval ===\n");
    printf("Você tem %d tentativas para acertar todos os navios.\n\n", TENTATIVAS);

    while (tentativasRestantes > 0) {
        imprimeTabuleiro(tabuleiro, 0);
        printf("\nTentativas restantes: %d\n", tentativasRestantes);
        printf("Digite a linha e coluna para atacar (ex: 2 3): ");
        scanf("%d %d", &linha, &coluna);

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Coordenadas inválidas! Tente novamente.\n\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
            printf("Você já tentou essa posição! Tente outra.\n\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == 'N') {
            printf("Parabéns! Você acertou um navio!\n\n");
            tabuleiro[linha][coluna] = 'X'; // Acertou navio
        } else {
            printf("Água!\n\n");
            tabuleiro[linha][coluna] = 'O'; // Errou
        }

        if (verificaVitoria(tabuleiro)) {
            printf("Você venceu! Afundou todos os navios!\n");
            imprimeTabuleiro(tabuleiro, 1);
            break;
        }

        tentativasRestantes--;
    }

    if (tentativasRestantes == 0) {
        printf("Fim do jogo! Você perdeu.\n");
        printf("Posições dos navios:\n");
        imprimeTabuleiro(tabuleiro, 1);
    }

    return 0;
}

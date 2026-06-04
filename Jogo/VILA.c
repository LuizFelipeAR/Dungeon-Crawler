#include <stdio.h>
#include <stdlib.h>

#define MAX 25

const char *MAPA_VILA[10] = {
    "**********",
    "*        *",   
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "**********"
};

char terreno[MAX][MAX];
int altura, largura;
int jogador_linha = 1, jogador_coluna = 1; // Posicao do Jogador
char jogador_dir = '>'; // Direcao que o jogador olha

void carregar_vila(void) {
    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
            terreno[i][j] = MAPA_VILA[i][j];
}

void desenhar_vila(void) {
    system("cls");
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (i == jogador_linha && j == jogador_coluna)
                printf("%c", jogador_dir);
            else
                printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
}

void mover(int dx, int dy, char dir) {
    jogador_dir = dir; // Vira mesmo batendo na parede
    int novo_linha = jogador_linha + dy;
    int novo_coluna = jogador_coluna + dx;
    if (terreno[novo_linha][novo_coluna] != '*') {
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;
    }
}

int main(void) {
    altura = 10;
    largura = 10;
    carregar_vila();

    char entrada;
    while (1) {
        desenhar_vila();
        printf("Movimento (WASD): ");
        scanf(" %c", &entrada);
        if (entrada == 'w')      mover(0, -1, '^');
        else if (entrada == 's') mover(0,  1, 'v');
        else if (entrada == 'a') mover(-1, 0, '<');
        else if (entrada == 'd') mover( 1, 0, '>');
        else break;
    }
    
    return 0;
    }


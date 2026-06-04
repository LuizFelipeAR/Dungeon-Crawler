#include <stdio.h>
#include <stdlib.h>

#define MAX 25

const char *MAPA_VILA[10] = {
    "**********",
    "*        *",   
    "*        *",
    "*        *",
    "*        *",
    "*    N   *",
    "*        *",
    "*        *",
    "*        *",
    "**********"
};

char terreno[MAX][MAX];
int altura, largura;
int jogador_linha = 1, jogador_coluna = 1; // Posicao do Jogador
char jogador_dir = '>'; // Direcao que o jogador olha
int arma = 0; // 0 = nenhuma ainda; 1 = espada, 2 = arco, 3 = cajado

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
    if (terreno[novo_linha][novo_coluna] != '*' && terreno[novo_linha][novo_coluna] != 'N') {
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;
    }
}

void interagir(void) {
    int frente_linha = jogador_linha;
    int frente_coluna = jogador_coluna;

    if (jogador_dir == '^')      frente_linha--;
    else if (jogador_dir == 'v') frente_linha++;
    else if (jogador_dir == '<') frente_coluna--;
    else if (jogador_dir == '>') frente_coluna++;

    if (terreno[frente_linha][frente_coluna] == 'N') {
        int escolha = 0;

        while (escolha < 1 || escolha > 3) { // Repete enquanto for invalida
            printf("\n=== NPC ===\n");
            printf("Escolha sua arma:\n");
            printf("1 - Espada\n");
            printf("2 - Arco e Flecha\n");
            printf("3 - Cajado\n");
            printf("Opcao: ");
            scanf(" %d", &escolha);

            if (escolha < 1 || escolha > 3)
                printf("Opcao invalida! Tente de novo.\n");
        }

        arma = escolha; // So chega aqui quando a escolha e valida
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
        else if (entrada == 'i') interagir(); //A tecla de interacao
        else break;
    }
    
    return 0;
    }


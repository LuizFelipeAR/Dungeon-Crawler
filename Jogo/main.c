#include <stdio.h>
#include <stdlib.h>

#define MAX 25
#define AVANCOU 0   // ALTERACAO: codigo de retorno -> jogador pegou a escada
#define SAIU    1   // ALTERACAO: codigo de retorno -> jogador encerrou

const char *MAPA_VILA[10] = {
    "**********",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*    N   *",
    "*        *",
    "*        *",
    "*      L *",
    "**********"
};

const char *MAPA_ANDAR1[10] = {
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

const char *MAPA_ANDAR2[15] = {
    "***************",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "*             *",
    "***************"
};

const char *MAPA_ANDAR3[25] = {
    "*************************",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*************************"
};

char terreno[MAX][MAX];
int altura, largura;
int jogador_linha = 1, jogador_coluna = 1; // Posicao do Jogador
char jogador_dir = '>'; // Direcao que o jogador olha
int arma = 0; // 0 = nenhuma ainda; 1 = espada, 2 = arco, 3 = cajado

// ALTERACAO: carregar_vila virou carregar_andar(int andar) -> escolhe o mapa
void carregar_andar(int andar) {
    const char **mapa;                                 // ALTERACAO: aponta pro mapa escolhido
    if (andar == 0)      { mapa = MAPA_VILA;   altura = 10; largura = 10; } // ALTERACAO
    else if (andar == 1) { mapa = MAPA_ANDAR1; altura = 10; largura = 10; } // ALTERACAO
    else if (andar == 2) { mapa = MAPA_ANDAR2; altura = 15; largura = 15; } // ALTERACAO
    else                 { mapa = MAPA_ANDAR3; altura = 25; largura = 25; } // ALTERACAO

    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
            terreno[i][j] = mapa[i][j];                // ALTERACAO: copia do mapa escolhido

    jogador_linha = 1;                                 // ALTERACAO: reposiciona ao iniciar o andar
    jogador_coluna = 1;                                // ALTERACAO
    jogador_dir = '>';                                 // ALTERACAO
}

void desenhar_mapa(void) { // ALTERACAO: desenhar_vila virou desenhar_mapa
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
    if (terreno[novo_linha][novo_coluna] != '*' && terreno[novo_linha][novo_coluna] != 'N' && terreno[novo_linha][novo_coluna] != 'L') {
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;
    }
}

int interagir(void) { // ALTERACAO: era void, agora retorna int (avisa se desceu a escada)
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
        return 0;       // ALTERACAO: interagiu com NPC, mas nao desce
    }

    else if (terreno[frente_linha][frente_coluna] == 'L') {
        return 1;       // ALTERACAO: sinaliza que deve descer a escada
    }
    return 0;           // ALTERACAO: nao havia nada na frente
}

// ALTERACAO: funcao nova -> roda o laco de um andar e devolve o que aconteceu
int jogar_andar(void) {
    char entrada;
    while (1) {
        desenhar_mapa(); // ALTERACAO: nome novo
        printf("Movimento (WASD): ");
        scanf(" %c", &entrada);
        if (entrada == 'w')      mover(0, -1, '^');
        else if (entrada == 's') mover(0,  1, 'v');
        else if (entrada == 'a') mover(-1, 0, '<');
        else if (entrada == 'd') mover( 1, 0, '>');
        else if (entrada == 'i') {                 // ALTERACAO
            if (interagir() == 1) return AVANCOU;  // ALTERACAO: escada -> sobe de andar
        }
        else return SAIU;                          // ALTERACAO: era break, agora retorna SAIU
    }
}

int main(void) {
    int andar = 0;                          // ALTERACAO: 0 = Vila, depois 1, 2, 3
    while (andar <= 3) {                     // ALTERACAO: laco diretor do jogo
        carregar_andar(andar);               // ALTERACAO: carrega o andar atual
        int resultado = jogar_andar();        // ALTERACAO: joga e ve o que aconteceu
        if (resultado == AVANCOU) andar++;    // ALTERACAO: pegou escada -> proximo andar
        else break;                           // ALTERACAO: SAIU -> encerra
    }
    if (andar > 3) printf("Voce zerou o jogo!\n"); // ALTERACAO

    return 0;
}
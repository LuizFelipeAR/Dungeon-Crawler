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
    "*      L *",
    "**********"
};

const char *MAPA_ANDAR1[10] = {
    "**********",
    "*        *",
    "*   kkk  *",
    "*   kkk  *",
    "*        *",
    "*@       *",
    "*****D****",
    "*        *",
    "*      L *",
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
int tem_chave = 0;   // 0 = nao tem; 1 = tem uma chave

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
    tem_chave = 0;
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
    if (terreno[novo_linha][novo_coluna] != '*' && 
        terreno[novo_linha][novo_coluna] != 'N' && 
        terreno[novo_linha][novo_coluna] != 'L' && 
        terreno[novo_linha][novo_coluna] != 'k' && 
        terreno[novo_linha][novo_coluna] != 'D') {
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

    else if (terreno[frente_linha][frente_coluna] == '@') {   // chave
        terreno[frente_linha][frente_coluna] = ' ';   // pega a chave (some do mapa)
        tem_chave = 1;
        return 0;
    }

    else if (terreno[frente_linha][frente_coluna] == 'D') {   // porta fechada
        if (tem_chave == 1) {
            terreno[frente_linha][frente_coluna] = '=';   // abre a porta
            tem_chave = 0;                                // consome a chave
        }
        return 0;
    }

    return 0;   // interagiu com algo que nao tem acao, ou nada na frente
}

int atacar(void) {
    int dl; // direcao do ataque (frente do jogador)
    int dc; // direcao do ataque (frente do jogador)

    if (arma == 1) {   // espada: retangulo 3x2 a frente
        for (dl = 1; dl <= 2; dl++) {          // dl = profundidade (1 e 2 a frente)
            for (dc = -1; dc <= 1; dc++) {     // dc = largura (3)
                int alvo_linha, alvo_coluna;

                if (jogador_dir == '^') {            // cima
                    alvo_linha  = jogador_linha - dl;
                    alvo_coluna = jogador_coluna + dc;
                }
                else if (jogador_dir == 'v') {       // baixo
                    alvo_linha  = jogador_linha + dl;
                    alvo_coluna = jogador_coluna + dc;
                }
                else if (jogador_dir == '<') {       // esquerda
                    alvo_linha  = jogador_linha + dc;
                    alvo_coluna = jogador_coluna - dl;
                }
                else {                               // direita '>'
                    alvo_linha  = jogador_linha + dc;
                    alvo_coluna = jogador_coluna + dl;
                }

                if (terreno[alvo_linha][alvo_coluna] == 'k')
                    terreno[alvo_linha][alvo_coluna] = ' ';
            }
        }
    }   

    else if (arma == 2) {   // arco
        for (dl = 1; dl <= 4; dl++) {
            int alvo_linha = jogador_linha;    // padrao: mesma do jogador
            int alvo_coluna = jogador_coluna;  // padrao: mesma do jogador

            if (jogador_dir == '^')      alvo_linha  -= dl;   // so mexe na linha
            else if (jogador_dir == 'v') alvo_linha  += dl;   // so mexe na linha
            else if (jogador_dir == '<') alvo_coluna -= dl;   // so mexe na coluna
            else                         alvo_coluna += dl;   // so mexe na coluna

            if (terreno[alvo_linha][alvo_coluna] == 'k')
                terreno[alvo_linha][alvo_coluna] = ' ';
        }
    }

    else if (arma == 3) {   // cajado: 8 celulas ao redor
        for (dl = -1; dl <= 1; dl++) {
            for (dc = -1; dc <= 1; dc++) {
                if (dl == 0 && dc == 0) continue;   // pula a propria celula

                int alvo_linha = jogador_linha + dl;
                int alvo_coluna = jogador_coluna + dc;

                if (terreno[alvo_linha][alvo_coluna] == 'k')
                    terreno[alvo_linha][alvo_coluna] = ' ';   // destroi a caixa
            }
        }
    }
    return 0;   // 0 = ataque normal; 1 sera o boss derrotado (Andar 3)
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
            if (interagir() == 1) return 1;  // ALTERACAO: escada -> sobe de andar
        }
        else if (entrada == 'o') {
            if (atacar() == 1) return 1;   // boss morto -> encerra o andar (vitoria)
        }
        else return 0;                          // ALTERACAO: era break, agora retorna 0
    }
}

int main(void) {
    int andar = 0;
    while (andar <= 3) {
        carregar_andar(andar);
        if (jogar_andar() == 1) andar++;   // pegou escada -> proximo andar
        else break;                        // saiu -> encerra
    }
    if (andar > 3) printf("Voce zerou o jogo!\n");

    return 0;
}
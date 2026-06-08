#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 25
#define MAX_MONSTROS 10

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
    "*    kkk *",
    "*    kkk *",
    "*        *",
    "*      # *",
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
int tem_chave = 0;   // 0 = nao tem; 1 = tem uma chave`
int vidas = 3;   // vidas da partida (NAO zerar no carregar_andar)

int monstro_linha[MAX_MONSTROS];
int monstro_coluna[MAX_MONSTROS];
int monstro_tipo[MAX_MONSTROS];
int monstro_vivo[MAX_MONSTROS];
int num_monstros = 0;

void carregar_monstros(int andar) {
    num_monstros = 0;

    if (andar == 1) {
        monstro_linha[0] = 3; monstro_coluna[0] = 7; monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 7; monstro_coluna[1] = 3; monstro_tipo[1] = 1; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
    else if (andar == 2) {
        monstro_linha[0] = 2; monstro_coluna[0] = 2;  monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 8; monstro_coluna[1] = 10; monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
    else if (andar == 3) {
        monstro_linha[0] = 3;  monstro_coluna[0] = 3;  monstro_tipo[0] = 2; monstro_vivo[0] = 1;
        monstro_linha[1] = 10; monstro_coluna[1] = 15; monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
}

void atacar_monstros(int alvo_linha, int alvo_coluna) {
    int m;
    for (m = 0; m < num_monstros; m++) {
        if (monstro_vivo[m] &&
            monstro_linha[m] == alvo_linha &&
            monstro_coluna[m] == alvo_coluna) {
            monstro_vivo[m] = 0;   // mata o monstro
            return;
        }
    }
}


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

    carregar_monstros(andar);                          // ALTERACAO: carrega os monstros do andar
}

char monstro_em(int i, int j) {
    int m;
    for (m = 0; m < num_monstros; m++) {
        if (monstro_vivo[m] && monstro_linha[m] == i && monstro_coluna[m] == j) {
            if (monstro_tipo[m] == 1) return 'X';
            else                      return 'Y';
        }
    }
    return ' ';   // nenhum monstro aqui
}

void desenhar_mapa(void) { // ALTERACAO: desenhar_vila virou desenhar_mapa
    // Desenhar o Mapa
    system("cls");
    char mob;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            mob = monstro_em(i, j);

            if (i == jogador_linha && j == jogador_coluna)
                printf("%c", jogador_dir);
            else if (mob != ' ')
                printf("%c", mob);
            else
                printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
    // Desenhar HUD
    printf("Vidas: ");
    for (int v = 0; v < vidas; v++){
        printf("<3 ");
    }
    printf("\n");
    printf("Arma: ");
    if (arma == 1)      printf("Espada  =={======-\n");
    else if (arma == 2) printf("Arco    )))>----->\n");
    else if (arma == 3) printf("Cajado  ========(*)\n");
    else                printf("Nenhuma\n");    
}

int mover(int dx, int dy, char dir) {
    jogador_dir = dir;
    int novo_linha = jogador_linha + dy;
    int novo_coluna = jogador_coluna + dx;

    if (terreno[novo_linha][novo_coluna] != '*' &&
        terreno[novo_linha][novo_coluna] != 'N' &&
        terreno[novo_linha][novo_coluna] != 'L' &&
        terreno[novo_linha][novo_coluna] != 'k' &&
        terreno[novo_linha][novo_coluna] != 'D') {
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;

        if (terreno[jogador_linha][jogador_coluna] == '#')   // pisou no espinho
            return 1;   // avisa: levei dano
    }
    return 0;   // nada aconteceu
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

                atacar_monstros(alvo_linha, alvo_coluna);
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

            atacar_monstros(alvo_linha, alvo_coluna);
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

                atacar_monstros(alvo_linha, alvo_coluna);
            }
        }
    }
    return 0;   // 0 = ataque normal; 1 sera o boss derrotado (Andar 3)
}

int mover_monstros(void) {
    int i;
    for (i = 0; i < num_monstros; i++) {
        if (monstro_vivo[i] == 0) continue;

        int nova_linha  = monstro_linha[i];
        int nova_coluna = monstro_coluna[i];

        if (monstro_tipo[i] == 1) {            // TIPO 1: aleatorio
            int dir = rand() % 4;
            if      (dir == 0) nova_linha--;
            else if (dir == 1) nova_linha++;
            else if (dir == 2) nova_coluna--;
            else               nova_coluna++;
        }
        else if (monstro_tipo[i] == 2) {       // TIPO 2: perseguidor
            int dl = jogador_linha  - monstro_linha[i];
            int dc = jogador_coluna - monstro_coluna[i];
            if (abs(dl) >= abs(dc)) {
                if (dl > 0) nova_linha++;
                else        nova_linha--;
            } else {
                if (dc > 0) nova_coluna++;
                else        nova_coluna--;
            }
        }

        if (terreno[nova_linha][nova_coluna] == '*' ||
            terreno[nova_linha][nova_coluna] == 'N' ||
            terreno[nova_linha][nova_coluna] == 'L' ||
            terreno[nova_linha][nova_coluna] == 'k' ||
            terreno[nova_linha][nova_coluna] == 'D') continue;

        if (nova_linha == jogador_linha && nova_coluna == jogador_coluna)
            return 1;   // encostou no jogador -> avisa dano

        monstro_linha[i]  = nova_linha;
        monstro_coluna[i] = nova_coluna;
    }
    return 0;   // nenhum monstro encostou
}

// ALTERACAO: funcao nova -> roda o laco de um andar e devolve o que aconteceu
int jogar_andar(int andar) {
    char entrada;
    int dano;

    while (1) {
        desenhar_mapa(); // ALTERACAO: nome novo
        printf("Movimento (WASD): ");
        scanf(" %c", &entrada);

        dano = 0; // reset do dano a cada movimento

        if (entrada == 'w')      dano = mover(0, -1, '^');
        else if (entrada == 's') dano = mover(0,  1, 'v');
        else if (entrada == 'a') dano = mover(-1, 0, '<');
        else if (entrada == 'd') dano = mover( 1, 0, '>');
        else if (entrada == 'i') {                 // ALTERACAO
            if (interagir() == 1) return 1;  // ALTERACAO: escada -> sobe de andar
        }
        else if (entrada == 'o') {
            if (atacar() == 1) return 1;   // boss morto -> encerra o andar (vitoria)
        }
        else return 0;                   

        if (entrada == 'w' || entrada == 's' || entrada == 'a' || entrada == 'd') {
            if (mover_monstros() == 1)   // monstro encostou no jogador?
                dano = 1;                // mesmo efeito do espinho
        }

        if (dano == 1) {               // pisou no espinho
            vidas--;
            if (vidas <= 0) return 2;    // game over
            carregar_andar(andar);       // reinicia a fase atual
        }
    }
}

int main(void) {
    srand(time(NULL));
    int andar = 0;
    while (andar <= 3) {
        carregar_andar(andar);
        int resultado = jogar_andar(andar);

        if (resultado == 1) andar++;   // pegou escada -> proximo andar

        else if (resultado == 2) {
            printf("\n=== GAME OVER ===\n");
            break;
        }     // saiu -> encerra

        else break;
    }

    if (andar > 3) printf("Voce zerou o jogo!\n");
    
    return 0;
}
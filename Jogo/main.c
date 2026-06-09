#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 25
#define MAX_MONSTROS 10


const char *MAPA_VILA[10] = { //Mapa da vila em um Char que guarda o desenho todo
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

const char *MAPA_ANDAR1[10] = { //Mapa do andar 1 um Char que guarda o desenho todo
    "**********",
    "*    kkk *",
    "*     kk *",
    "*        *",
    "*    #   *",
    "*    #   *",
    "*       @*",
    "*     ****",
    "*     D L*",
    "**********"
};

const char *MAPA_ANDAR2[15] = { //Mapa do andar 2 em um Char que guarda o desenho todo
    "***************",
    "*       ##  O *",
    "*             *",
    "*             *",
    "*             *",
    "*         #   *",
    "*        ##  @*",
    "*         #   *",
    "*   ###       *",
    "*             *",
    "*****D*********",
    "*   *         *",
    "*   *      ****",
    "*@  *      D L*",
    "***************"   
};

const char *MAPA_ANDAR3[25] = { //Mapa do andar 3 em um Char que guarda o desenho todo
    "*************************",
    "*                 ##    *",
    "*                       *",
    "*         ###           *",
    "*          #       @    *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*            ##      ****",
    "*                    D @*",
    "*******D***     #    ****",
    "*         *             *",
    "*         ***************",
    "*                       *",
    "*                 @     *",
    "*        ###            *",
    "*                ##     *",
    "*            #          *",
    "*****D*******************",
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
int arma = 0; // 0 = nenhuma ainda, 1 = espada, 2 = arco, 3 = cajado
int tem_chave = 0; // 0 = nao tem, 1 = tem uma chave`
int vidas = 3; // vidas da partida (NAO zerar no carregar_andar)
int vida_boss = 4;

int monstro_linha[MAX_MONSTROS];
int monstro_coluna[MAX_MONSTROS];
int monstro_tipo[MAX_MONSTROS];
int monstro_vivo[MAX_MONSTROS];
int num_monstros = 0;

void carregar_monstros(int andar) { //define a posicao de comeco dos monstros e cada detalhe dos monstros de cada andar
    num_monstros = 0;

    if (andar == 1) {
        monstro_linha[0] = 3; monstro_coluna[0] = 7; monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 5; monstro_coluna[1] = 3; monstro_tipo[1] = 1; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
    else if (andar == 2) {
        monstro_linha[0] = 4; monstro_coluna[0] = 6;  monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 7; monstro_coluna[1] = 4;  monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        monstro_linha[2] = 11; monstro_coluna[2] = 6;  monstro_tipo[2] = 1; monstro_vivo[2] = 1;
        num_monstros = 3;
    }
    else if (andar == 3) {
        monstro_linha[0] = 5;  monstro_coluna[0] = 10;  monstro_tipo[0] = 2; monstro_vivo[0] = 1;
        monstro_linha[1] = 14; monstro_coluna[1] = 8;  monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        monstro_linha[2] = 21; monstro_coluna[2] = 12; monstro_tipo[2] = 3; monstro_vivo[2] = 1;
        num_monstros = 3;
        vida_boss = 4;
    }
}

int atacar_monstros(int alvo_linha, int alvo_coluna) {
    int m;
    for (m = 0; m < num_monstros; m++) {
        if (monstro_vivo[m] &&
            monstro_linha[m] == alvo_linha &&
            monstro_coluna[m] == alvo_coluna) {

            if (monstro_tipo[m] == 3) {     // BOSS
                vida_boss--;                // BOSS leva dano
                if (vida_boss <= 0) {       // Verifica se o BOSS morreu
                    monstro_vivo[m] = 0;    // BOSS morreu
                    return 1;               // Avisa: BOSS DERROTADO -> vitoria
                }
                return 0;                   // BOSS levou dano mas nao morreu
            }
            else {                          // Monstro comum
                monstro_vivo[m] = 0;        // Morre na hora
                return 0;
            }
        }
    }
    return 0; // Nao acertou nada
}


// Carrega o mapa atual
void carregar_andar(int andar) {
    const char **mapa;                                 
    if (andar == 0)      { mapa = MAPA_VILA;   altura = 10; largura = 10; } // Vila
    else if (andar == 1) { mapa = MAPA_ANDAR1; altura = 10; largura = 10; } // Andar 1
    else if (andar == 2) { mapa = MAPA_ANDAR2; altura = 15; largura = 15; } // Andar 2
    else                 { mapa = MAPA_ANDAR3; altura = 25; largura = 25; } // Andar 3

    int i, j;

    for (i = 0; i < altura; i++)
        for (j = 0; j < largura; j++)
            terreno[i][j] = mapa[i][j];                // Copia do mapa escolhido para facilitar a manipulacao

    jogador_linha = 1;                                 // Reposiciona ao iniciar o andar
    jogador_coluna = 1;                                // Reposiciona ao iniciar o andar
    jogador_dir = '>';                                 // Reposiciona ao iniciar o andar
    tem_chave = 0;

    carregar_monstros(andar);                          // Carrega os monstros do andar
}

char monstro_em(int i, int j) {
    int m;
    for (m = 0; m < num_monstros; m++) {
        if (monstro_vivo[m] && monstro_linha[m] == i && monstro_coluna[m] == j) {
            if (monstro_tipo[m] == 1) return 'X';
            else if (monstro_tipo[m] == 2) return 'Y';
            else                           return 'Z';
        }
    }
    return ' ';   // Nenhum monstro aqui
}

void desenhar_mapa(void) { // Desenha o mapa atual na tela
    system("cls"); 
    char mob;

    int i, j;

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
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
    jogador_dir = dir;  // Mostra onde o jogador esta olhando
    int novo_linha = jogador_linha + dy; // Atualiza a posicao do jogador 
    int novo_coluna = jogador_coluna + dx; // Atualiza a posicao do jogador

    // Verifica se nao ha obstaculo
    if (terreno[novo_linha][novo_coluna] != '*' &&
        terreno[novo_linha][novo_coluna] != 'N' &&
        terreno[novo_linha][novo_coluna] != 'L' &&
        terreno[novo_linha][novo_coluna] != 'k' &&
        terreno[novo_linha][novo_coluna] != 'D' &&
        terreno[novo_linha][novo_coluna] != 'O') {
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;

        if (terreno[jogador_linha][jogador_coluna] == '#') // Pisou no espinho
            return 1; // Avisa dano
    }
    return 0; // Nada aconteceu
}

int interagir(void) { // Inputs
    int frente_linha = jogador_linha; // Assume o valor do jogador para calcular o que tem na frente/lado
    int frente_coluna = jogador_coluna; // Assume o valor do jogador para calcular o que tem na frente/lado

    if (jogador_dir == '^')      frente_linha--;
    else if (jogador_dir == 'v') frente_linha++;
    else if (jogador_dir == '<') frente_coluna--;
    else if (jogador_dir == '>') frente_coluna++;

    // NPC na frente
    if (terreno[frente_linha][frente_coluna] == 'N') {
    int escolha = 0; // Guardar a escolha de arma do jogador

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

        arma = escolha; // Guarda a arma
        return 0;       // Interagiu com NPC, mas nao desce
    }

    else if (terreno[frente_linha][frente_coluna] == 'L') {
        return 1;       //Sinaliza que deve descer a escada
    }

    else if (terreno[frente_linha][frente_coluna] == '@') {    // Chave
        terreno[frente_linha][frente_coluna] = ' ';            // Pega a chave (some do mapa)
        tem_chave = 1;
        return 0;
    }

    else if (terreno[frente_linha][frente_coluna] == 'D') {    // Porta fechada
        if (tem_chave == 1) {
            terreno[frente_linha][frente_coluna] = '=';        // Abre a porta
            tem_chave = 0;                                     // Consome a chave
        }

        return 0;
    }

    else if (terreno[frente_linha][frente_coluna] == 'O') {   // Botao
        terreno[12][4] = ' ';                                 // Abre a barreira
        return 0;
    }

    return 0;
}

int atacar(void) {
    int dl; // Direcao do ataque (frente/lado do jogador)
    int dc; // Direcao do ataque (frente/lado do jogador)

    if (arma == 1) {   // Espada: retangulo 3x2 a frente
        for (dl = 1; dl <= 2; dl++) {          // dl = profundidade (1 e 2 a frente)
            for (dc = -1; dc <= 1; dc++) {     // dc = largura (3)
                int alvo_linha, alvo_coluna;

                if (jogador_dir == '^') {            
                    alvo_linha  = jogador_linha - dl;
                    alvo_coluna = jogador_coluna + dc;
                }
                else if (jogador_dir == 'v') {       
                    alvo_linha  = jogador_linha + dl;
                    alvo_coluna = jogador_coluna + dc;
                }
                else if (jogador_dir == '<') {       
                    alvo_linha  = jogador_linha + dc;
                    alvo_coluna = jogador_coluna - dl;
                }
                else {                               
                    alvo_linha  = jogador_linha + dc;
                    alvo_coluna = jogador_coluna + dl;
                }

                if (terreno[alvo_linha][alvo_coluna] == 'k') // Caixa
                    terreno[alvo_linha][alvo_coluna] = ' ';

                if (atacar_monstros(alvo_linha, alvo_coluna) == 1)
                    return 1;   // BOSS morreu -> vitoria
            }
        }
    }   

    else if (arma == 2) {   // Arco e Flecha
        for (dl = 1; dl <= 4; dl++) {
            int alvo_linha = jogador_linha;    
            int alvo_coluna = jogador_coluna;  

            if (jogador_dir == '^')      alvo_linha  -= dl;   // So mexe na linha
            else if (jogador_dir == 'v') alvo_linha  += dl;   // So mexe na linha
            else if (jogador_dir == '<') alvo_coluna -= dl;   // So mexe na coluna
            else                         alvo_coluna += dl;   // So mexe na coluna

            if (terreno[alvo_linha][alvo_coluna] == 'k')
                terreno[alvo_linha][alvo_coluna] = ' ';

            if (atacar_monstros(alvo_linha, alvo_coluna) == 1)
                return 1;   // BOSS morreu -> vitoria
        }
    }

    else if (arma == 3) {   // Cajado
        for (dl = -1; dl <= 1; dl++) {
            for (dc = -1; dc <= 1; dc++) {
                if (dl == 0 && dc == 0) continue;   // Pula a propria celula

                int alvo_linha = jogador_linha + dl;
                int alvo_coluna = jogador_coluna + dc;

                if (terreno[alvo_linha][alvo_coluna] == 'k')
                    terreno[alvo_linha][alvo_coluna] = ' ';   

                if (atacar_monstros(alvo_linha, alvo_coluna) == 1)
                    return 1;   // BOSS morreu -> vitoria
            }
        }
    }
    return 0;   // 0 = ataque normal, 1 sera o BOSS derrotado (Andar 3)
}

// Move os monstros e verifica se encostou no jogador
int mover_monstros(void) { 
    int i;
    for (i = 0; i < num_monstros; i++) {
        if (monstro_vivo[i] == 0) continue; // Monstro morto

        int nova_linha  = monstro_linha[i];
        int nova_coluna = monstro_coluna[i];

        if (monstro_tipo[i] == 1) { // TIPO 1: aleatorio
            int dir = rand() % 4;
            if      (dir == 0) nova_linha--;
            else if (dir == 1) nova_linha++;
            else if (dir == 2) nova_coluna--;
            else               nova_coluna++;
        }
        else if (monstro_tipo[i] == 2) { // TIPO 2: perseguidor
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

        else if (monstro_tipo[i] == 3) {       // BOSS: so persegue quando o jogador entra na arena
            if (jogador_linha >= 19) {         // 19 = primeira linha da arena
                int passo;
                for (passo = 0; passo < 2; passo++) { // Passo < 2, pois BOSS anda 2 vezes
                    int dl = jogador_linha  - nova_linha;
                    int dc = jogador_coluna - nova_coluna;
                    if (abs(dl) >= abs(dc)) {
                        if (dl > 0) nova_linha++;
                        else        nova_linha--;
                    } else {
                        if (dc > 0) nova_coluna++;
                        else        nova_coluna--;
                    }
                }
            }
        }

        if (terreno[nova_linha][nova_coluna] == '*' ||
            terreno[nova_linha][nova_coluna] == 'N' ||
            terreno[nova_linha][nova_coluna] == 'L' ||
            terreno[nova_linha][nova_coluna] == 'k' ||
            terreno[nova_linha][nova_coluna] == 'D') continue;

        if (nova_linha == jogador_linha && nova_coluna == jogador_coluna)
            return 1;   // Encostou no jogador, retorna dano

        monstro_linha[i]  = nova_linha;
        monstro_coluna[i] = nova_coluna;
    }
    return 0;   // Nenhum monstro encostou no jogador
}

// Agrupamento de varios void
int jogar_andar(int andar) {
    char entrada;
    int dano;

    while (1) {
        desenhar_mapa(); // Desenha o mapa a cada loop para mostrar as atualizacoes
        printf("Movimento (WASD): ");
        scanf(" %c", &entrada);

        dano = 0; // Reset do dano a cada movimento

        if (entrada == 'w')      dano = mover(0, -1, '^');
        else if (entrada == 's') dano = mover(0,  1, 'v');
        else if (entrada == 'a') dano = mover(-1, 0, '<');
        else if (entrada == 'd') dano = mover( 1, 0, '>');
        else if (entrada == 'i') {                 
            if (interagir() == 1) return 1;  // Sobe de andar
        }
        else if (entrada == 'o') {
            if (atacar() == 1) return 1;   // BOSS morto -> encerra o andar (vitoria)
        }
        else return 0;                   

        if (entrada == 'w' || entrada == 's' || entrada == 'a' || entrada == 'd') {
            if (mover_monstros() == 1)   // Verifica se houve dano pelo mosntro
                dano = 1;                
        }

        if (dano == 1) {               // Pisou no espinho
            vidas--;
            if (vidas <= 0) return 2;    // Game over
            carregar_andar(andar);       // Reinicia a fase atual
        }
    }
}

// "Funcao principal"
void jogar(void) {
    vidas = 3;
    int andar = 0;
    while (andar <= 3) {
        carregar_andar(andar);
        int resultado = jogar_andar(andar);

        if (resultado == 1) andar++;   // pegou escada -> proximo andar

        else if (resultado == 2) {
            printf("   ____    _    __  __ _____     _____     _______ ____     \n");
            printf("  / ___|  / \\  |  \\/  | ____|   / _ \\ \\   / / ____|  _ \\    \n");
            printf(" | |  _  / _ \\ | |\\/| |  _|    | | | \\ \\ / /|  _| | |_) |   \n");
            printf(" | |_| |/ ___ \\| |  | | |___   | |_| |\\ V / | |___|  _ <    \n");
            printf("  \\____/_/   \\_\\_|  |_|_____|   \\___/  \\_/  |_____|_| \\_\\   \n");
            break;
        }

        else break;
    }

    if (andar > 3) {
        printf("__     __  ___   _____    ___    ____    ___      _           \n");
        printf("\\ \\   / / |_ _| |_   _|  / _ \\  |  _ \\  |_ _|    / \\     \n");
        printf(" \\ \\ / /   | |    | |   | | | | | |_) |  | |    / _ \\      \n");
        printf("  \\ V /    | |    | |   | |_| | |  _ <   | |   / ___ \\      \n");
        printf("   \\_/    |___|   |_|    \\___/  |_| \\_\\ |___| /_/   \\_\\  \n");
        printf("\nVoce derrotou o rei demonio!\n");
        printf("O reino finalmente esta em paz...\n");
        printf("Parabens!\n");
    }

}

void tutorial(void) { //Funcao que chama o tutorial do jogo
    int escolha;
    while (1) {
        system("cls");
        printf("========================================\n");
        printf("            TUTORIAL DO JOGO\n");
        printf("========================================\n");
        printf("\nHISTORIA:\n");
        printf("Voce e um aventureiro que desceu a uma masmorra\n");
        printf("de tres andares para derrotar o terror que a habita.\n");
        printf("\nCONTROLES:\n");
        printf("W - Andar para cima\n");
        printf("A - Andar para a esquerda\n");
        printf("S - Andar para baixo\n");
        printf("D - Andar para a direita\n");
        printf("I - Interagir com objetos a frente\n");
        printf("O - Atacar a frente\n");
        printf("\nMECANICAS:\n");
        printf("Voce tem 3 vidas. Espinho ou monstro tira 1 vida\n");
        printf("e reinicia a fase. Sem vidas: GAME OVER.\n");
        printf("\nSIMBOLOS:\n");
        printf("^ v < > - Jogador (direcao)\n");
        printf("* Parede | # Espinho | k Caixa | O Botao\n");
        printf("D Porta fechada | @ Chave | = Porta aberta | L Escada\n");
        printf("X Monstro Tipo 1 | Y Monstro Tipo 2 | Z Boss\n");
        printf("\nDigite 1 para voltar ao menu: ");
        scanf(" %d", &escolha);
        if (escolha == 1) break;
    }
}

// Funcao principal
int main() {
    srand(time(NULL)); // Randomizar os movimentos dos inimigos "X"
    int opcao;
    while (1) {
        system("cls");
        printf(" ____    _   _   _   _    ____   _____    ___    _   _        ____   ____       _     __        __  _       _____   ____  \n");
        printf("|  _ \\  | | | | | \\ | |  / ___| | ____|  / _ \\  | \\ | |      / ___| |  _ \\     / \\    \\ \\      / / | |     | ____| |  _ \\ \n");
        printf("| | | | | | | | |  \\| | | |  _  |  _|   | | | | |  \\| |     | |     | |_) |   / _ \\    \\ \\ /\\ / /  | |     |  _|   | |_) |\n");
        printf("| |_| | | |_| | | |\\  | | |_| | | |___  | |_| | | |\\  |     | |___  |  _ <   / ___ \\    \\ V  V /   | |___  | |___  |  _ < \n");
        printf("|____/   \\___/  |_| \\_|  \\____| |_____|  \\___/  |_| \\_|      \\____| |_| \\_\\ /_/   \\_\\    \\_/\\_/    |_____| |_____| |_| \\_\\ \n\n");
        printf("1. Jogar\n");
        printf("2. Tutorial\n");
        printf("3. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &opcao);

        if (opcao == 1) {  // Comeca o jogo
            jogar();
            printf("\nDigite qualquer tecla e ENTER para voltar ao menu: ");
            char t;
            scanf(" %c", &t);
        }
        else if (opcao == 2) { // Chama o tutorial
            tutorial();
        }
        else if (opcao == 3) {  // Sair do programa
            system("cls");
            printf("Saindo do programa...\n");
            break;
        }
        else {
            printf("\nOpcao invalida!\n");
            printf("Digite qualquer tecla e ENTER para continuar: ");
            char t;
            scanf(" %c", &t);
        }
    }
    return 0;
}
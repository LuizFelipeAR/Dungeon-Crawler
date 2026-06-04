#include <stdio.h>

#include <stdio.h>

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

void carregar_fase(void) {
    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
            terreno[i][j] = MAPA_VILA[i][j];
}

int jogador_y = 1, jogador_x = 1; // Posicao do Jogador
void desenhar_mapa(char entrada) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
           if (i == jogador_y && j == jogador_x){
                if (entrada == 'd'){
                    printf(">");
                }
                else if(entrada == 's'){
                    printf("v");
                }
                else if(entrada == 'w'){
                    printf("^");
                }
                else if(entrada == 'a'){
                    printf("<");
                }
           }else
                printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
}

void mover(int dx, int dy){
    int novo_y = jogador_y + dy;
    int novo_x = jogador_x + dx;

    if(terreno[novo_y][novo_x] != '*'){
        jogador_x = novo_x;
        jogador_y = novo_y;
    }
}

int main(void) {
    altura = 10;            
    largura = 10;
    carregar_fase();   
    char entrada = 'd';
    while(1){     
        desenhar_mapa(entrada);
        printf("Movimento (WASD): ");
        scanf(" %c", &entrada);
        if (entrada == 'w') {
             mover(0, -1);
         }
        else if (entrada == 's') {
            mover(0,  1);
        }
        else if (entrada == 'a') {
            mover(-1, 0);
        }
        else if (entrada == 'd') {
            mover( 1, 0);
        }
        else{
            break;
        }  // sair
    }
    return 0;
    }


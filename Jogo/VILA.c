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
    int i, j;
    for (i = 0; i < altura; i++)
        for (j = 0; j < largura; j++)
            terreno[i][j] = MAPA_VILA[i][j];
}

void desenhar_mapa(void) {
    int i, j;
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    altura = 10;            
    largura = 10;
    carregar_fase();       
    desenhar_mapa();       

    return 0;
}

#include <stdio.h>
#include <stdio.h>

#define MAX 25 // Tamanho máximo do mapa

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
}; // Mapa da vila

char terreno[MAX][MAX]; // Matriz para armazenar o mapa atual
int altura, largura;

void carregar_vila(void) {
    int i, j;
    for (i = 0; i < altura; i++)
        for (j = 0; j < largura; j++)
            terreno[i][j] = MAPA_VILA[i][j];
} // Função para carregar o mapa da vila na matriz terreno

void desenhar_vila(void) {
    int i, j;
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
} // Função para desenhar o mapa

int main(void) {
    altura = 10; // Definindo a altura do mapa          
    largura = 10; // Definindo a largura do mapa
    carregar_vila();       
    desenhar_vila();       

    return 0;
}

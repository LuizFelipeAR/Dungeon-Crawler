#include <stdio.h>
#include <stdio.h>

#define MAX 25 // Tamanho máximo do mapa

const char *MAPA_3[25] = {
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
}; // Mapa 3

char terreno[MAX][MAX]; // Matriz para armazenar o mapa atual
int altura, largura;

void carregar_mapa3(void) {
    int i, j;
    for (i = 0; i < altura; i++)
        for (j = 0; j < largura; j++)
            terreno[i][j] = MAPA_3[i][j];
} // Função para carregar o mapa da vila na matriz terreno

void desenhar_mapa3(void) {
    int i, j;
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
} // Função para desenhar o mapa

int main(void) {
    altura = 25; // Definindo a altura do mapa          
    largura = 25; // Definindo a largura do mapa
    carregar_mapa3();       
    desenhar_mapa3();       

    return 0;
}


#include <stdio.h>

int main(){

    #define MAX 25

    const char *MAPA_VILA[ALTURA] = {
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

    int altura, largura = 10;

    char terreno[MAX][MAX];

    void carregar_fase(void) {
        for (int i = 0; i < altura; i++)
            for (int j = 0; j < largura; j++)
                terreno[i][j] = MAPA_VILA[i][j];
} 

    return 0;
}

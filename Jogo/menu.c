#include <stdio.h>

int main(){

int opcao;


while(1){

    
printf("Bem Vindo ao DUNGEON CRAWLER!\n");

printf("1. Jogar - Inicia o jogo a partir da vila\n");
printf("2. Tutorial - Exibe a historia do jogo, significado de cada simbolo e controles\n");
printf("3. Sair");

scanf("%d",&opcao);

  switch(opcao) {
        case 1:
            printf("Você escolheu JOGAR.\n");
            // void(jogo);
            break;
        case 2:
            printf("Você escolheu TUTORIAL.\n");
            // void(tutorial);
            break;
        case 3:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
    }

if(opcao == 3){
    break;
}

}

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void tutorial() {
    int escolha;

    while (1) {

        system("cls||clear");

        printf("========================================\n");
        printf("            TUTORIAL DO JOGO\n");
        printf("========================================\n");

        printf("\nTUTORIAL DOS CONTROLES:\n");
        printf("W - Andar para cima\n");
        printf("A - Andar para a esquerda\n");
        printf("S - Andar para baixo\n");
        printf("D - Andar para a direita\n");
        printf("I - Interagir com objetos a frente do jogador\n");
        printf("O - Ataque a celula a frente do jogador\n");

        printf("\nMECANICAS GERAIS:\n");
        printf("O jogador possui apenas TRES vidas!\n");
        printf("Se colidir com um espinho ou ser tocado por um monstro,\n");
        printf("o jogador perde 1 vida e a fase volta do inicio.\n");
        printf("Se perder TODAS as vidas: GAME OVER.\n");
        printf("O jogo retorna ao menu principal.\n");

        printf("\nSIGNIFICADO DE CADA SIMBOLO:\n");
        printf("^ - Jogador olhando para cima\n");
        printf("> - Jogador olhando para a direita\n");
        printf("< - Jogador olhando para a esquerda\n");
        printf("v - Jogador olhando para baixo\n");
        printf("* - Parede\n");
        printf("# - Espinho\n");
        printf("k - Caixa destrutivel\n");
        printf("O - Botao\n");
        printf("D - Porta fechada\n");
        printf("@ - Chave\n");
        printf("= - Porta aberta\n");
        printf("L - Escada\n");
        printf("X - Monstro Tipo 1\n");
        printf("Y - Monstro Tipo 2\n");
        printf("Z - Boss Final\n");

        printf("\nDigite 1 para voltar ao menu: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            printf("\nVoltando ao menu...\n");
            break;
        }
    }
}

int main() {

    int opcao;

    while (1) {

        system("cls||clear");

        printf("========================================\n");
        printf("       BEM-VINDO AO DUNGEON CRAWLER\n");
        printf("========================================\n\n");

        printf("1. Jogar\n");
        printf("   Inicia o jogo a partir da vila\n\n");

        printf("2. Tutorial\n");
        printf("   Exibe a historia, simbolos e controles\n\n");

        printf("3. Sair\n\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                system("cls||clear");
                printf("Voce escolheu JOGAR.\n");

                // jogo();

                printf("\nPressione ENTER para continuar...");
                getchar();
                getchar();
                break;

            case 2:
                tutorial();
                break;

            case 3:
                system("cls||clear");
                printf("Saindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");

                printf("\nPressione ENTER para continuar...");
                getchar();
                getchar();
        }

        if (opcao == 3) {
            break;
        }
    }

    return 0;
}
#include <stdio.h>
//escrever o tutorial
int main(){

printf("TUTORIAL DOS CONTROLES:\n");
printf("W - Andar para cima\n");
printf("A - Andar para a esquerda\n");
printf("S - Andar para baixo\n");
printf("D - Andar para a direita\n");
printf("I - Interagir com objetos a frente do jogador\n");
printf("O - Ataque a celula a frente do jogador\n");

printf("\nMECANICAS GERAIS\n");
printf("O jogador possui apenas TRES vidas!\n");
printf("Se colidir com um espinho ou ser tocado por um monstro, o jogador perde 1 vida e a fase volta do inicio\n");
printf("Se perder TODAS as vidas: GAME OVER, volta pro menu principal (EH SAL)\n");

printf("\nSIGNIFICADO DE CADA SIMBOLO\n");
printf("^ - Jogador olhando pra cima\n");
printf("> - Jogador olhando para a direita\n");
printf("< - Jogador olhando para a esquerda\n");
printf("v - Jogador olhando pra baixo\n");
printf("# Espinho: o jogador morre ao passar por cima\n");
printf("k Caixa: o jogador não pode passar, mas pode ser destruída com ataque\n");
printf("O Botão: executa uma ação ao ser pressionado\n");
printf("D Porta fechada: o jogador não pode passar\n");
printf("@ Chave: abre uma porta fechada ao interagir\n");
printf("= Porta aberta: o jogador pode passar\n");
printf("L Escada: leva o jogador para a próxima fase\n");
printf("X Monstro Tipo 1\n");
printf("Y Monstro Tipo 2\n");
printf("Z Boss Final");


return 0;
}

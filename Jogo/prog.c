#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

initscr();

int main(){

int i;
int j;

printf("\n\nTESTE primeiro\n");

for(i=0;i<12;i++){
printf("#");
}
printf("\n#");
for(i=0;i<7;i++){
    for(j=0;j<10;j++){
        printf(" ");
    }
printf("#\n#");
}
for(i=0;i<11;i++){
    printf("#");
}

return 0; 
}
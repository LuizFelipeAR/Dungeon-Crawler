#include <stdio.h>
#include <stdlib.h>




int main(){
             

int i;
int j;

printf("\n\nTESTE primeiro\n");

for(i=0;i<12;i++){
printf("#");
}
printf("\n#");
for(i=0;i<10;i++){
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
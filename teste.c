#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

int main(){
    
    char tecla = 'a';
    char op = 'a';
    int display_erro = 0;
    do{
        if(kbhit()){
            tecla = getch();

            if(
                tecla == 'a' ||
                tecla == 'w' ||
                tecla == 's' ||
                tecla == 'd'
            ){
                op = tecla;
                display_erro = 0;
            } else {
                display_erro = 1;
            }

        }
        system("cls");
        printf("%c\n", op);

        if(display_erro){
            printf("tecla invalida\n");
        }
    //executo meu programa bazeado na tecla
    }while(tecla != '0');
}
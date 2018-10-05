
#include "includes.c"
#define TAM 10
#define TAM_MAX 100
#include "structs.c"

char matriz[TAM][TAM];
Minhoca  minhoca;
Doce doce ;
char op = 's';

#include "prototipos.c"
#include "functions.c"


int main() {

	config();

	jogar();

}


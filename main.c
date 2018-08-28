#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10
#define TAM_MAX 100
#include "structs.c"
Minhoca  minhoca;
Doce doce ;
char matriz[TAM][TAM];
#include "prototipos.c"
#include "functions.c"


int main() {

	config();

	jogar();

}


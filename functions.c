void limparMatriz(){
    for(int i = 0; i < TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            matriz[i][j] = ' ';
        }
    }    
}

void imprimirMatriz(){
  for(int i = 0; i < TAM; i++){ //colunas
        printf("|");
        for(int j = 0; j < TAM; j++){               //barrinha no inicio e
            printf(" %c ", matriz[i][j]);           //fim de cada linha
        }
        printf("|\n");
    }    
    printf("\n");
}


int ponteiroNulo(Posicao *p ){
	if(p == NULL){
		printf("Não foi possível alocar memória :(\n");
		exit(1);
	}
	return 0;
}

void config(){
	srand((unsigned) time(NULL));
	minhoca.tamanho = 3;
	minhoca.p = (Posicao*) malloc(sizeof(Posicao) * minhoca.tamanho);
	ponteiroNulo(minhoca.p);
	
	for(int i = 0; i < minhoca.tamanho; i++){
		minhoca.p[i].x = 0;
		minhoca.p[i].y = minhoca.tamanho - i - 1;

		printf("(%d, %d))\n", 0, (minhoca.tamanho - i -1));

	}

	gerarDoce();

	limparMatriz();

	colocaObjeto();

}

void gerarDoce(){

	doce.posi.x = rand()%10;
	doce.posi.y = rand()%10;

	for(int i = 0; i < minhoca.tamanho; i++){
		if(doce.posi.x == minhoca.p[i].x  &&  doce.posi.y == minhoca.p[i].y ){
			doce.posi.x = rand()%10;
			doce.posi.y = rand()%10;
			i = 0;
		}		
	}

	doce.vida = abs(doce.posi.x - minhoca.p[0].x) + abs(doce.posi.y - minhoca.p[0].y) + 1;

}

void colocaObjeto(){
	for(int i = 0; i < minhoca.tamanho; i++){
		matriz[ minhoca.p[i].y ][ minhoca.p[i].x ] = '0';
	}
	matriz[ doce.posi.x ][ doce.posi.y ] = '*';
}

void movimentar(Posicao p){
  	
	minhoca.p = (Posicao *) realloc( minhoca.p, sizeof(Posicao) * minhoca.tamanho );

	for( int i =0; i < minhoca.tamanho; i++ )

	doce.vida--;
}

void jogar(){
	char op; 

	Posicao posiCabeca;
	
    while(1){

    	limparTela();

        imprimirMatriz();
        op = getch();

        posiCabeca = minhoca.p[0];

        switch(op){
        	case 'a':
        	case 'A':
        		posiCabeca.x--;
        		break;
        	case 'w' :
        	case 'W' :
        		posiCabeca.y--;
        		break;
			case 'd' :
        	case 'D' :
        		posiCabeca.x++;
        		break;
        	case 's' :
        	case 'S' :
        		posiCabeca.x++;
        		break;
        	case 'q' :
        	case 'Q' :
        		sair();
        		break;
        	default :
        		limparTela();
                printf("Tecla inválida\n");
                printf("(Tecla W) Para cima\n");
                printf("(Tecla A) Para esquerda\n");
                printf("(Tecla S) Para baixo\n");
                printf("(Tecla D) Para direita\n");
                printf("(Tecla Q) Para sair\n\n");
                break;
        }

        if(doce.vida == 0){
        	gerarDoce();
        }

        if(posiCabeca.x == doce.posi.x  &&  posiCabeca.y == doce.posi.y ){
        	minhoca.tamanho++;
     		gerarDoce();
        }

        if(minhoca.tamanho == TAM_MAX ){
        	printf("Fim de jogo, você atingiu o tamanho máximo da minhoca!  :D\n");
        	sair();
        }

        for(int i = 0;i < minhoca.tamanho; i++){
        	if(posiCabeca.x == minhoca.p[i].x  &&  posiCabeca.y == minhoca.p[i].y){
        		printf("Fim de jogo, a minhoca bateu no própio corpo! :(\n");
        		sair();
        	}
        }

        if( TAM < posiCabeca.x || posiCabeca.x < 0  ||  TAM < posiCabeca.x  ||  posiCabeca.x < 0 ){
        	printf("Fim de jogo, você bateu nas extremidades do tabuleiro!  :(\n");
        	sair();
        }


    }
}

void limparTela(){
   system("@cls||clear");
}

void sair(){

	free(minhoca.p);
	exit(1);
}
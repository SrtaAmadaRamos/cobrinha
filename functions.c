void limparMatriz(){
    for(int i = 0; i < TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            matriz[i][j] = ' ';
        }
    }    
}

void imprimirMatriz(){
    printf("Resta %d movimentos\n", doce.vida);
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
        minhoca.p[i].x = minhoca.tamanho - i - 1;
		minhoca.p[i].y = 0;
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
			i = -1;
		}		
	}

	doce.vida = abs(doce.posi.x - minhoca.p[0].x) + abs(doce.posi.y - minhoca.p[0].y) + 1;

}

void colocaObjeto(){
    matriz[ doce.posi.x ][ doce.posi.y ] = '*';
	for(int i = 0; i < minhoca.tamanho; i++){
		matriz[ minhoca.p[i].x ][ minhoca.p[i].y ] = '0';
	}	
}

void movimentar(Posicao p){
	minhoca.p = (Posicao *) realloc( minhoca.p, sizeof(Posicao) * minhoca.tamanho );
	for( int i = minhoca.tamanho -1 ; i >= 0 ;i-- ){
        if(i == 0){
            minhoca.p[i] = p;
        }else{
            minhoca.p[i] = minhoca.p[i - 1] ;
        }
    }

    for(int i = 1; i < minhoca.tamanho - 1; i++){
        if(minhoca.p[0].x == minhoca.p[i].x  &&  minhoca.p[0].y == minhoca.p[i].y){
            sair(2);
        }
    }

    if( TAM < minhoca.p[0].x || minhoca.p[0].x < 0  ||  TAM < minhoca.p[0].y  ||  minhoca.p[0].y < 0 ){
        sair(3);
    }
}

void jogar(){
	char op; 
	Posicao posiCabeca = minhoca.p[0];;
	limparTela();
    int valida = 1; 
    char letra;
    op = 's';

    while(1){   

        imprimirMatriz();
        sleep(1);

        if(kbhit()){
            letra = getch();

            if( letra == 'a' ||
                letra == 'A' ||
                letra == 's' ||
                letra == 'S' ||
                letra == 'd' ||
                letra == 'D' ||
                letra == 'w' ||
                letra == 'W' ||
                letra == 'q' ||
                letra == 'Q'
            ){
                valida = 1;
                op = letra ;
            }else{
                valida = 0;
            }

        }
        
        switch(op){
        	case 'a':
        	case 'A':
        		posiCabeca.y--;
                doce.vida--;
        		break;
        	case 'w' :
        	case 'W' :
        		posiCabeca.x--;
                doce.vida--;
        		break;
			case 'd' :
        	case 'D' :
        		posiCabeca.y++;
                doce.vida--;
        		break;
        	case 's' :
        	case 'S' :
        		posiCabeca.x++;
                doce.vida--;
        		break;
        	case 'q' :
        	case 'Q' :
        		sair(4);
        		break;
        	default :
        		limparTela();
                break;
        }

        if(posiCabeca.x == doce.posi.x  &&  posiCabeca.y == doce.posi.y ){
        	minhoca.tamanho++;
     		gerarDoce();
        }

        movimentar(posiCabeca);

        if(doce.vida == 0){
            gerarDoce();
        }            

        if(minhoca.tamanho == TAM_MAX ){
            sair(1);
        }  

        limparMatriz();

        colocaObjeto();
        limparTela();

        
        if(!valida){
            printf("Tecla inválida\n");
            printf("(Tecla W) Para cima\n");
            printf("(Tecla A) Para esquerda\n");
            printf("(Tecla S) Para baixo\n");
            printf("(Tecla D) Para direita\n");
            printf("(Tecla Q) Para sair\n\n");
        }

    }
}

void limparTela(){
   system("@cls||clear");
}

void sair(int op){

    if(op == 1)
        printf("Fim de jogo, você atingiu o tamanho máximo da minhoca!  :D\n");
    if(op == 2)
        printf("Fim de jogo, a minhoca bateu no própio corpo! :(\n");
    if(op == 3)
        printf("Fim de jogo, você bateu nas extremidades do tabuleiro!  :(\n");
    
	free(minhoca.p);
	exit(1);
}

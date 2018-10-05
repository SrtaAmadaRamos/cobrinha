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

    int continua;

    printf("1 - Continuar o jogo anterior.\n");
    printf("2 - Iniciar um novo jogo.\n");
    printf("=> ");
    scanf("%d", &continua);

    srand((unsigned) time(NULL));

    if(continua == 1){

        if(!carregarJogo()){

            printf("Não foi possível carregar o jogo\n");
            exit(1);
        }

    }else if(continua == 2){
        minhoca.tamanho = 3;
        minhoca.p = (Posicao*) malloc(sizeof(Posicao) * minhoca.tamanho);
        ponteiroNulo(minhoca.p);
    
        for(int i = 0; i < minhoca.tamanho; i++){
            minhoca.p[i].x = minhoca.tamanho - i - 1;
            minhoca.p[i].y = 0;
        }

        gerarDoce();
    }else{
        printf("Opção inválida\n");
        exit(1);
    }

	limparMatriz();

	colocaObjeto();
}

int carregarJogo(){
    FILE *file ;                              // criando ponteiro para o aquivo
    Jogo *jogo;                               //criando ponteiro p/ jogo
    file = fopen("salvo.txt" , "rb");        //abre um arquivo binario para leitura

    if(file == NULL ){                    // verificando se conseguiu abrir o arquivo
        return 0;
    }

    jogo = (Jogo *) malloc(sizeof(Jogo));   //alocando memoria pra variavel jogo

    fread(jogo, sizeof(Jogo) , 1, file);  //f read ler o arquivo e salva os dados na variavel jogo(variavel,tamanho,quantidade, pointeiro)

    minhoca.tamanho = jogo->tamanho_minhoca ;  
    
    minhoca.p = (Posicao *) malloc(sizeof(Posicao) * minhoca.tamanho);  //alocou a posicao da minhocaa

    for(int i = 0; i < minhoca.tamanho ; i++){
        minhoca.p[i] = jogo->posi_minhoca[i];
    }

    doce.vida = jogo->doce.vida;
    doce.posi = jogo->doce.posi;
    op = jogo->direcao;

    fclose(file);
    free(jogo);  
    return 1;
}

void salvarJogo(){
    FILE *file;
    file = fopen("salvo.txt", "wb");  //abrindo uma arquivo binario para escrita

    if(file == NULL){
        printf("Não foi possivel abrir o arquivo :(");
        exit(1);
    }

    Jogo *jogo ;
    jogo = (Jogo *) malloc( sizeof(Jogo));

    jogo->doce.vida = doce.vida;
    jogo->doce.posi.x = doce.posi.x;                //copiando os dados do jogo pra variavel jogo
    jogo->doce.posi.y = doce.posi.y;
    jogo->direcao = op;

    jogo->tamanho_minhoca = minhoca.tamanho;

    for(int i = 0 ; i < minhoca.tamanho; i++){
        jogo->posi_minhoca[i] = minhoca.p[i] ;
    }

    fwrite(jogo, 1, sizeof(Jogo), file);  //escreve os dados setados anteriormente no arquivo
    fclose(file);
    free(jogo);  
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

    for(int i = 1; i < minhoca.tamanho; i++){
        if(minhoca.p[0].x == minhoca.p[i].x  &&  minhoca.p[0].y == minhoca.p[i].y){
            sair(2);
        }
    }

    if( TAM <= minhoca.p[0].x || minhoca.p[0].x < 0  ||  TAM <= minhoca.p[0].y  ||  minhoca.p[0].y < 0 ){
        sair(3);
    }
}

void jogar(){
	Posicao posiCabeca = minhoca.p[0];;
	limparTela();
    int valida = 1; 
    char letra;

    while(1){   

        imprimirMatriz();
        millisleep(400);

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
                letra == 'r' ||
                letra == 'R' ||
                letra == 'q' ||
                letra == 'Q'
            ){

                if(
                    letra == 'r' ||
                    letra == 'R' 
                ) {
                    salvarJogo();
                }else{
                    valida = 1;
                    op = letra ;
                }

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
            printf("(Tecla R) Para salvar o jogo\n");
            printf("(Tecla Q) Para sair\n\n");


        }

    }
}

void limparTela(){
   system("@cls||clear");
}

void sair(int op){

    if(op == 1)
        printf("Game Over, você atingiu o tamanho máximo da minhoca!  :D\n");
    if(op == 2)
        printf("Game Over, a minhoca bateu no própio corpo! :(\n");
    if(op == 3)
        printf("Game Over, você bateu nas extremidades do tabuleiro!  :(\n");
    
	free(minhoca.p);
	exit(1);
}

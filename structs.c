typedef struct {
	int x;
	int y;

} Posicao;

typedef struct {
	int tamanho;
	Posicao *p ;
} Minhoca;

typedef struct  {
	int vida;
	Posicao posi;

} Doce;

typedef struct{
	int tamanho_minhoca;
	Posicao posi_minhoca[TAM_MAX];
    Doce doce ;
    char direcao;
} Jogo; 

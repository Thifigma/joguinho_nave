/*Biblioteca responsável pelo controle do armamento das naves. 
 * É dividida entre o armamento da nave e o armamento das naves
 * inimigas. */

#ifndef __ARMA__H_
#define __ARMA__H_

#define NUM_BALAS 8
#define NUM_BALAS_INIMIGOS 2

struct bala {

	int especial;
	int tamanho_bala;
	int x;
	int y;
	int velocidade;	
	char ativo;
};


/* Responsável por setar os valores iniciais a bala. */
void inicia_bala(struct bala *arma);

/*Essa função é responsável por atirar um projetil. 
* Toda vez que a tecla espaço é apertada um projetil é disparado. */
void atira(struct bala *arma, int x, int y);

/* Essa função é responsável por realizar a movimentação da bala. */
void atualiza_bala(struct bala *arma);

/* Essa função é responsável por desenhar a bala da nave na tela. */
void desenha_bala(struct bala *arma);


/* Arma inimigos. 
*	Todas as funções abaixo são homologas as de cima, porém
*	é utilizada apenas pelo inimigos. 
*/
void inicia_bala_inimigos(struct bala *arma);
void atira_inimigos(struct bala *arma, int x, int y);
void atualiza_bala_inimigos(struct bala *arma);
void desenha_bala_inimigos(struct bala *arma, int id_inimigo);


#endif

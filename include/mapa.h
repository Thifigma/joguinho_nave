/*Biblioteca para controle geral do mapa, como colisões, explosões,
 * especiais.  */

#include "nave.h"
#include "arma.h"
#include "inimigos.h"

#ifndef __MAPA_H_
#define __MAPA_H_

#define LARGURA_T 1200
#define ALTURA_T 600
#define FPS 60
#define NUM_ESTRELAS 100
#define NUM_PLANOS 3

struct explosao {

	ALLEGRO_BITMAP *sprite[8];
	int frame_atual;
	int num_frames;	
	int largura_frame;
	int altura_frame;
};

struct especial {

	ALLEGRO_BITMAP *img;
	int frame_atual;
	int num_frames;	
	int largura_frame;
	int altura_frame;

	int x;
	int y;
	int borda_x;
	int borda_y;
};

struct fundo {

	ALLEGRO_BITMAP *sprite;
	int largura_t;
	int altura_t;

	int largura_bg;
	int altura_bg;

	float escala_x;
	float escala_y;
};

struct plano {
	
	int x;
	int y;
	int velocidade;
};

/*Essa função é responsavel por iniciar o fundo do jogo, para representar 
 * as três dimensões. */
void inicia_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS]);

/*Essas funções são responsaveis por dar a sensação de movimento. */
void atualiza_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS]);
void desenha_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS], int fase);

/* As funções de colisões tratam da geometria de colisão a 
 * bala se trata da geometria da colisão entre a bala da nave 
 * contra os inimigos. Já a a colisão nave, trata da colisão entre 
 * as naves e a colisão inimigos da bala do inimigo com a nave. */
void colisao_bala(struct bala *arma, struct skin *inimigo);
void colisao_nave(struct nave *tucano, struct skin *i);
void colisao_bala_inimigos(struct bala *arma, struct nave *tucano);
void colisao_bala_cf(struct bala *arma, struct nave *tucano);

/* Essa função é responsavel por dar a sensação de explosões 
 * é chamada quando a vida das naves chegam a 0. */
void inicia_explosao(struct explosao *f);
void desenha_explosao(struct explosao *f, int x, int y);
void destroi_explosao(struct explosao *f);

/*Essas funções são responsáveis por representar o especial no 
 * mapa.*/
void inicia_especial(struct especial *poder);
void desenha_especial(struct especial *poder);

/*Essa função em especial é uma geometria de colisão contra um objeto no mapa.*/
int pega_especial(struct nave *tucano, struct especial *poder);


#endif

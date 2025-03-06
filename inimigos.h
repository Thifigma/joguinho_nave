/*Biblioteca responsável pelo controle geral dos inimigos. */

#include "arma.h"


#ifndef __INIMIGOS_H_
#define __INIMIGOS_H_

#define QT_INIMIGOS 12

struct skin {

	int x;
	int y;
	int vida;
	int velocidade;

	int borda_x;
	int borda_y;

	ALLEGRO_BITMAP *sprite;
	int frame_atual;
	int num_frames;
	int largura_frame;
	int altura_frame;


	struct bala arma[NUM_BALAS_INIMIGOS]; 
};


/*Fase 0. */

/* O toten é responsável por controlar o inicio do jogo. 
*  Após destruido se da inicio a jogatina. 
*/
void inicia_toten(struct skin *toten);
void desenha_toten(struct skin *toten);

/*As naves inimigas são divididas em fase(1, 2, 3) respectivamente. 
 * A função inicia_ é responsavel por iniciar as variáveis e carregar 
 * as sprites de cada nave inimiga. 
 *
 * A função de atualiza é responsável pela movimentação das naves
 * inimigas em conjunto com a função desenha que após atualizar
 * sua posição em '(x, y)' seu sprite é carregado. */


/* fase 1. */

void inicia_barto(struct skin *barto);
void inicia_lomeu(struct skin *lomeu);
void inicia_spin(struct skin *spin);
void inicia_chefao(struct skin *chefao);


void atualiza_barto(struct skin *i);
void atualiza_lomeu(struct skin *i);
void atualiza_spin(struct skin *i);
void atualiza_chefao(struct skin *i);


void desenha_barto(struct skin *barto);
void desenha_lomeu(struct skin *lomeu);
void desenha_spin(struct skin *spin);
void desenha_chefao(struct skin *chefao);


/*Fase 2. */

void inicia_peixoto(struct skin *peixoto);
void inicia_paladino(struct skin *paladino);
void inicia_gris(struct skin *gris);
void inicia_loor(struct skin *loor);
void inicia_chefao_f2(struct skin *chefao_f2);

void desenha_peixoto(struct skin *peixoto);
void desenha_paladino(struct skin *paladino);
void desenha_gris(struct skin *gris);
void desenha_loor(struct skin *loor);
void desenha_chefao_f2(struct skin *chefao_f2);

void atualiza_peixoto(struct skin *i);
void atualiza_paladino(struct skin *i);
void atualiza_loor(struct skin *i);
void atualiza_gris(struct skin *i);
void atualiza_chefao_f2(struct skin *i);

/* Final. */
void inicia_cf(struct skin *cf);
void desenha_cf(struct skin *cf);
void atualiza_cf(struct skin *cf);


/* Destrutor. */

void destroi_inimigo(struct skin *i);

#endif

/*Biblioteca responsável pela nave principal do jogo. */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "arma.h"


#ifndef __NAVE__H_
#define __NAVE__H_

#define PESO_NAVE 20
#define MASSA_NAVE 10

#define CIMA 0
#define BAIXO 1
#define ESQUERDA 2
#define DIREITA 3
#define ESPACO 4


struct nave {

	int x;
	int y;
	int vida;
	int velocidade;

	int borda_x;
	int borda_y;

	ALLEGRO_BITMAP *sprite;
	ALLEGRO_BITMAP *sprite_esq;
	int frame_atual;
	int num_frames;
	int largura_frame;
	int altura_frame;
	
	struct bala arma[NUM_BALAS];
};


void inicia_nave(struct nave *tucano);

void atualiza_nave(struct nave *tucano, int *teclas);

int atualiza_nave_fim_de_jogo(struct nave *tucano);
int atualiza_nave_ganha_jogo(struct nave *tucano);

void desenha_nave(struct nave *t, int *teclas);


#endif

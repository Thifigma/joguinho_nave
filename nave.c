#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "nave.h"
#include "mapa.h"
#include "arma.h"

void inicia_nave(struct nave *tucano)
{
	tucano->x = 100;
	tucano->y = (ALTURA_T / 2);
	tucano->vida = 100;
	tucano->velocidade = 10;
	tucano->sprite = al_load_bitmap("sprites/nave.png");
	tucano->sprite_esq = al_load_bitmap("sprites/nave_esquerda.png");
	tucano->frame_atual = 0;
	tucano->num_frames = 1;
	tucano->largura_frame = 64;
	tucano->altura_frame = 64;

	tucano->borda_x = 100;
	tucano->borda_y = 40;

	inicia_bala(tucano->arma);
}

void atualiza_nave(struct nave *tucano, int *teclas)
{
	tucano->y -= teclas[CIMA] * tucano->velocidade;
	tucano->y += teclas[BAIXO] * tucano->velocidade;
	tucano->x -= teclas[ESQUERDA] * tucano->velocidade;
	tucano->x += teclas[DIREITA] * tucano->velocidade;
}


int atualiza_nave_fim_de_jogo(struct nave *tucano)
{
	tucano->x += 3;
	if(tucano->x > 1000)
		return 1;
	return 0; 
}


int atualiza_nave_ganha_jogo(struct nave *tucano)
{
	if(tucano->x > 1000)
		return 1; /*Para sair do jogo. */ 
	return 0; /*Vai ficar no jogo. */ 
}

void desenha_nave(struct nave *t, int *teclas)
{
	if(t->x > LARGURA_T)
		t->x = LARGURA_T - 50;
	else if(t->x < 0)
		t->x = 50;
 		
	if(t->y > ALTURA_T)
		t->y = ALTURA_T - 60;
	else if(t->y < 0)
		t->y = 5;
	
	if(teclas[ESQUERDA]) {
		al_draw_bitmap_region(t->sprite_esq, 
						  t->frame_atual * t->largura_frame, 0,
						  t->largura_frame, t->altura_frame, 
						  t->x, t->y, 0);
	}
	else{

		al_draw_bitmap_region(t->sprite, 
						  t->frame_atual * t->largura_frame, 0,
						  t->largura_frame, t->altura_frame, 
						  t->x, t->y, 0);
	}
}

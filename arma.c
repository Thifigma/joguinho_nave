#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>

#include "mapa.h"
#include "arma.h"


void inicia_bala(struct bala *arma)
{
	for(int i = 0; i < NUM_BALAS; i++) {
		
		arma[i].especial = 0;	
		arma[i].tamanho_bala = 2;
		arma[i].velocidade = 10;	
		arma[i].ativo = 0;
	}
}


void atira(struct bala *arma, int x, int y)
{
	for(int i = 0; i < NUM_BALAS; i++) {
			
		if(! arma[i].ativo) {
				
			arma[i].x = x + 5;
			arma[i].y = y;			
			arma[i].ativo = 1;

			break; /* Garante que apenas uma bala vai ser disparada!  */
		}
	}	
}


void atualiza_bala(struct bala *arma)
{
	for(int i = 0; i < NUM_BALAS; i++) {
			
		if(arma[i].ativo) {
			
			/* Movimentação a direita de cada projetil. */
				arma[i].x += arma[i].velocidade;	

			/* Se a bala passar da tela ela é re-inserida na arma. */
			if(arma[i].x > LARGURA_T) 
				arma[i].ativo = 0;
		}
	}
}



void desenha_bala(struct bala *arma)
{
	for(int i = 0; i < NUM_BALAS; i++) {
		if(arma[i].ativo) {
			
			if(arma[i].especial) {
				arma[i].tamanho_bala = 5;
				al_draw_filled_circle(arma[i].x + 30, arma[i].y + 30, 
				arma[i].tamanho_bala, al_map_rgb(255, 0, 0));
			}
			else {
				al_draw_filled_circle(arma[i].x + 30, arma[i].y + 30, 
				arma[i].tamanho_bala, al_map_rgb(255, 255, 255));
			}
		}
	}
}


/*Inimigos. */

void inicia_bala_inimigos(struct bala *arma)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
		
		arma[i].tamanho_bala = 2;
		arma[i].velocidade = 10;	
		arma[i].ativo = 0;
	}
}



void atira_inimigos(struct bala *arma, int x, int y)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
			
		if(! arma[i].ativo) {
				
			arma[i].x = x - 5;
			arma[i].y = y;			
			arma[i].ativo = 1;
			break;
		}
	}	
}


void atualiza_bala_inimigos(struct bala *arma)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
			
		if(arma[i].ativo) {
			
			/* Desloca o projetil a esquerda. */
			arma[i].x -= arma[i].velocidade;	

			/* Garante que quando sair da tela sera re-utilizado. */
			if(arma[i].x < 0) 
				arma[i].ativo = 0;
		}
	}
}

void desenha_bala_inimigos(struct bala *arma, int id_inimigo)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
		if(arma[i].ativo) {
			
			arma[i].tamanho_bala = 5;

			/*Padrão. */
			if(id_inimigo == 1) {
				al_draw_filled_circle(arma[i].x - 30, arma[i].y + 60, 
				arma[i].tamanho_bala, al_map_rgb(255, 10, 10));
			}  /*Chefões. */
			else if(id_inimigo == 2) {
				
				arma[i].tamanho_bala = 10;
				al_draw_filled_circle(arma[i].x - 30, arma[i].y + 60, 
				arma[i].tamanho_bala, al_map_rgb(255, 40, 2));
			} /*Chefão final*/
			else if(id_inimigo == 3) {

				arma[i].tamanho_bala = 2;

				al_draw_filled_circle(arma[i].x - 10, arma[i].y + 180, 
				arma[i].tamanho_bala, al_map_rgb(255, 0, 0));

				al_draw_filled_circle(arma[i].x - 10, arma[i].y - 260, 
				arma[i].tamanho_bala, al_map_rgb(255, 0, 0));

			}
		}
	}
}

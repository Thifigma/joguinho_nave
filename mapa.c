#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdio.h>

#include "mapa.h"
#include "nave.h"

void inicia_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS])
{

	srand(time(NULL));

	for(int i = 0; i < NUM_PLANOS; i++) {
		for(int j = 0; j < NUM_ESTRELAS; j++) {
			
			if(i == 0) { /*Dimensao mais na frente, perto da nave. */

				fundo[i][j].x = 5 + rand() % (LARGURA_T - 10);
				fundo[i][j].y = 5 + rand() % (ALTURA_T - 10);
				fundo[i][j].velocidade = 6;
			}
			else if(i == 1) {

				fundo[i][j].x = 5 + rand() % (LARGURA_T - 10);
				fundo[i][j].y = 5 + rand() % (ALTURA_T - 10);
				fundo[i][j].velocidade = 4;
			} 
			else if(i == 2)	{ /*Dimensão mais ao fundo. */

				fundo[i][j].x = 5 + rand() % (LARGURA_T - 10);
				fundo[i][j].y = 5 + rand() % (ALTURA_T - 10);
				fundo[i][j].velocidade = 1;
			}	
		}
	}
}

void inicia_explosao(struct explosao *f)
{
	for(int i = 0; i < 8; i++) {
		char nome[50];
		sprintf(nome, "sprites/explosao/%d.png", i+1);
		f->sprite[i] = al_load_bitmap(nome);
	}	

	f->frame_atual = 0;
	f->num_frames = 1;	
	f->largura_frame = 64;
	f->altura_frame = 64;
}


void destroi_explosao(struct explosao *f)
{
	for(int i = 0; i < 8; i++) {
		
		al_destroy_bitmap(f->sprite[i]);
		f->sprite[i] = NULL;
	}

}

void atualiza_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS])
{
	for(int i = 0; i < NUM_PLANOS; i++) {
		for(int j = 0; j < NUM_ESTRELAS; j++) {
			
			if(i == 0) {

				fundo[i][j].x -= fundo[i][j].velocidade;
				
				if(fundo[i][j].x < 0)
					fundo[i][j].x = LARGURA_T;
			}
			else if(i == 1) {

				fundo[i][j].x -= fundo[i][j].velocidade;
				
				if(fundo[i][j].x < 0)
					fundo[i][j].x = LARGURA_T;

			}
			else if(i == 2)	{

				fundo[i][j].x -= fundo[i][j].velocidade;
				
				if(fundo[i][j].x < 0)
					fundo[i][j].x = LARGURA_T;
			}
		}
	}
}


void desenha_fundo(struct plano fundo[NUM_PLANOS][NUM_ESTRELAS], int fase)
{
	for(int i = 0; i < NUM_PLANOS; i++) {
		for(int j = 0; j < NUM_ESTRELAS; j++) {
			
			if(i == 0) {

				if(fase == 1 || fase == 0 || fase == 4) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 255, 255));
				}
				else if(fase == 2) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(0, 0, 255));
				}	
				else if(fase == 3) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 0, 0));
				}
			}
			else if(i == 1) {

				if(fase == 1 || fase == 0 || fase == 4) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 255, 255));
				}
				else if(fase == 2) {
	
					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(0, 0, 255));
				}
				else if(fase == 3) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 0, 0));
				}
			}
			else if(i == 2)	{

				if(fase == 1 || fase == 0 || fase == 4) {
					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 220, 0));
				}
				else if(fase == 2){

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(0, 0, 255));
				}
				else if(fase == 3) {

					al_draw_pixel(fundo[i][j].x, fundo[i][j].y, 
					al_map_rgb(255, 0, 0));
				}
			}
		}
	}
}


void desenha_explosao(struct explosao *f, int x, int y)
{
	for(int i = 0; i < 8; i++) {
		
		x += 40;
		y += 10;
		
		al_draw_bitmap_region(f->sprite[i], 
							  f->frame_atual * f->largura_frame, 0,
							  f->largura_frame, f->altura_frame, 
							  x, y, 0);

		al_rest(1 / FPS);
	}
}



void colisao_bala(struct bala *arma, struct skin *inimigo)
{
	for(int i = 0; i < NUM_BALAS; i++) {
		
		if(arma[i].ativo) {
			
			if(arma[i].x > (inimigo->x - inimigo->borda_x) && 
			   arma[i].x < (inimigo->x + inimigo->borda_x) && 
			   arma[i].y > ((inimigo->y - inimigo->borda_y) + 40) &&
			   arma[i].y < ((inimigo->y + inimigo->borda_y) + 40))
				{

					if(arma[i].especial) {
						arma[i].especial = 0;
						arma[i].tamanho_bala = 2;
						inimigo->vida -= 50;
					}

					arma[i].ativo = 0;
					inimigo->vida -= 25;
				
					if(inimigo->vida < 10) {
						struct explosao bom;
						inicia_explosao(&bom);
						desenha_explosao(&bom, inimigo->x, inimigo->y);
						destroi_explosao(&bom);
						inimigo->vida = 0;						
					}
				} 
		}
	}
}


void colisao_bala_inimigos(struct bala *arma, struct nave *tucano)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
		
		if(arma[i].ativo) {
			
			if(arma[i].x > (tucano->x - tucano->borda_x) && 
			   arma[i].x < (tucano->x + tucano->borda_y) && 
			   arma[i].y > (tucano->y - tucano->borda_y) &&
			   arma[i].y < (tucano->y + tucano->borda_y))
				{

					arma[i].ativo = 0;
					tucano->vida -= 25;
				
					if(tucano->vida < 10) {
						struct explosao bom;
						inicia_explosao(&bom);
						desenha_explosao(&bom, tucano->x, tucano->y);
						destroi_explosao(&bom);
						tucano->vida = 0;						
					}
				} 
		}
	}
}



void colisao_nave(struct nave *tucano, struct skin *i)
{
	if(tucano->x > (i->x - (i->borda_x )) && 
	   tucano->x < (i->x + (i->borda_x )) && 
	   tucano->y > (i->y - (i->borda_y )) &&
	   tucano->y < (i->y + (i->borda_y )) )
	{
		struct explosao bom;
		inicia_explosao(&bom);
		desenha_explosao(&bom, tucano->x, tucano->y);	
		tucano->vida = 0;
	}
}



void inicia_especial(struct especial *poder)
{
	poder->img = al_load_bitmap("sprites/especial.png");

	poder->frame_atual = 0;
	poder->num_frames = 1;	
	poder->largura_frame = 128;
	poder->altura_frame = 128;

	poder->x = (LARGURA_T / 2);
	poder->y = (ALTURA_T / 2);

	poder->borda_x = 50;
	poder->borda_y = 50;
}


void desenha_especial(struct especial *poder)
{
	al_draw_bitmap_region(poder->img, 
					  poder->frame_atual * poder->largura_frame, 0,
					  poder->largura_frame, poder->altura_frame, 
					  poder->x, poder->y, 0);
	
}



int pega_especial(struct nave *tucano, struct especial *poder)
{
	if(tucano->x > (poder->x - (poder->borda_x )) && 
	   tucano->x < (poder->x + (poder->borda_x )) && 
	   tucano->y > (poder->y - (poder->borda_y )) &&
	   tucano->y < (poder->y + (poder->borda_y )) ) 
	{
		tucano->arma->especial = 1;
		return 1;
	}

	return 0;
}




void colisao_bala_cf(struct bala *arma, struct nave *tucano)
{
	for(int i = 0; i < NUM_BALAS_INIMIGOS; i++) {
		
		if(arma[i].ativo) {
			
			if(arma[i].x > (tucano->x - tucano->borda_x) && 
			   arma[i].x < (tucano->x + tucano->borda_x) && 
			   arma[i].y > ((tucano->y - tucano->borda_y) + 40) &&
			   arma[i].y < ((tucano->y + tucano->borda_y) + 40))
				{

					arma[i].ativo = 0;
					tucano->vida -= 30;
				
					if(tucano->vida <= 10) {
						struct explosao bom;
						inicia_explosao(&bom);
						desenha_explosao(&bom, tucano->x, tucano->y);
						tucano->vida = 0;						
					}
				} 
		}
	}
}


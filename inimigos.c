
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>
#include "mapa.h"
#include "inimigos.h"
#include "arma.h"


/*Barto*/

void inicia_barto(struct skin *barto)
{
	barto->x = (LARGURA_T - 100);
	barto->y = (ALTURA_T - 100);
	barto->vida = 100;
	barto->velocidade = 4;
	barto->sprite = al_load_bitmap("sprites/inimigos/fase_1/barto.png");
	barto->frame_atual = 0;
	barto->num_frames = 1;
	barto->largura_frame = 128;
	barto->altura_frame = 128;


	barto->borda_x = 80;
	barto->borda_y = 80;

	inicia_bala_inimigos(barto->arma);
}

void atualiza_barto(struct skin *i)
{
	i->x -= i->velocidade; 
	i->y = i->x + i->x*pow(M_E, 2 - pow(i->x, 2)) + log((i->x + (5*M_E) ) / 17); 
}


void desenha_barto(struct skin *barto)
{
	if(barto->x > LARGURA_T)
		barto->x = 5;
	else if(barto->x < 0)
		barto->x = LARGURA_T - 5;

	if(barto->y > ALTURA_T)
		barto->y = 5;
	else if(barto->y < 0)
		barto->y = ALTURA_T + 5;

	al_draw_bitmap_region(barto->sprite, 
						  barto->frame_atual * barto->largura_frame, 0,
						  barto->largura_frame, barto->altura_frame, 
						  barto->x, barto->y, 0);
	
	atira_inimigos(barto->arma, barto->x, barto->y);
}


/*Lomeu. */


void inicia_lomeu(struct skin *lomeu)
{
	lomeu->x = (LARGURA_T - 200);
	lomeu->y = ((ALTURA_T / 2)); //+ 150);
	lomeu->vida = 100;
	lomeu->velocidade = 6;
	lomeu->sprite = al_load_bitmap("sprites/inimigos/fase_1/lomeu.png");
	lomeu->frame_atual = 0;
	lomeu->num_frames = 1;
	lomeu->largura_frame = 128;
	lomeu->altura_frame = 128;

	lomeu->borda_x = 80;
	lomeu->borda_y = 80;

	inicia_bala_inimigos(lomeu->arma);
}


void atualiza_lomeu(struct skin *i)
{
	i->x -= i->velocidade;
	i->y -= sin(i->x);
	
	if(i->x >  LARGURA_T / 2) 
		i->y += tanh(i->x);
}

void desenha_lomeu(struct skin *lomeu)
{

	if(lomeu->x > LARGURA_T)
		lomeu->x = 5;
	else if(lomeu->x < 0)
		lomeu->x = LARGURA_T - 5;

	if(lomeu->y > ALTURA_T)
		lomeu->y = 5;
	else if(lomeu->y < 0)
		lomeu->y = ALTURA_T + 5;

	al_draw_bitmap_region(lomeu->sprite, 
						  lomeu->frame_atual * lomeu->largura_frame, 0,
						  lomeu->largura_frame, lomeu->altura_frame, 
						  lomeu->x, lomeu->y, 0);


	atira_inimigos(lomeu->arma, lomeu->x, lomeu->y);
}


/* spin. */

void inicia_spin(struct skin *spin)
{
	spin->x = (LARGURA_T - 200);
	spin->y = ((ALTURA_T / 2) + 130);
	spin->vida = 100;
	spin->velocidade = 6;
	spin->sprite = al_load_bitmap("sprites/inimigos/fase_1/spin.png");
	spin->frame_atual = 0;
	spin->num_frames = 1;
	spin->largura_frame = 128;
	spin->altura_frame = 128;

	spin->borda_x = 80;
	spin->borda_y = 80;

	inicia_bala_inimigos(spin->arma);	
}


void atualiza_spin(struct skin *i)
{
	i->x -= i->velocidade;;
}


void desenha_spin(struct skin *spin)
{
	if(spin->x > LARGURA_T)
		spin->x = 5;
	else if(spin->x < 0)
		spin->x = LARGURA_T - 5;

	if(spin->y > ALTURA_T)
		spin->y = 5;
	else if(spin->y < 0)
		spin->y = ALTURA_T + 5;

	al_draw_bitmap_region(spin->sprite, 
						  spin->frame_atual * spin->largura_frame, 0,
						  spin->largura_frame, spin->altura_frame, 
						  spin->x, spin->y, 0);

	atira_inimigos(spin->arma, spin->x, spin->y);
}


/* Chefao Fase 1.*/

void inicia_chefao(struct skin *chefao)
{
	chefao->x = (LARGURA_T / 2);
	chefao->y = ((ALTURA_T / 2) - 200); //+ 150);
	chefao->vida = 700;
	chefao->velocidade = 3;
	chefao->sprite = al_load_bitmap("sprites/inimigos/fase_1/chefao_f1.png");
	chefao->frame_atual = 0;
	chefao->num_frames = 1;
	chefao->largura_frame = 315;
	chefao->altura_frame = 348;


	chefao->borda_x = 150;
	chefao->borda_y = 150;

	inicia_bala_inimigos(chefao->arma);
}



void desenha_chefao(struct skin *chefao)
{

	if(chefao->x > LARGURA_T)
		chefao->x = 5;
	else if(chefao->x < 0)
		chefao->x = LARGURA_T - 5;


	if(chefao->y > ALTURA_T)
		chefao->y = 5;
	else if(chefao->y < 0)
		chefao->y = ALTURA_T;
	
	al_draw_bitmap_region(chefao->sprite, 
						  chefao->frame_atual * chefao->largura_frame, 0,
						  chefao->largura_frame, chefao->altura_frame, 
						  chefao->x, chefao->y, 0);

	atira_inimigos(chefao->arma, chefao->x, chefao->y);
}


void atualiza_chefao(struct skin *i)
{
	i->x -= i->velocidade;
	
	if(i->vida < (i->vida / 2) )
		i->x -= log(i->velocidade);
	
	if(i->y < ALTURA_T + 300)
		i->y -= 2;
	else
		i->y += 3;
}


/* Fase 2. */


void inicia_peixoto(struct skin *peixoto)
{
	peixoto->x = (LARGURA_T - 100);
	peixoto->y = ((ALTURA_T / 2) - 100);
	peixoto->vida = 200;
	peixoto->velocidade = 4;
	peixoto->sprite = al_load_bitmap("sprites/inimigos/fase_2/peixoto.png");
	peixoto->frame_atual = 0;
	peixoto->num_frames = 1;
	peixoto->largura_frame = 128;
	peixoto->altura_frame = 128;

	peixoto->borda_x = 80;
	peixoto->borda_y = 80;

	inicia_bala_inimigos(peixoto->arma);
}


void desenha_peixoto(struct skin *peixoto)
{
	if(peixoto->x > LARGURA_T)
		peixoto->x = 5;
	else if(peixoto->x < 0)
		peixoto->x = LARGURA_T - 5;

	if(peixoto->y > ALTURA_T)
		peixoto->y = 5;
	else if(peixoto->y < 0)
		peixoto->y = ALTURA_T;

	al_draw_bitmap_region(peixoto->sprite, 
						  peixoto->frame_atual * peixoto->largura_frame, 0,
						  peixoto->largura_frame, peixoto->altura_frame, 
						  peixoto->x, peixoto->y, 0);
	
	atira_inimigos(peixoto->arma, peixoto->x, peixoto->y);
}


void atualiza_peixoto(struct skin *i)
{
	i->x -= i->velocidade;
	i->y -= sin(i->x);
	
	if(i->x >  LARGURA_T / 2) 
		i->y += tanh(i->x);
}


void inicia_paladino(struct skin *paladino)
{
	paladino->x = (LARGURA_T - 100);
	paladino->y = (ALTURA_T / 2) + 50;
	paladino->vida = 200;
	paladino->velocidade = 7;
	paladino->sprite = al_load_bitmap("sprites/inimigos/fase_2/paladino.png");
	paladino->frame_atual = 0;
	paladino->num_frames = 1;
	paladino->largura_frame = 128;
	paladino->altura_frame = 128;

	paladino->borda_x = 80;
	paladino->borda_y = 80;

	inicia_bala_inimigos(paladino->arma);
}


void desenha_paladino(struct skin *paladino)
{
	if(paladino->x > LARGURA_T)
		paladino->x = 5;
	else if(paladino->x < 0)
		paladino->x = LARGURA_T - 5;

	if(paladino->y > ALTURA_T)
		paladino->y = 5;
	else if(paladino->y < 0)
		paladino->y = ALTURA_T;

	al_draw_bitmap_region(paladino->sprite, 
						  paladino->frame_atual * paladino->largura_frame, 0,
						  paladino->largura_frame, paladino->altura_frame, 
						  paladino->x, paladino->y, 0);

	atira_inimigos(paladino->arma, paladino->x, paladino->y);
}


void atualiza_paladino(struct skin *i)
{
	i->x -= i->velocidade;

	if(i->x > 800)
		i->y += tanh(i->x);
	else
		i->y -= tanh(i->x);
}



void inicia_loor(struct skin *loor)
{
	loor->x = (LARGURA_T - 300);
	loor->y = (ALTURA_T  - 500);
	loor->vida = 200;
	loor->velocidade = 7;
	loor->sprite = al_load_bitmap("sprites/inimigos/fase_2/loor.png");
	loor->frame_atual = 0;
	loor->num_frames = 1;
	loor->largura_frame = 128;
	loor->altura_frame = 128;

	loor->borda_x = 80;
	loor->borda_y = 80;

	inicia_bala_inimigos(loor->arma);
}


void desenha_loor(struct skin *loor)
{
	if(loor->x > LARGURA_T)
		loor->x = 5;
	else if(loor->x < 0)
		loor->x = LARGURA_T - 5;

	if(loor->y > ALTURA_T)
		loor->y = 5;
	else if(loor->y < 0)
		loor->y = ALTURA_T;


	al_draw_bitmap_region(loor->sprite, 
						  loor->frame_atual * loor->largura_frame, 0,
						  loor->largura_frame, loor->altura_frame, 
						  loor->x, loor->y, 0);

	atira_inimigos(loor->arma, loor->x, loor->y);
}

void inicia_gris(struct skin *gris)
{
	gris->x = (LARGURA_T / 2) + 400;
	gris->y = (ALTURA_T / 2) - 200;
	gris->vida = 350;
	gris->velocidade = 6.5;
	gris->sprite = al_load_bitmap("sprites/inimigos/fase_2/gris.png");
	gris->frame_atual = 0;
	gris->num_frames = 1;
	gris->largura_frame = 370;
	gris->altura_frame = 370;

	gris->borda_x = 150;
	gris->borda_y = 350;

	inicia_bala_inimigos(gris->arma);
}


void desenha_gris(struct skin *gris)
{
	if(gris->x > LARGURA_T)
		gris->x = 5;
	else if(gris->x < 0)
		gris->x = LARGURA_T - 5;

	if(gris->y > ALTURA_T)
		gris->y = 5;
	else if(gris->y < 0)
		gris->y = ALTURA_T;

	al_draw_bitmap_region(gris->sprite, 
						  gris->frame_atual * gris->largura_frame, 0,
						  gris->largura_frame, gris->altura_frame, 
						  gris->x, gris->y, 0);


	atira_inimigos(gris->arma, gris->x, gris->y);
}


void atualiza_gris(struct skin *i)
{
	i->x -= i->velocidade;
	i->y -= sin(i->x);
	
	if(i->x >  LARGURA_T / 2) 
		i->y += tanh(i->x);
}



void inicia_chefao_f2(struct skin *chefao_f2)
{
	chefao_f2->x = (LARGURA_T / 2) + 400;
	chefao_f2->y = (ALTURA_T / 2) - 200;
	chefao_f2->vida = 850;
	chefao_f2->velocidade = 5;
	chefao_f2->sprite = al_load_bitmap("sprites/inimigos/fase_2/chefe_f2.png");
	chefao_f2->frame_atual = 0;
	chefao_f2->num_frames = 1;
	chefao_f2->largura_frame = 250;
	chefao_f2->altura_frame = 182;

	chefao_f2->borda_x = 150;
	chefao_f2->borda_y = 150;
	
	inicia_bala_inimigos(chefao_f2->arma);
}


void desenha_chefao_f2(struct skin *chefao_f2)
{
	if(chefao_f2->x > LARGURA_T)
		chefao_f2->x = 5;
	else if(chefao_f2->x < 0)
		chefao_f2->x = LARGURA_T - 5;

	if(chefao_f2->y > ALTURA_T)
		chefao_f2->y = 5;
	else if(chefao_f2->y < 0)
		chefao_f2->y = ALTURA_T;

	al_draw_bitmap_region(chefao_f2->sprite, 
						  chefao_f2->frame_atual * chefao_f2->largura_frame, 0,
						  chefao_f2->largura_frame, chefao_f2->altura_frame, 
						  chefao_f2->x, chefao_f2->y, 0);

	atira_inimigos(chefao_f2->arma, chefao_f2->x, chefao_f2->y);
}


void atualiza_chefao_f2(struct skin *i)
{
	i->x -= i->velocidade; 
	i->y = (i->x) + i->x*pow(M_E, 2 - pow(rand(), 2)) + log((rand() - (5*M_E) ) / 17);
}


/* Final. */


void inicia_cf(struct skin *cf)
{
	cf->x = (LARGURA_T / 2) + 500;
	cf->y = (ALTURA_T / 2) - 300;
	cf->vida = 400;
	cf->velocidade = 10;
	cf->sprite = al_load_bitmap("sprites/inimigos/final/cf.png");
	cf->frame_atual = 0;
	cf->num_frames = 1;
	cf->largura_frame = 754;
	cf->altura_frame = 548;

	cf->borda_x = 250;
	cf->borda_y = 450;
	
	inicia_bala_inimigos(cf->arma);
}


void desenha_cf(struct skin *cf)
{
	if(cf->x > LARGURA_T)
		cf->x = 5;
	else if(cf->x < 0)
		cf->x = LARGURA_T - 5;

	if(cf->y > ALTURA_T)
		cf->y = 5;
	else if(cf->y < 0)
		cf->y = ALTURA_T;


	al_draw_bitmap_region(cf->sprite, 
						  cf->frame_atual * cf->largura_frame, 0,
						  cf->largura_frame, cf->altura_frame, 
						  cf->x, cf->y, 0);

	atira_inimigos(cf->arma, cf->x, cf->y);
}


void atualiza_cf(struct skin *cf)
{
	int i = 2;

	if(cf->vida < 350) {
		cf->x -= cf->velocidade * i;
		i++;
	}
}



void inicia_toten(struct skin *toten)
{
	toten->x = (LARGURA_T / 2);
	toten->y = (ALTURA_T - 245);
	toten->vida = 50;
	toten->velocidade = 0;
	toten->sprite = al_load_bitmap("sprites/inimigos/toten.png");
	toten->frame_atual = 0;
	toten->num_frames = 1;
	toten->largura_frame = 128;
	toten->altura_frame = 256;

	toten->borda_x = 80;
	toten->borda_y = 250;
}



void desenha_toten(struct skin *toten)
{
	if(toten->x > LARGURA_T)
		toten->x = 5;
	else if(toten->x < 0)
		toten->x = LARGURA_T - 5;

	if(toten->y > ALTURA_T)
		toten->y = 5;
	else if(toten->y < 0)
		toten->y = ALTURA_T;

	al_draw_bitmap_region(toten->sprite, 
						  toten->frame_atual * toten->largura_frame, 0,
						  toten->largura_frame, toten->altura_frame, 
						  toten->x, toten->y, 0);
}



void destroi_inimigo(struct skin *i)
{
	al_destroy_bitmap(i->sprite);
	i->sprite = NULL;
}

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "nave.h"
#include "mapa.h"
#include "inimigos.h"


int main()
{
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();

	int sair = 0;
	int fase = 0;
	char especial = 0;
	int teclas[5] = {0, 0, 0, 0, 0};	

	ALLEGRO_FONT *fonte = NULL;
	fonte = al_load_font("./sprites/fonte.ttf", 13, 0);
	
	/*Estruturas fundamentais. */

	struct plano fundo[NUM_PLANOS][NUM_ESTRELAS];
	inicia_fundo(fundo);	
	
	struct especial melhora_tiro;
	inicia_especial(&melhora_tiro);

	struct nave tucano;
	inicia_nave(&tucano);

	/*Fase 0. */
	struct skin toten;
	inicia_toten(&toten);


	/*Inimigos fase 1 */

	struct skin barto;
	inicia_barto(&barto);

	struct skin lomeu;
	inicia_lomeu(&lomeu);

	struct skin spin;
	inicia_spin(&spin);

	struct skin chefao_f1;
	inicia_chefao(&chefao_f1);

	/* Inimigos fase 2 */

	struct skin peixoto;
	inicia_peixoto(&peixoto);

	struct skin paladino;
	inicia_paladino(&paladino);

	struct skin loor;
	inicia_loor(&loor);

	struct skin gris;
	inicia_gris(&gris);

	struct skin chefao_f2;
	inicia_chefao_f2(&chefao_f2);

	/*Inimigos fase 3. */

	struct skin cf;
	inicia_cf(&cf);	



	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
	ALLEGRO_DISPLAY *janela = al_create_display(LARGURA_T, ALTURA_T);
	ALLEGRO_EVENT evento;


	/* Captura de eventos. */
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());	
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));	
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));		
	

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);	
	while(! sair) {

		al_wait_for_event(fila_eventos, &evento);

		if(evento.type == ALLEGRO_EVENT_TIMER) {

			desenha_fundo(fundo, fase);
			
			/*Fim de jogo. */	
			if(tucano.vida <= 0) {
				fase = 4;
			}			

			/*Passagens de fases. */

			if(chefao_f1.vida <= 0 && tucano.vida > 0)
				fase = 2;
			
			if(chefao_f2.vida <= 0 && tucano.vida > 0)
				fase = 3;

			if(cf.vida <= 0 && tucano.vida > 0)
				fase = 5;
		
			/*Inicio de jogo. */
			if(fase == 0) {

				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2, 
				(ALTURA_T - 550) - al_get_font_ascent(fonte) / 2, 
				ALLEGRO_ALIGN_CENTRE, "INICIO DE JOGO!");	

				al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_T / 2 + 1, 
				(ALTURA_T - 550) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "INICIO DE JOGO!");	


				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "DESTRUA O TOTEM PARA INICIAR O JOGO!");	

				al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "DESTRUA O TOTEM PARA INICIAR O JOGO!");	

				desenha_toten(&toten);
				colisao_bala(tucano.arma, &toten);			
				
				if(toten.vida <= 0)
					fase = 1;
			}
					
			/*Fases */

			if(fase == 1) {
			
				if(barto.vida > 0) {

					desenha_barto(&barto);
					desenha_bala_inimigos(barto.arma, 1);
					colisao_bala(tucano.arma, &barto);			
					colisao_bala_inimigos(barto.arma, &tucano);			
					colisao_nave(&tucano, &barto);
				}

				if(lomeu.vida > 0) {

					desenha_lomeu(&lomeu);
					desenha_bala_inimigos(lomeu.arma, 1);
					colisao_bala(tucano.arma, &lomeu);
					colisao_bala_inimigos(lomeu.arma, &tucano);			
					colisao_nave(&tucano, &lomeu);
				}

				if(spin.vida > 0) {
		
					desenha_spin(&spin);
					desenha_bala_inimigos(spin.arma, 1);
					colisao_bala(tucano.arma, &spin);
					colisao_bala_inimigos(spin.arma, &tucano);			
					colisao_nave(&tucano, &spin);
				}

				if(barto.vida == 0 && lomeu.vida == 0 && spin.vida == 0) {

					desenha_chefao(&chefao_f1);
					desenha_bala_inimigos(chefao_f1.arma, 2);
					colisao_bala(tucano.arma, &chefao_f1);
					colisao_bala_inimigos(chefao_f1.arma, &tucano);			
					colisao_nave(&tucano, &chefao_f1);
				}
			}
			
			if(fase == 2) {
			
				if(especial == 0) {
					desenha_especial(&melhora_tiro);
					especial = pega_especial(&tucano, &melhora_tiro);
				}

				if(peixoto.vida > 0) {
					
					desenha_peixoto(&peixoto);
					desenha_bala_inimigos(peixoto.arma, 1);
					colisao_bala(tucano.arma, &peixoto);
					colisao_bala_inimigos(peixoto.arma, &tucano);			
					colisao_nave(&tucano, &peixoto);
				}

				if(paladino.vida > 0) {

					desenha_paladino(&paladino);
					desenha_bala_inimigos(paladino.arma, 1);
					colisao_bala(tucano.arma, &paladino);
					colisao_bala_inimigos(paladino.arma, &tucano);			
					colisao_nave(&tucano, &paladino);
				}

				if(loor.vida > 0) {

					desenha_loor(&loor);
					desenha_bala_inimigos(loor.arma, 1);
					colisao_bala(tucano.arma, &loor);
					colisao_bala_inimigos(loor.arma, &tucano);			
					colisao_nave(&tucano, &loor);
				}
				
				if(gris.vida > 0 && peixoto.vida == 0 && paladino.vida == 0 &&
				loor.vida < 50) {
					
					desenha_gris(&gris);	
					desenha_bala_inimigos(gris.arma, 2);
					colisao_bala(tucano.arma, &gris);
					colisao_bala_inimigos(gris.arma, &tucano);			
					colisao_nave(&tucano, &gris);
				}

				if(gris.vida <= 0) {

					desenha_chefao_f2(&chefao_f2);
					desenha_bala_inimigos(chefao_f2.arma, 2);
					colisao_bala(tucano.arma, &chefao_f2);
					colisao_bala_inimigos(chefao_f2.arma, &tucano);			
					colisao_nave(&tucano, &chefao_f2);
				}

			}
			
			if(fase == 3) {
				
				desenha_cf(&cf);
				desenha_bala_inimigos(cf.arma, 3);
				colisao_bala(tucano.arma, &cf);
				colisao_bala_inimigos(cf.arma, &tucano);			
				colisao_nave(&tucano, &cf);
			} 

			/* Fim de jogo.*/
			if(fase == 4) {

				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "FOI DE BASE! ");	

				al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "FOI DE BASE!");	
			}
		
			/* Quando ganha o jogo. */
			if(fase == 5) {

				al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "VOCE GANHOU! PARABENS! ");	

				al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_T / 2 + 1, 
				(ALTURA_T - 300) - al_get_font_ascent(fonte) / 2 + 1, 
				ALLEGRO_ALIGN_CENTRE, "VOCE GANHOU! PARABENS! ");
		
				sair = 1;	
			}

			
			/*Atualiza posição da nave. */	
			desenha_nave(&tucano, teclas);
			desenha_bala(tucano.arma);	

			char vida_tucano[50];
			sprintf(vida_tucano, "VIDA: %d", tucano.vida);
			
			char fase_painel[50];
			if(fase == 4)
				sprintf(fase_painel, "FIM DE JOGO!");
			else
				sprintf(fase_painel, "FASE: %d", fase);

			/* Desenha o painel.  */
			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T - 1120, 
			(ALTURA_T - 580) - al_get_font_ascent(fonte) / 2, ALLEGRO_ALIGN_CENTRE,
			vida_tucano);	

			al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_T - 1000, 
			(ALTURA_T - 580) - al_get_font_ascent(fonte) / 2, ALLEGRO_ALIGN_CENTRE,
			fase_painel);	

			/* Atualização da tela. */
			al_flip_display();
    			al_clear_to_color(al_map_rgb(0,0,0));
		}          
		

		/*Controle de pressionamento das teclas. */	
		if(evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(evento.keyboard.keycode) {
			
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = 1;		
				break;
					
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = 1;
				break;
				
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = 1;
				break;
					
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = 1;
				break;

				case ALLEGRO_KEY_SPACE:
					teclas[ESPACO] = 1; 
					atira(tucano.arma, tucano.x, tucano.y);
				break;
			}
		}           
		else if (evento.type == ALLEGRO_EVENT_KEY_UP) {

			switch(evento.keyboard.keycode) {
			
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = 0;		
				break;
					
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = 0;
				break;
				
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = 0;
				break;
					
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = 0;
				break;
			} 
		}
		else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = 1;
		}
			
		atualiza_fundo(fundo);
		atualiza_nave(&tucano, teclas);
		
		if(fase == 4) {
			sair = atualiza_nave_fim_de_jogo(&tucano);
		}
		else if(fase == 5) {
			sair = atualiza_nave_ganha_jogo(&tucano);
		}

		if(fase == 1) {
			atualiza_barto(&barto);
			atualiza_lomeu(&lomeu);
			atualiza_spin(&spin);
			atualiza_chefao(&chefao_f1);
		}
		else if(fase == 2) {
			
			atualiza_peixoto(&peixoto);
			atualiza_paladino(&paladino);
			atualiza_gris(&gris);
			atualiza_chefao_f2(&chefao_f2);
		}
		else if(fase == 3) {
			
			atualiza_cf(&cf);
		}
		
		/* Responsável por aplicar a gravidade no jogo. */
		if(tucano.y < ALTURA_T - 50)
			tucano.y += (PESO_NAVE / MASSA_NAVE);
		else
			tucano.y = ALTURA_T - 50;

		/*Atualização das balas. */
		atualiza_bala(tucano.arma);

		atualiza_bala_inimigos(barto.arma);
		atualiza_bala_inimigos(lomeu.arma);
		atualiza_bala_inimigos(spin.arma);
		atualiza_bala_inimigos(chefao_f1.arma);
		
		atualiza_bala_inimigos(peixoto.arma);
		atualiza_bala_inimigos(paladino.arma);
		atualiza_bala_inimigos(loor.arma);
		atualiza_bala_inimigos(gris.arma);
		atualiza_bala_inimigos(chefao_f2.arma);
		
		atualiza_bala_inimigos(cf.arma);

	} /*Fim do laço principal. */

	
	/*Destrutores. */

	al_destroy_font(fonte);
	al_destroy_timer(timer);
	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);

	destroi_inimigo(&barto);
	destroi_inimigo(&lomeu);
	destroi_inimigo(&spin);
	destroi_inimigo(&chefao_f1);
	destroi_inimigo(&peixoto);
	destroi_inimigo(&paladino);
	destroi_inimigo(&loor);
	destroi_inimigo(&gris);
	destroi_inimigo(&chefao_f2);
	destroi_inimigo(&cf);

	return 0;
}

flags = -Wall -Wextra
allegro = $(shell pkg-config allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 --libs --cflags)
 
main: main.o mapa.o nave.o arma.o inimigos.o
	gcc $(flags) -o jogo main.o mapa.o nave.o arma.o inimigos.o $(allegro) -lm

main.o: main.c
	gcc -c $(flags) $(allegro) main.c

mapa.o: mapa.c mapa.h
	gcc -c $(flags) $(allegro) mapa.c

nave.o: nave.c nave.h
	gcc -c $(flags) $(allegro) nave.c

arma.o: arma.c arma.h
	gcc -c $(flags) $(allegro) arma.c

inimigos.o: inimigos.c inimigos.h
	gcc -c $(flags) $(allegro) inimigos.c -lm

clean:
	rm -f *.o *.gch jogo


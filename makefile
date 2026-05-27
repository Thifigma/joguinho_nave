flags = -Wall -Wextra
allegro = $(shell pkg-config allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 --libs --cflags)
 
main: main.o mapa.o nave.o arma.o inimigos.o
	gcc $(flags) -o jogo main.o mapa.o nave.o arma.o inimigos.o $(allegro) -lm

main.o: src/main.c
	gcc -c $(flags) $(allegro) src/main.c

mapa.o: src/mapa.c include/mapa.h
	gcc -c $(flags) $(allegro) src/mapa.c

nave.o: src/nave.c include/nave.h
	gcc -c $(flags) $(allegro) src/nave.c

arma.o: src/arma.c include/arma.h
	gcc -c $(flags) $(allegro) src/arma.c

inimigos.o: src/inimigos.c include/inimigos.h
	gcc -c $(flags) $(allegro) src/inimigos.c -lm

clean:
	rm -f *.o *.gch jogo


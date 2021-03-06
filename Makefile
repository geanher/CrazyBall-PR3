
#g++ -c main.cpp crazyball.cpp -I ~/Descargas/Aleph-w 


#g++ main.o crazyball.o -o crazyball -L ~/Descargas/Aleph-w -lAleph-w -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

LIBS = -lAleph -lc -lm -lgsl -lgslcblas -lgmp -lmpfr -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

programa: main.o crazyball.o
	g++ main.o crazyball.o -o crazyball -L ~/Descargas/Aleph-w $(LIBS)
    
#lAleph-w -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp CrazyBall.h
	g++ -c main.cpp -I ~/Descargas/Aleph-w 

crazyball.o: crazyball.cpp CrazyBall.h
	g++ -c crazyball.cpp -I ~/Descargas/Aleph-w 

clean:
	rm -f ~*.o

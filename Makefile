map_file: main.cpp square.cpp shape.cpp Ishape.cpp Tshape.cpp Lshape.cpp
	g++ main.cpp square.cpp shape.cpp Ishape.cpp Tshape.cpp Lshape.cpp -o tetris -lncurses -Wall -Werror

clean:
	rm -f tetris *~
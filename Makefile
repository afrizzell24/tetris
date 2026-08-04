map_file: main.cpp square.cpp shape.cpp Ishape.cpp Tshape.cpp Lshape.cpp
	g++ -g -DNCURSES_STATIC -IC:/msys64/ucrt64/include/ncurses main.cpp square.cpp shape.cpp Ishape.cpp Tshape.cpp Lshape.cpp -o tetris -lncurses -Wall -Werror

clean:
	rm -f tetris *~
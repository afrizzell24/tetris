tetris: src/main.cpp src/shapes/square.cpp src/shape.cpp src/shapes/Ishape.cpp src/shapes/Tshape.cpp src/shapes/Lshape.cpp
	g++ -g -DNCURSES_STATIC -IC:/msys64/ucrt64/include/ncurses \
	-Iheaders \
	src/main.cpp src/shapes/square.cpp src/shape.cpp src/shapes/Ishape.cpp src/shapes/Tshape.cpp src/shapes/Lshape.cpp -o tetris \
	-lncurses -Wall -Werror

clean:
	rm -f tetris *~
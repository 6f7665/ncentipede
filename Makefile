GXX=clang++

all: ncentipede

ncentipede: main.cpp
	$(GXX) -std=c++17 -lncursesw main.cpp -o ncentipede

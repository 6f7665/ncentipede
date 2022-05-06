GXX=clang++

all: ncaterpillar

ncaterpillar: main.cpp
	$(GXX) -std=c++17 -lncurses main.cpp -o ncaterpillar

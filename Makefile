
CXX=clang++
VERSION=$(shell $(CXX) -dumpversion)
FLAGS=-O3 -mavx -msse4.2 -mtune=skylake -g
all:
	mkdir -p bin 
	$(CXX) -DCOMPILER="\"$(CXX)\"" -DVERSION="\"$(VERSION)\"" -DFLAGS="\"$(FLAGS)\"" -o bin/fastkv $(FLAGS) -lc -lpthread -ldl $(wildcard *.cpp)

clean:
	rm -rf bin 

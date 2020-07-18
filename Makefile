CC=g++
CXXFLAGS=-std=c++11 -g
LDFLAGS=-g

all: encode decode

encode: HuffmanNode.o HuffmanTree.o

decode: HuffmanNode.o HuffmanTree.o

HuffmanTree.o: HuffmanNode.h HuffmanTree.h

HuffmanNode.o: HuffmanNode.h

clean:
	rm -f encode decode *.o
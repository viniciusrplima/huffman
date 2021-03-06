
OBJS = obj/huffman.o obj/bitstream.o obj/main.o

bin/huffman: $(OBJS)
	gcc $(OBJS) -o bin/huffman -lstdc++

obj/huffman.o: huffman.h huffman.cpp
	gcc -c -Wall huffman.cpp -o obj/huffman.o

obj/bitstream.o: bitstream.h bitstream.cpp
	gcc -c -Wall bitstream.cpp -o obj/bitstream.o

obj/main.o: main.cpp
	gcc -c -Wall main.cpp -o obj/main.o

clean:
	rm bin/huffman $(OBJS)

build: 
	mkdir obj bin
	make

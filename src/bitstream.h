/*
 *
 * Bitstream.h
 *
 * 29 / 03 / 2020
 * by Vinicius Rodrigues
 *
*/

#include <fstream>

class OutBitstream {

public: 
	OutBitstream(std::ofstream*);

	void putc(int, int first = 7);
	void put(bool);
	void close();

	~OutBitstream();

private:

	std::ofstream *file;
	int length;
	char c;
};

class InBitstream {

public: 

	InBitstream(std::ifstream*);

	int getc(int size = 8);
	bool get();
	bool eof();

	~InBitstream();

private:

	std::ifstream* file;
	char c;
	int length;
};


/*

   Bitstream.hpp

   18 / 03 / 2020
   by Vinicius Rodrigues

*/

#include "bitstream.h"


OutBitstream::OutBitstream(std::ofstream *file) {

	this->file = file;
	c = 0;
	length = 0;
}

void OutBitstream::putc(int c, int first) {

	for(int i = first; i >= 0; i--)
	{
		bool b = c & 1 << i;
		put(b);
	}
}

void OutBitstream::put(bool b) {

	length++;
	c = c << 1;
	c |= b ? 1 : 0;

	if(length == 8)
	{
		file -> put(c);
		length = 0;
		c = 0;
	}
}

void OutBitstream::close() {

	if(length > 0)
	{
		int offset = 8 - length;
		c = c << offset;
		file -> put(c);
	}
}

OutBitstream::~OutBitstream() {}





InBitstream::InBitstream(std::ifstream *file) {
	this->file = file;
	c = 0;
	length = 0;
}

int InBitstream::getc(int size) {
	int c = 0;
	while(size > 0)	{
		c = c << 1;
		c |= get() ? 1 : 0;
		size--;
	}
	return c;
}

bool InBitstream::get() {
	if(length > 0) {
		length--;
		return c & 1 << length;
	}
	else {
		length = 8;
		file -> get(c);
		return get();
	}
}

bool InBitstream::eof() {
	return file->eof();
}

InBitstream::~InBitstream() {}



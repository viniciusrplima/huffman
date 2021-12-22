/*
 * huffman.h
 *
 * 29 de Março de 2020
 * by Vinicius Rodrigues
 *
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>
#include <ctime>

#include "bitstream.h"

struct NODE;

float getFileSizeKB(std::string);
NODE* makeNode(int, NODE*, NODE*);
NODE* makeLeaf(int, char);
std::vector<NODE*> getLeafQueue(std::ifstream&);
NODE* makeCharTree(std::ifstream&);
void mapCodeSet(NODE*, std::map<char, std::string>&, std::string);
void writeToken(OutBitstream*, char, std::string);
void writeHead(OutBitstream*, std::map<char, std::string>);
void writeBody(std::ifstream&, OutBitstream*, std::map<char, std::string>);
void compressFile(const std::string, const std::string);
void readHead(InBitstream*, std::map<std::string, char>&);
void parseBody(InBitstream*, std::map<std::string, char>, std::ofstream&);
void decompressFile(const std::string, const std::string);



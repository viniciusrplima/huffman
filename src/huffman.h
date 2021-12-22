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

class Huffman {

public:
    static void compressFile(const std::string, const std::string);
    static void decompressFile(const std::string, const std::string);
    static float getFileSizeKB(std::string);

private:

    static NODE* makeNode(int, NODE*, NODE*);
    static NODE* makeLeaf(int, char);
    static std::vector<NODE*> getLeafQueue(std::ifstream&);
    static NODE* makeCharTree(std::ifstream&);
    static void mapCodeSet(NODE*, std::map<char, std::string>&, std::string);
    static void writeToken(OutBitstream*, char, std::string);
    static void writeHead(OutBitstream*, std::map<char, std::string>);
    static void writeBody(std::ifstream&, OutBitstream*, std::map<char, std::string>);
    static void readHead(InBitstream*, std::map<std::string, char>&);
    static void parseBody(InBitstream*, std::map<std::string, char>, std::ofstream&);

};





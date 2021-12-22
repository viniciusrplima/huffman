/*

	Huffman Algorithm	


	by Vinicius Rodrigues
	25 de Fevereiro de 2020



 */


#include "huffman.h"

struct NODE
{
	char value;
	int priority;
	bool leaf;
	NODE *child0, *child1;
};

float Huffman::getFileSizeKB(std::string filepath)
{
	std::ifstream file(filepath, std::ios::ate);
	float size = (float) file.tellg() / 1000.0f;
	file.close();
	return size;
}

// Make an Internal Node of Tree
NODE* Huffman::makeNode(int priority, NODE* child0, NODE* child1)
{
	NODE* node = new NODE();
	node -> priority = priority;
	node -> child0 = child0;
	node -> child1 = child1;
	node -> leaf = false;
	
	return node;
}

// Make a Node with Value, Final point to a Branch
NODE* Huffman::makeLeaf(int priority, char value)
{
	NODE* node = new NODE();
	node -> priority = priority;
	node -> value = value;
	node -> leaf = true;

	return node;
}

// Create the Priority Node Queue
std::vector<NODE*> Huffman::getLeafQueue(std::ifstream &file)
{
	std::map<char, int> occurs;
	std::vector<char> orderedKeys;
	std::vector<NODE*> leafQueue;
	
	char c;
	while(file.get(c) and c != EOF)
		occurs[c]++;
	
	for(auto occur : occurs)
		orderedKeys.push_back(occur.first);

	std::sort(orderedKeys.begin(), orderedKeys.end(), [&occurs](char a, char b) {
														  return occurs[a] < occurs[b];
													  });
	
	for(auto key : orderedKeys)
		leafQueue.push_back(makeLeaf(occurs[key], key));
	
	return leafQueue;
}

// Create the Huffman tree
NODE* Huffman::makeCharTree(std::ifstream &file)
{
	auto leafQueue = getLeafQueue(file);

	while(leafQueue.size() > 1)
	{
		NODE *left = leafQueue[0];
		NODE *right = leafQueue[1];
		leafQueue[0] = leafQueue.back();
		leafQueue.pop_back();
		leafQueue[1] = leafQueue.back();
		leafQueue.pop_back();

		int priority = left->priority +  right->priority;
		leafQueue.push_back(makeNode(priority, left, right));

		std::sort(leafQueue.begin(), leafQueue.end(), [](NODE* a, NODE* b) {
														  return a -> priority < b -> priority;
		});
	}
	
	return leafQueue.front();
}

// Map the Codes
void Huffman::mapCodeSet(NODE* node, std::map<char, std::string> &codeset, std::string code)
{
	if(node->leaf)
	{
		codeset[node->value] = code;
	}
	else
	{
		mapCodeSet(node->child0, codeset, code + "0");
		mapCodeSet(node->child1, codeset, code + "1");
	}
}

void Huffman::writeToken(OutBitstream *out, char c, std::string code)
{
	out->putc(c);

	char range = code.length()-1;
	out->putc(range, 4); // the first five digits
	
	int iCode = std::stoi(code, 0, 2);
	out->putc(iCode, range);

}

// Append tree to beginning of the compressed file
void Huffman::writeHead(OutBitstream *out, std::map<char, std::string> codeset)
{
	char size = codeset.size();
	out->putc(size);

	for(auto token : codeset)
		writeToken(out, token.first, token.second);
}

void Huffman::writeBody(std::ifstream &in, OutBitstream *out, std::map<char, std::string> codeset)
{
    in.clear();
    in.seekg(0, in.beg);
    
    char c = 0;
    while(in.get(c) and c != EOF)
    {
        char size = codeset[c].length();
        int code = std::stoi(codeset[c], 0, 2);
        out -> putc(code, size-1);
	}
}

void Huffman::compressFile(const std::string in, const std::string out)
{
	std::ifstream file(in);
	std::ofstream compressed(out, std::ios::binary);

	NODE* treeHead = makeCharTree(file);
	std::map<char, std::string> codeset;
	mapCodeSet(treeHead, codeset, "");

/*	for(auto token : codeset)
	std::cout << token.first << " : " << token.second << std::endl;
*/
	
	OutBitstream oStream(&compressed);
	
	writeHead(&oStream, codeset);
	writeBody(file, &oStream, codeset);

	oStream.close();
	compressed.close();
	file.close();
}

void Huffman::readHead(InBitstream *in, std::map<std::string, char> &codeset)
{
	char size = in->getc();
        
	while(size > 0)
	{
		char value = in->getc();

		char codeSize = in->getc(5) + 1;
		char offset = 32 - codeSize;
		std::string code = std::bitset<32>(in->getc(codeSize)).to_string().substr(offset, codeSize);
        
		codeset[code] = value;

		std::cout << value << ' ' << std::setw(2) << (int)codeSize << ' '
		<< code
		<< std::endl;
		
		size--;
	}
}

void Huffman::parseBody(InBitstream *in, std::map<std::string, char> codeset, std::ofstream &out)
{
	std::string code = "";
	while(!in->eof())
	{
		code += in->get() ? '1' : '0';

		if(codeset.count(code) == 1)
		{
			out.put(codeset[code]);
			code = "";
		}

		if(code.length() > 32)
		{
			std::cout << "error: exceded code length" << std::endl;
			break;
		}
	}
}

void Huffman::decompressFile(const std::string in, const std::string out)
{
	std::ifstream file(in);
	std::ofstream decompress(out);
	InBitstream iStream(&file);
	std::map<std::string, char> codeset;
	
	readHead(&iStream, codeset);

	parseBody(&iStream, codeset, decompress);

	file.close();
	decompress.close();
}

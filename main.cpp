

#include <iostream>

#include "huffman.hpp"


int main(int argc, char** argv)
{
	if(argc != 4)
	{
		std::cout << std::endl;
		std::cout << "Error: invalid number of parameters" << std::endl;
		std::cout << "Valid format: huffman <action> <input-file> <output-file>" << std::endl;
		return 1;
	}

	std::string action = argv[1];
	std::string inputFile = argv[2];
	std::string outputFile = argv[3];

	if(action == "com")
	{
		float inputSize =  getFileSizeKB(inputFile);
	
		int initTime = std::clock();
		compressFile(inputFile, outputFile);
		int elapsedTime = std::clock() - initTime;
		int compressTime = (float) elapsedTime / CLOCKS_PER_SEC * 1000.0f;

		float outputSize = getFileSizeKB(outputFile);

		float compression = (float) (inputSize - outputSize) / inputSize * 100.0f;
       
		std::cout << std::fixed;
		std::cout << std::setprecision(3);
		
		std::cout << std::endl;
		std::cout << "input: " << inputSize << " KB" << std::endl;
		std::cout << "output: " << outputSize << " KB" << std::endl;
		std::cout << "compression: " << compression << "%" << std::endl;
		std::cout << "time: " << compressTime << " ms" << std::endl;
	}
	else if(action == "decom")
	{
		float inputSize =  getFileSizeKB(inputFile);
	
		int initTime = std::clock();
		decompressFile(inputFile, outputFile);
		int elapsedTime = std::clock() - initTime;
		int decompressTime = (float) elapsedTime / CLOCKS_PER_SEC * 1000.0f;

		float outputSize = getFileSizeKB(outputFile);

		std::cout << std::fixed;
		std::cout << std::setprecision(3);
		
		std::cout << std::endl;
		std::cout << "input: " << inputSize << " KB" << std::endl;
		std::cout << "output: " << outputSize << " KB" << std::endl;
		std::cout << "time: " << decompressTime << " ms" << std::endl;		
	}
	else
	{
		std::cout << std::endl;
		std::cout << "Error: invalid action\n";
		std::cout << "Valid actions: \n";
		std::cout << "com   - compression\n";
		std::cout << "decom - decompression\n";

		return 1;
	}
	
	return 0;
}

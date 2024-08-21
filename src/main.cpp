#include <iostream>
#include <fstream>
using namespace std;

string readFile(string filePath)
{
    ifstream inputFile(filePath);

    string fileString;
    while (getline(inputFile, fileString))
    inputFile.close();

    return fileString;
}

int main()
{
    string plaintext = readFile("./plaintext/sample.txt");
    std::cout << "Plaintext:\n" << plaintext << "\n\n";

    string key = readFile("./keys/sample.txt");
    std::cout << "Key:\n" << key;

    string ciphertext = plaintext;
    ofstream outputFile("./ciphertext/sample.txt");
    outputFile << ciphertext;

    return 0;
}
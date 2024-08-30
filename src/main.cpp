#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "cipher.h"

/**
 * @brief Read all the content of a text file. 
 * 
 * @param filePath The filepath of the text file to read. 
 * @return std::string The text contained in the file. 
 */
std::string readFile(std::string filePath)
{
    std::ifstream inputFile(filePath);

    std::string fileString;
    while (getline(inputFile, fileString))
    inputFile.close();

    return fileString;
}

int main(int argc, char *argv[])
{
    // Raise an error if the user did not pass the necessary arguments.
    if (argc < 3)
    {
        throw std::invalid_argument("Please pass in an operation(\"encrypt\" or \"decrypt\") and file name.");
    }
    
    std::string fileName = (std::string)argv[2];
    std::string key = readFile("./keys/" + fileName);
    VigenereCipher cipher(key);

    if ((std::string)argv[1] == "encrypt") {
        std::cout << "Hello world!";
    }

    std::string plaintext = readFile("./plaintext/" + fileName);

    std::string ciphertext = cipher.encrypt(plaintext);
    std::ofstream ciphertextFile("./ciphertext/" + fileName);
    ciphertextFile << ciphertext;

    // Print results
    std::cout << "Successfully encrypted." << "\n\n";
    std::cout << "Plaintext: " << plaintext << '\n';
    std::cout << "Key: " << key << '\n';
    std::cout << "Ciphertext: " << ciphertext;

    return EXIT_SUCCESS;
}
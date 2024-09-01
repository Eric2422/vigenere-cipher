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
    {
    }
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
    std::filesystem::path plaintextFile("./plaintext/" + fileName);

    std::string plaintextFilePath = "./plaintext/" + fileName;
    std::string ciphertextFilePath = "./plaintext/" + fileName;

    // Create a cipher out of the key
    std::string key = readFile("./keys/" + fileName);
    VigenereCipher cipher(key);

    if ((std::string)argv[1] == "encrypt")
    {
        std::string plaintext = readFile(plaintextFilePath);

        // Encrypt plaintext, and write ciphertext into the file.
        std::string ciphertext = cipher.encrypt(plaintext);
        std::ofstream ciphertextFile("./ciphertext/" + fileName);
        ciphertextFile << ciphertext;

        // Print results
        std::cout << "Successfully encrypted." << "\n\n";
        std::cout << "Plaintext: " << plaintext << '\n';
        std::cout << "Key: " << key << '\n';
        std::cout << "Ciphertext: " << ciphertext << '\n';
        // std::cout << cipher.decrypt(ciphertext) << '\n';
    }

    else if ((std::string)argv[1] == "decrypt")
    {
        std::string ciphertext = readFile("./ciphertext/" + fileName);

        // Decrypt ciphertext, and write plaintext into the file.
        std::string plaintext = cipher.decrypt(ciphertext);
        std::ofstream ciphertextFile("./plaintext/" + fileName);
        ciphertextFile << plaintext;

        // Print results
        std::cout << "Successfully decrypted." << "\n\n";
        std::cout << "Ciphertext: " << ciphertext << '\n';
        std::cout << "Key: " << key << '\n';
        std::cout << "Plaintext: " << plaintext << '\n';
    }

    else
    {
        throw std::invalid_argument("The second argument must be either \"encrypt\" or \"decrypt\".");
    }

    return EXIT_SUCCESS;
}
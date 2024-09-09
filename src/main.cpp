#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "cipher.h"
using namespace std;

/**
 * @brief Read all the content of a text file.
 *
 * @param filePath The filepath of the text file to read.
 * @return string The text contained in the file.
 */
string readFile(string filePath)
{
    ifstream inputFile(filePath);

    string fileString;
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
        throw invalid_argument("Please pass in an operation(\"encrypt\" or \"decrypt\") and file name.");
    }

    string fileName = (string)argv[2];
    filesystem::path inputFile;
    filesystem::path outputFile;

    // Set the input and output files based on the operation
    if (string(argv[1]) == "encrypt")
    {
        inputFile = "./plaintext/" + fileName;
        outputFile = "./ciphertext/" + fileName;
    }

    else if (string(argv[1]) == "decrypt")
    {
        inputFile = "./ciphertext/" + fileName;
        outputFile = "./plaintext/" + fileName;
    }

    // Raise an error if an invalid argument is passed in.
    else
    {
        throw invalid_argument("The second argument must be either \"encrypt\" or \"decrypt\".");
    }

    string plaintextFilePath = "./plaintext/" + fileName;
    string ciphertextFilePath = "./ciphertext/" + fileName;

    // Create a cipher out of the key
    string key = readFile("./keys/" + fileName);
    VigenereCipher cipher(key);

    string inputText = readFile(inputFile.string());
    string outputText;

    // Encrypt plaintext
    if (string(argv[1]) == "encrypt")
    {
        outputText = cipher.encrypt(inputText);
    }

    // Decrypt ciphertext
    else
    {
        outputText = cipher.decrypt(inputText);
    }

    // Write the text to the corresponding output file
    ofstream(outputFile.string()) << outputText;

    cout << "Successfully " << argv[1] << "ed\n\n";
    cout << "Input from " << inputFile.string() << ":\n" << inputText << "\n\n";
    cout << "Key:\n" << key << "\n\n";
    cout << "Output to " << outputFile.string() << ":\n" << outputText;

    return EXIT_SUCCESS;
}
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
    filesystem::path plaintextFile("./plaintext/" + fileName);
    filesystem::path ciphertextFile("./ciphertext" + fileName);

    string plaintextFilePath = "./plaintext/" + fileName;
    string ciphertextFilePath = "./ciphertext/" + fileName;

    // Create a cipher out of the key
    // string key = readFile("./keys/" + fileName);
    // VigenereCipher cipher(key);

    char key = 10;

    // The number of non-control ASCII characters
    int modulus = (numeric_limits<char>::max());
    cout << "Modulus: " << modulus << "\n\n";

    for (int i=33; i<(numeric_limits<char>::max()); i++) {
        // Apply Vigenère's cipher, but prevent unprintable characters
        char ciphertext = (i + key) % modulus;

        cout << char(i) << " (" << i << ')' << " -> ";
        cout << ciphertext << " (" << int(ciphertext) << ')' << " -> ";

        char decrypted = (ciphertext - key) % modulus;
        cout << decrypted << " (" << int(decrypted) << ')' << '\n';
    }

    // if ((string)argv[1] == "encrypt")
    // {
    //     string plaintext = readFile(plaintextFilePath);

    //     // Encrypt plaintext, and write ciphertext into the file.
    //     string ciphertext = cipher.encrypt(plaintext);
    //     ofstream ciphertextFile("./ciphertext/" + fileName);
    //     ciphertextFile << ciphertext;

    //     // Print results
    //     cout << "Successfully encrypted." << "\n\n";
    //     cout << "Plaintext: " << plaintext << '\n';
    //     cout << "Key: " << key << '\n';
    //     cout << "Ciphertext: " << ciphertext << '\n';
    //     // cout << cipher.decrypt(ciphertext) << '\n';
    // }

    // else if ((string)argv[1] == "decrypt")
    // {
    //     string ciphertext = readFile("./ciphertext/" + fileName);

    //     // Decrypt ciphertext, and write plaintext into the file.
    //     string plaintext = cipher.decrypt(ciphertext);
    //     ofstream ciphertextFile("./plaintext/" + fileName);
    //     ciphertextFile << plaintext;

    //     // Print results
    //     cout << "Successfully decrypted." << "\n\n";
    //     cout << "Ciphertext: " << ciphertext << '\n';
    //     cout << "Key: " << key << '\n';
    //     cout << "Plaintext: " << plaintext << '\n';
    // }

    // else
    // {
    //     throw invalid_argument("The second argument must be either \"encrypt\" or \"decrypt\".");
    // }

    return EXIT_SUCCESS;
}
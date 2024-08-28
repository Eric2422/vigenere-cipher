#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

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

    // Raise an error if the plaintext and key differ in length.
    int plaintextSize = std::filesystem::file_size("./plaintext/" + fileName);
    int keySize = std::filesystem::file_size("./keys/" + fileName);
    if (plaintextSize != keySize)
    {
        throw std::invalid_argument("The input and key must be of the same length.");
    }

    std::ifstream plaintextFile("./plaintext/" + fileName);
    std::ifstream keyFile("./keys/" + fileName);
    std::ofstream ciphertextFile("./ciphertext/" + fileName);

    std::string plaintext;
    std::string key;
    std::string ciphertext;

    // Read each plaintext letter, encrypt it with the key, and write it to ciphertext
    for (int i = 0; i < plaintextSize; i++)
    {
        char plaintextChar = plaintextFile.get();
        plaintext += plaintextChar;

        char keyChar = keyFile.get();
        key += keyChar;

        // Apply Vigenère's cipher.
        // Subtract 32 from the modulus to account for non-printable ASCII characters,
        // and add 32 to the result to prevent non-printable ASCII characters.
        char ciphertextChar = encryptChar(plaintextChar, keyChar);
        ciphertext += ciphertextChar;
    }
    ciphertextFile << ciphertext;

    plaintextFile.close();
    keyFile.close();
    ciphertextFile.close();

    // Print results
    std::cout << "Successfully encrypted." << "\n\n";
    std::cout << "Plaintext: " << plaintext << '\n';
    std::cout << "Key: " << key << '\n';
    std::cout << "Ciphertext: " << ciphertext;

    return EXIT_SUCCESS;
}
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int __argc, char *__argv[])
{
    // Raise an error if the user did pass the necessary arguments.
    if (__argc < 2)
    {
        throw std::invalid_argument("Please pass in a file name.");
    }

    std::string fileName = (std::string)__argv[1];

    // Raise an error if the plaintext and key differ in length.
    int plaintextSize = std::filesystem::file_size("./plaintext/" + fileName);
    int keySize = std::filesystem::file_size("./keys/" + fileName);
    if (plaintextSize != keySize)
    {
        throw std::logic_error("The plaintext and key must be of the same length.");
    }

    std::ifstream plaintextFile("./plaintext/" + fileName);
    std::ifstream keyFile("./keys/" + fileName);
    std::ofstream ciphertextFile("./ciphertext/" + fileName);

    // Read each plaintextletter, encrypt with the key, and write it to ciphertext
    for (int i = 0; i < plaintextSize; i++)
    {
        char plaintextChar = plaintextFile.get();
        char keyChar = keyFile.get();

        int encryptedAscii = (int)plaintextChar + (int)keyChar % std::numeric_limits<char>::max();
        std::cout << encryptedAscii << ' ';

        ciphertextFile << (char)(encryptedAscii);
    }

    plaintextFile.close();
    keyFile.close();
    ciphertextFile.close();

    return EXIT_SUCCESS;
}
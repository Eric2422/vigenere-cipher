#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int, char *[])
{
    // Raise an error if the user did not pass the necessary arguments.
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
        throw std::invalid_argument("The plaintext and key must be of the same length.");
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
        char ciphertextChar = (char)(((int)plaintextChar + (int)keyChar) % (std::numeric_limits<char>::max() - 32) + 32);
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
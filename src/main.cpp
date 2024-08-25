#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

/**
 * @brief Encrypt a single character using Vigenère's cipher and a character as the key.
 *
 * Uses 7-bit ASCII values to encrypt the character.
 * Avoids producing a ASCII control character.
 *
 * @param plaintext A single character to use as the plaintext.
 * @param key A single character to use as the key.
 * @return char A ciphertext character produced using the key and plaintext.
 *         Will not be a control character.
 */
char encryptChar(char plaintext, char key)
{
    // Apply Vigenère's cipher.
    // Subtract 32 from the modulus to account for non-printable ASCII characters,
    // and add 32 to the result to prevent non-printable ASCII characters.
    return (char)(((int)plaintext + (int)key) % (std::numeric_limits<char>::max() - 32) + 32);
}

/**
 * @brief Decrypt a single character using Vigenère's cipher and a character as the key.
 *
 * Uses 7-bit ASCII values to decrypt the character.
 * Avoids producing a ASCII control character.
 *
 * @param ciphertext A single character to use as the ciphertext.
 * @param key A single character to use as the key.
 * @return char A plaintext character produced using the key and plaintext.
 *         Will not be a control character.
 */
char decryptChar(char ciphertext, char key)
{
    // Undo Vigenère's cipher.
    // Subtract 32 from the modulus to account for non-printable ASCII characters,
    // and subtract 32 from the result to prevent non-printable ASCII characters.
    return (char)(((int)ciphertext - (int)key) % (std::numeric_limits<char>::max() - 32) - 32);
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
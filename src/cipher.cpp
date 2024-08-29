#include "cipher.h"

VigenereCipher::VigenereCipher(std::string key)
{
    this->key = key;
};

bool VigenereCipher::isValidInput(std::string inputString)
{
    return sizeof(inputString) == sizeof(this->key);
}

std::string VigenereCipher::encrypt(std::string plaintext)
{
    if (!isValidInput(plaintext))
    {
        throw std::invalid_argument("The input and key must be of the same length.");
    }

    std::string ciphertext;
    for (int i = 0; i < sizeof(plaintext); i++)
    {
        int plaintextAscii = (int)plaintext[i];
        int keyAscii = (int)this->key[i];

        // Apply Vigenère's cipher.
        // Subtract 32 from the modulus to account for non-printable ASCII characters,
        // and add 32 to the result to prevent non-printable ASCII characters.
        ciphertext += (char)((plaintextAscii + keyAscii) % (std::numeric_limits<char>::max() - 32) + 32);
    }

    return ciphertext;
}

std::string VigenereCipher::decrypt(std::string ciphertext)
{
    if (!isValidInput(ciphertext))
    {
        throw std::invalid_argument("The input and key must be of the same length.");
    }

    std::string plaintext;
    for (int i = 0; i < sizeof(ciphertext); i++)
    {
        int ciphertextAscii = (int)ciphertext[i];
        int keyAscii = (int)this->key[i];

        // Undo Vigenère's cipher.
        // Subtract 32 from the modulus to account for non-printable ASCII characters,
        // and subtract 32 from the result to prevent non-printable ASCII characters.
        plaintext += (char)(((int)ciphertextAscii - (int)keyAscii) % (std::numeric_limits<char>::max() - 32) - 32);
    }

    return plaintext;
}

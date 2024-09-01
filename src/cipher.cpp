#include "cipher.h"

VigenereCipher::VigenereCipher(std::string key)
{
    this->key = key;
};

bool VigenereCipher::isValidInput(std::string inputString)
{
    std::cout << "Input string size: " << sizeof(inputString) << '\n';
    std::cout << "Key size: " << sizeof(key) << '\n';

    return sizeof(inputString) == sizeof(this->key);
}

std::string VigenereCipher::encrypt(std::string plaintext)
{
    return convertString(plaintext, 1);
}

std::string VigenereCipher::decrypt(std::string ciphertext)
{
    return convertString(ciphertext, -1);
}

std::string VigenereCipher::convertString(std::string input, int shift)
{
    if (!isValidInput(input))
    {
        throw std::invalid_argument("The input and key must be of the same length.");
    }

    // Loop through each character in the input
    std::string output = "";
    for (int i = 0; i < sizeof(input); i++)
    {
        int inputAscii = (int)input[i];

        // If the char is a newline(10) or carriage return(13), skip.
        if (inputAscii == 10 || inputAscii == 13)
        {
            output += inputAscii;
            continue;
        }

        // Apply the shift to the key
        int keyAscii = (int)this->key[i] * shift;

        // The number of non-control ASCII characters
        int modulus = (std::numeric_limits<char>::max() - 32);

        // Apply Vigenère's cipher, but prevent unprintable characters
        output += (char)((inputAscii + keyAscii) % modulus + (32 * shift));
    }

    return output;
}

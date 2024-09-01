#include "cipher.h"

VigenereCipher::VigenereCipher(std::string key)
{
    this->key = key;
};

bool VigenereCipher::isValidInput(std::string inputString)
{
    return inputString.size() == this->key.size();
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
        std::string errorMessage = "The input and key must be of the same length, ";
        errorMessage += "but the input string is of size " + std::to_string(input.size());
        errorMessage += ", while the key is of size " + std::to_string(key.size()) + ".";
        throw std::invalid_argument(errorMessage);
    }

    // Loop through each character in the input
    std::string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        int inputAscii = int(input[i]);
        // std::cout << "Input: " << input[i] << "(" << inputAscii << ")\n";

        // If the char is a newline(10) or carriage return(13), skip.
        if (inputAscii == 10 || inputAscii == 13)
        {
            output += inputAscii;
            continue;
        }

        // Apply the shift to the key
        int keyAscii = int(this->key[i]) * shift;
        // std::cout << "Key: " << key[i] << "(" << keyAscii << ")\n";

        // The number of non-control ASCII characters
        int modulus = (std::numeric_limits<char>::max() - 32);

        // Apply Vigenère's cipher, but prevent unprintable characters
        int outputAscii = (inputAscii + keyAscii) % modulus + (32 * shift);
        // std::cout << "Output: " << char(outputAscii) << "(" << outputAscii << ")\n\n";

        output += char(outputAscii);
    }

    return output;
}

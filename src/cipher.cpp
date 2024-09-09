#include "cipher.h"

VigenereCipher::VigenereCipher(string key)
{
    this->key = key;
};

bool VigenereCipher::isValidInput(string inputString)
{
    return inputString.size() == this->key.size();
}

string VigenereCipher::encrypt(string plaintext)
{
    return convertString(plaintext, 1);
}

string VigenereCipher::decrypt(string ciphertext)
{
    return convertString(ciphertext, -1);
}

int VigenereCipher::nonNegativeMod(int a, int b)
{
    int remainder;
    return ((remainder = a % b) >= 0) ? remainder : remainder + b;
}

string VigenereCipher::convertString(string input, int shiftDirection)
{
    if (!isValidInput(input))
    {
        string errorMessage = "The input and key must be of the same length, ";
        errorMessage += "but the input string is of size " + to_string(input.size());
        errorMessage += ", while the key is of size " + to_string(key.size()) + ".";
        throw invalid_argument(errorMessage);
    }

    // Loop through each character in the input
    string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        int inputAscii = int(input[i]);
        // cout << "Input: " << input[i] << "(" << inputAscii << ")\n";

        // If the char is not one of the printable characters(i.e. 32-126), skip it.
        if (inputAscii < 32 || inputAscii == 127)
        {
            output += inputAscii;
            continue;
        }

        // Apply the shiftDirection to the key
        int keyAscii = int(this->key[i]) * shiftDirection;
        // cout << "Key: " << key[i] << "(" << keyAscii << ")\n";

        // The number of non-control ASCII characters
        int modulus = numeric_limits<char>::max() - 32;

        // Apply Vigenère's cipher, but prevent unprintable characters
        int outputAscii = VigenereCipher::nonNegativeMod(inputAscii - 32 + keyAscii, modulus) + 32;
        // cout << "Output: " << char(outputAscii) << '(' << outputAscii << ")\n";

        output += char(outputAscii);
    }

    return output;
}

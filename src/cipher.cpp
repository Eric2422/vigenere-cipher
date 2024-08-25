#include <filesystem>
#include <iostream>

class VigenereCipher
{
    std::string key;

public:
    VigenereCipher(std::string key)
    {
        this->key = key;
    };
    
    /**
     * @brief Check whether the given string is the same size as the key.
     * 
     * Assumes both the key and input are in ASCII.
     * 
     * @param inputString An string to check the size of(i.e. a plaintext or ciphertext)
     * @return true If the given string is the same size as the key.
     * @return false If the given string differs in size from the key.
     */
    bool isValidInput(std::string inputString)
    {
        return sizeof(inputString) == sizeof(this->key);
    }

    /**
     * @brief Encrypt a plaintext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to encrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both plaintext and key are in ASCII.
     *
     * @param plaintext A string to use as the plaintext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return A ciphertext string produced using the plaintext and key.
     *         Will not be a control character.
     */
    std::string encrypt(std::string plaintext)
    {
        if (!isValidInput(plaintext)) {
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

    /**
     * @brief Decrypt a ciphertext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to decrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both ciphertext and key are in ASCII.
     *
     * @param ciphertext A string to use as the ciphertext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return A plaintext string produced using the key ciphertext and key.
     *         Will not be a control character.
     */
    std::string decrypt(std::string ciphertext)
    {
        if (!isValidInput(ciphertext)) {
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
};
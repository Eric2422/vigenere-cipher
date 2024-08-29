#include <filesystem>
#include <iostream>

class VigenereCipher
{
private:
    std::string key;

public:
    VigenereCipher(std::string key);

    /**
     * @brief Check whether the given string is the same size as the key.
     *
     * Assumes both the key and input are in ASCII.
     *
     * @param inputString An string to check the size of(i.e. a plaintext or ciphertext)
     * @return true If the given string is the same size as the key.
     * @return false If the given string differs in size from the key.
     */
    bool isValidInput(std::string inputString);

    /**
     * @brief Encrypt a plaintext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to encrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both plaintext and key are in ASCII.
     *
     * @param plaintext A string to use as the plaintext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return std::string A ciphertext string produced using the plaintext and key.
     *         Will not be a control character.
     */
    std::string encrypt(std::string plaintext);

    /**
     * @brief Decrypt a ciphertext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to decrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both ciphertext and key are in ASCII.
     *
     * @param ciphertext A string to use as the ciphertext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return std::string A plaintext string produced using the key ciphertext and key.
     *         Will not be a control character.
     */
    std::string decrypt(std::string ciphertext);
};
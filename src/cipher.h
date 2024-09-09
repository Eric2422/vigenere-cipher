#include <filesystem>
#include <iostream>
using namespace std;

class VigenereCipher
{
public:
    /**
     * @brief Construct a new Vigenere Cipher object.
     * 
     * @param key The string that serves as the key of the Vigenère cipher.
     */
    VigenereCipher(string key);

    /**
     * @brief Check whether the given string is the same size as the key.
     *
     * Assumes both the key and input are in ASCII.
     *
     * @param inputString An string to check the size of(i.e. a plaintext or ciphertext)
     * @return true If the given string is the same size as the key.
     * @return false If the given string differs in size from the key.
     */
    bool isValidInput(string inputString);

    /**
     * @brief Encrypt a plaintext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to encrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both plaintext and key are in ASCII.
     * Skips over new lines.
     *
     * @param plaintext A string to use as the plaintext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return string A ciphertext string produced using the plaintext and key.
     *         Will not be a control character.
     */
    string encrypt(string plaintext);

    /**
     * @brief Decrypt a ciphertext string using using this cipher's key.
     *
     * Uses 7-bit ASCII values to decrypt the character.
     * Avoids producing a ASCII control character.
     * Assumes both ciphertext and key are in ASCII.
     * Skips over new lines.
     *
     * @param ciphertext A string to use as the ciphertext.
     * @exception `plaintext` and `self->key` strings differ in length.
     * @return string A plaintext string produced using the key ciphertext and key.
     *         Will not be a control character.
     */
    string decrypt(string ciphertext);

private:
    string key;

    /**
     * @brief A modulo operation that does not return a negative value.
     * 
     * @param a The dividend of the operation.
     * @param b The modulus of the operation.
     * @return int The remainder resulting from the modulo operation.
     */
    static int nonNegativeMod(int a, int b);

    /**
     * @brief A private function to use for both encryption and decryption
     *
     * @param input The string to be encrypted or decrypted.
     * @param shift Integer with one of two values, 1 or -1.
     *              1 is encryption, and -1 is decryption.
     * @return string The string outputed by encryption or decryption
     */
    string convertString(string input, int shift);
};
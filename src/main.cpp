#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int, char *[])
{
    if (__argc < 2)
    {
        throw std::invalid_argument("Please pass in a file name.");
    }



    std::ifstream plaintextFile(std::strcat("./plaintext/", __argv[1]));
    std::ifstream keyFile(std::strcat("./keys/", __argv[1]));
    std::ifstream ciphertextFile(std::strcat("./ciphter/", __argv[1]));

    std::cout << std::filesystem::file_size(std::strcat("./plaintext/", __argv[1]));

    return EXIT_SUCCESS;
}
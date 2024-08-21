#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Create and read a file.
    ifstream InputFile("input.txt");

    string plaintext;

    while (getline(InputFile, plaintext))
    {
    }

    cout << plaintext;

    InputFile.close();

    return 0;
}
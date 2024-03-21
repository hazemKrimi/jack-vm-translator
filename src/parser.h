#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Parser
{
private:
    ifstream file;

public:
    Parser(string path)
    {
        file = ifstream(path);
    }

    void printFile()
    {
        string text;

        while (getline(file, text))
        {
            cout << text;
        }
    }
};

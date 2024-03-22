#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <cctype>

using namespace std;

class Parser
{
private:
    ifstream file;
    string vmCode;

    bool isEmptyLine(string text)
    {
        for (char c : text)
        {
            if (!isspace(c))
                return false;
        }

        return true;
    }

    void removeCommentsAndWhitespace()
    {
        string text;
        smatch matched;

        while (getline(file, text))
        {
            if (regex_search(text, matched, regex("^(.*)?(\\/\\/.*)")) || isEmptyLine(text))
            {
                if (!isEmptyLine(matched[1])) {
                    string command = matched[1];
                    vmCode.append(command + '\n');
                }
                continue;
            }
            else
            {
                vmCode.append(text + '\n');
            }
        }
    }

public:
    Parser(string path)
    {
        file = ifstream(path);

        removeCommentsAndWhitespace();
    }

    void printFile()
    {
        stringstream vmCodeStream(vmCode);
        string text;

        while (getline(vmCodeStream, text, '\n'))
        {
            cout << text << endl;
        }
    }
};

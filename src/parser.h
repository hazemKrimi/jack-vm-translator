#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <cctype>
#include <vector>

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
                if (!isEmptyLine(matched[1]))
                {
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

    vector<vector<string>> getCommands()
    {
        stringstream vmCodeStream(vmCode);
        string text;
        smatch matched;
        vector<vector<string>> tokens;

        while (getline(vmCodeStream, text, '\n'))
        {
            vector<string> matchedVector;

            if (regex_search(text, matched, regex("^(.*) (.*) (.*)")))
            {
                matchedVector.push_back(matched[1]);
                matchedVector.push_back(matched[2]);
                matchedVector.push_back(matched[3]);
            }
            else
            {
                matchedVector.push_back(text);
            }
            tokens.push_back(matchedVector);
        }

        return tokens;
    }

    void closeFile() {
        file.close();
    }
};

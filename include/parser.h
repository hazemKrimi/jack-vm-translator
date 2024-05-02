#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <cctype>
#include "types.h"
#include "utils.h"

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

                    trim(command);
                    vmCode.append(command + '\n');
                }
                continue;
            }
            else
            {
                trim(text);
                vmCode.append(text + '\n');
            }
        }
    }

    void closeFile()
    {
        file.close();
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
        vector<vector<string>> commands;

        while (getline(vmCodeStream, text, '\n'))
        {
            vector<string> matchedVector;

            if (regex_search(text, matched, regex("^(.*) (.*) (.*)")))
            {
                matchedVector.push_back(matched[1]);
                matchedVector.push_back(matched[2]);
                matchedVector.push_back(matched[3]);
            }
            else if (regex_search(text, matched, regex("^(.*) (.*)")))
            {
                matchedVector.push_back(matched[1]);
                matchedVector.push_back(matched[2]);
            }
            else if (regex_search(text, matched, regex("^(.*)")))
            {
                matchedVector.push_back(matched[1]);
            }
            commands.push_back(matchedVector);
        }

        return commands;
    }
};

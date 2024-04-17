#include <iostream>
#include <fstream>
#include <string>
#include "types.h"
#include "operations.h"
#include "memory.h"

using namespace std;

class Code
{
private:
    ofstream file;
    string filename;
    vector<vector<string>> commands;

public:
    Code(string path, vector<vector<string>> tokens)
    {
        size_t slashIndex = path.find_last_of('/');
        size_t dotIndex = path.find_last_of('.');

        if (slashIndex != string::npos && dotIndex != string::npos)
        {
            filename = path.substr(slashIndex + 1, dotIndex - slashIndex - 1);
        }

        file = ofstream(path);
        commands = tokens;
    }

    void translate()
    {
        for (const auto &vec : commands)
        {   
            if (vec.size() > 1)
            {
                if (vec[0] == "push")
                {
                    file << translatePush(filename, determineSegment(vec[1]), stoi(vec[2]));
                }
                if (vec[0] == "pop")
                {
                    file << translatePop(filename, determineSegment(vec[1]), stoi(vec[2]));
                }
            }

            if (vec.size() == 1)
            {
                if (vec[0] == "add")
                    cout << translateAdd();

                if (vec[0] == "sub")
                    cout << translateSub();

                if (vec[0] == "neg")
                    cout << translateNeg();
            }

            file << endl;
        }
    }

    void closeFile()
    {
        file.close();
    }
};

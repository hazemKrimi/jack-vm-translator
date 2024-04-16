#include <iostream>
#include <fstream>
#include <string>
#include "types.h"
#include "memory.h"
#include "arithmetic.h"

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
                else
                {
                    file << translatePop(filename, determineSegment(vec[1]), stoi(vec[2]));
                }
            }

            if (vec.size() == 1)
            {
                int op = determineArithmeticOperator(vec[0]);

                cout << op << " " << vec[0] << endl; 

                switch (determineArithmeticOperator(vec[0]))
                {
                case ArithmeticOperator::ADD:
                    file << translateAdd();
                    break;
                case ArithmeticOperator::SUB:
                    file << translateSub();
                    break;
                case ArithmeticOperator::NEG:
                default:
                    file << translateNeg();
                    break;
                }
            }

            file << endl;
        }
    }

    void closeFile()
    {
        file.close();
    }
};

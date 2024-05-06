#include <iostream>
#include <fstream>
#include <string>
#include "types.h"
#include "utils.h"
#include "operations.h"
#include "memory.h"
#include "branching.h"
#include "functions.h"

using namespace std;

class Code
{
private:
    ofstream file;
    string filename;
    vector<vector<string>> commands;

    void closeFile()
    {
        file.close();
    }

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

    ~Code()
    {
        closeFile();
    }

    void translate()
    {
        for (const vector<string> &vec : commands)
        {
            if (vec.size() == 3)
            {
                switch (determineTwoArgumentCommand(vec[0]))
                {
                case PUSH:
                    file << translatePush(filename, determineSegment(vec[1]), stoi(vec[2]));
                    break;
                case POP:
                default:
                    file << translatePop(filename, determineSegment(vec[1]), stoi(vec[2]));
                }
            }
            else if (vec.size() == 2)
            {
                switch (determineOneArgumentCommand(vec[0]))
                {
                case LABEL:
                    file << translateLabel(vec[1]);
                    break;
                case GOTO:
                    file << translateGoto(vec[1]);
                    break;
                case IFGOTO:
                default:
                    file << translateIfGoto(vec[1]);
                    break;
                }
            }
            else if (vec.size() == 1)
            {
                switch (determineNoArgumentCommand(vec[0]))
                {
                case ADD:
                    file << translateAdd();
                    break;
                case SUB:
                    file << translateSub();
                    break;
                case NEG:
                    file << translateNeg();
                    break;
                case EQ:
                    file << translateEq();
                    break;
                case GT:
                    file << translateGt();
                    break;
                case LT:
                    file << translateLt();
                    break;
                case AND:
                    file << translateAnd();
                    break;
                case OR:
                    file << translateOr();
                    break;
                case NOT:
                    file << translateNot();
                    break;
                default:
                    file << translateNeg();
                    break;
                }
            }
        }
    }
};

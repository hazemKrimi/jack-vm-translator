#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum Segment
{
    LCL,
    ARG,
    THIS,
    THAT,
};

class Code
{
private:
    ofstream file;
    vector<vector<string>> commands;

    string translatePush(int constant)
    {
        stringstream output;

        output << '@' << constant << endl;
        output << "D=A" << endl;
        output << "@SP" << endl;
        output << "D=M" << endl;
        output << "@SP" << endl;
        output << "M=M+1" << endl;

        return output.str();
    };

    Segment determineSegment(string segment)
    {
        if (segment == "local")
            return Segment::LCL;
        if (segment == "argument")
            return Segment::ARG;
        if (segment == "this")
            return Segment::THIS;
        if (segment == "that")
            return Segment::THAT;
    }

    string translatePop(Segment segment, int index)
    {
        stringstream output;

        output << "@SP" << index << endl;
        output << "A=M" << endl;
        output << "D=M" << endl;

        switch (segment)
        {
        case LCL:
            output << "@LCL" << endl;
            break;
        case ARG:
            output << "@ARG" << endl;
            break;
        case THIS:
            output << "@THIS" << endl;
            break;
        case THAT:
            output << "@THAT" << endl;
            break;

        default:
            break;
        }

        output << "M=D" << endl;
        output << "@SP" << endl;
        output << "M=M-1" << endl;

        return output.str();
    };

public:
    Code(string path, vector<vector<string>> tokens)
    {
        file = ofstream(path);
        commands = tokens;
    }

    void translate()
    {
        for (const auto &vec : commands)
        {
            if (vec.size() > 1)
            {
                file << vec[0] << "-";
                if (vec.size() > 1)
                    file << vec[1] << "-";
                if (vec.size() > 1)
                    file << vec[2];
                file << endl;
            }
            else
            {
                file << vec[0] << endl;
            }
        }
    }

    void closeFile()
    {
        file.close();
    }
};

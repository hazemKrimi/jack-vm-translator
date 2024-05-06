#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string translatePush(string filename, Segment segment, int index)
{
    stringstream output;

    switch (segment)
    {
    case LCL:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@LCL" << endl;
        output << "A=D+M" << endl;
        output << "D=M" << endl;
        break;
    case ARG:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@ARG" << endl;
        output << "A=D+M" << endl;
        output << "D=M" << endl;
        break;
    case THIS:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@THIS" << endl;
        output << "A=D+M" << endl;
        output << "D=M" << endl;
        break;
    case THAT:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@THAT" << endl;
        output << "A=D+M" << endl;
        output << "D=M" << endl;
        break;
    case POINTER:
        output << (index == 0 ? "@THIS" : "@THAT") << endl;
        output << "D=M" << endl;
        break;
    case STATIC:
        output << "@" << filename << "." << index << endl;
        output << "D=M" << endl;
        break;
    case TEMP:
        output << "@" << index + 5 << endl;
        output << "D=M" << endl;
        break;
    case CONSTANT:
    default:
        output << '@' << index << endl;
        output << "D=A" << endl;
        break;
    }

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translatePop(string filename, Segment segment, int index)
{
    stringstream output;

    switch (segment)
    {
    case LCL:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@LCL" << endl;
        output << "D=D+M" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case ARG:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@ARG" << endl;
        output << "D=D+M" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case THIS:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@THIS" << endl;
        output << "D=D+M" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case THAT:
        output << "@" << index << endl;
        output << "D=A" << endl;
        output << "@THAT" << endl;
        output << "D=D+M" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case POINTER:
        output << (index == 0 ? "@THIS" : "@THAT") << endl;
        output << "D=A" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case STATIC:
        output << "@" << filename << "." << index << endl;
        output << "D=A" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;
    case TEMP:
        output << "@" << index + 5 << endl;
        output << "D=A" << endl;
        output << "@ADDR" << endl;
        output << "M=D" << endl;
        break;

    default:
        break;
    }

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;
    output << "@ADDR" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;

    return output.str();
}

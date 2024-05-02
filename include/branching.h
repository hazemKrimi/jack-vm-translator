#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string translateLabel(string label)
{
    stringstream output;

    output << "(" << label << ")" << endl;

    return output.str();
}

string translateGoto(string label)
{
    stringstream output;

    output << "@" << label << endl;
    output << "0;JMP" << endl;

    return output.str();
}

string translateIfGoto(string label)
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@" << label << endl;
    output << "D;JNE" << endl;

    return output.str();
}
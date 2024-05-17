#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int callCounter = 0;

string translateFunction(string name, int args)
{
    stringstream output;

    output << "(" << name << ")" << endl;

    for (int i = 0; i < args; i++)
    {
        output << "@0" << endl;
        output << "D=A" << endl;
        output << "@SP" << endl;
        output << "A=M" << endl;
        output << "M=D" << endl;
        output << "@SP" << endl;
        output << "M=M+1" << endl;
    }

    return output.str();
}

string translateCall(string name, int args)
{
    stringstream output;
    string label = name + "$ret" + std::to_string(callCounter);

    callCounter++;

    output << "@" << label << endl;
    output << "D=A" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    output << "@LCL" << endl;
    output << "D=M" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    
    output << "@ARG" << endl;
    output << "D=M" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    
    output << "@THIS" << endl;
    output << "D=M" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    
    output << "@THAT" << endl;
    output << "D=M" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    output << "@SP" << endl;
    output << "D=M" << endl;
    output << "@C" << endl;
    output << "M=D" << endl;
    output << "@5" << endl;
    output << "D=A" << endl;
    output << "@C" << endl;
    output << "M=M-D" << endl;
    output << "@" << args << endl;
    output << "D=A" << endl;
    output << "@C" << endl;
    output << "M=M-D" << endl;
    output << "D=M" << endl;
    output << "@ARG" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "D=M" << endl;
    output << "@LCL" << endl;
    output << "M=D" << endl;

    output << "@" << name << endl;
    output << "0;JMP" << endl;
    output << "(" << label << ")" << endl;

    return output.str();
}

string translateReturn()
{
    stringstream output;

    output << "@LCL" << endl;
    output << "D=M" << endl;
    output << "@EF" << endl;
    output << "M=D" << endl;

    output << "@RA" << endl;
    output << "M=D" << endl;
    output << "@5" << endl;
    output << "D=A" << endl;
    output << "@RA" << endl;
    output << "M=M-D" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;
    output << "@RA" << endl;
    output << "M=D" << endl;

    output << "@ARG" << endl;
    output << "D=M" << endl;
    output << "@ADDR" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;
    output << "@ADDR" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;

    output << "@ARG" << endl;
    output << "D=M+1" << endl;
    output << "@SP" << endl;
    output << "M=D" << endl;

    output << "@EF" << endl;
    output << "D=M" << endl;
    output << "@1" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@THAT" << endl;
    output << "M=D" << endl;

    output << "@EF" << endl;
    output << "D=M" << endl;
    output << "@2" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@THIS" << endl;
    output << "M=D" << endl;

    output << "@EF" << endl;
    output << "D=M" << endl;
    output << "@3" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@ARG" << endl;
    output << "M=D" << endl;

    output << "@EF" << endl;
    output << "D=M" << endl;
    output << "@4" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@LCL" << endl;
    output << "M=D" << endl;

    output << "@RA" << endl;
    output << "D=M" << endl;
    output << "D;JMP" << endl;

    return output.str();
}
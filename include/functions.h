#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
    string label = name + "$ret" + generateRandomLabel(3);

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
    output << "@R" << endl;
    output << "M=D" << endl;
    output << "@5" << endl;
    output << "D=A" << endl;
    output << "@R" << endl;
    output << "M=M-D" << endl;
    output << "@" << args << endl;
    output << "D=A" << endl;
    output << "@R" << endl;
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
    string cleanupLabel = "cleanup$ret" + generateRandomLabel(3);
    string endLabel = "end$ret" + generateRandomLabel(3);

    output << "@LCL" << endl;
    output << "D=M" << endl;
    output << "@END_FRAME" << endl;
    output << "M=D" << endl;

    output << "@RETURN_ADDR" << endl;
    output << "M=D" << endl;
    output << "@5" << endl;
    output << "D=A" << endl;
    output << "@RETURN_ADDR" << endl;
    output << "M=M-D" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;
    output << "@RETURN_ADDR" << endl;
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

    output << "@END_FRAME" << endl;
    output << "D=M" << endl;
    output << "@1" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@THAT" << endl;
    output << "M=D" << endl;

    output << "@END_FRAME" << endl;
    output << "D=M" << endl;
    output << "@2" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@THIS" << endl;
    output << "M=D" << endl;

    output << "@END_FRAME" << endl;
    output << "D=M" << endl;
    output << "@3" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@ARG" << endl;
    output << "M=D" << endl;

    output << "@END_FRAME" << endl;
    output << "D=M" << endl;
    output << "@4" << endl;
    output << "D=D-A" << endl;
    output << "A=D" << endl;
    output << "D=M" << endl;
    output << "@LCL" << endl;
    output << "M=D" << endl;

    output << "@RETURN_ADDR" << endl;
    output << "D=M" << endl;
    output << "D;JMP" << endl;

    return output.str();
}
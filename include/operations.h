#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

string translateAdd()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@A" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@A" << endl;
    output << "M=D+M" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateSub()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@S" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@S" << endl;
    output << "M=D-M" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateNeg()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@N" << endl;
    output << "M=D" << endl;
    output << "M=M-D" << endl;
    output << "M=M-D" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateEq()
{
    stringstream output;

    srand(static_cast<unsigned int>(time(nullptr)));

    string LABEL = generateRandomLabel(8);

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@E" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@E" << endl;
    output << "M=D-M" << endl;
    output << "D=M" << endl;
    output << "@" << LABEL << "_TRUE" << endl;
    output << "D;JEQ" << endl;
    output << "@" << LABEL << "_FALSE" << endl;
    output << "D;JNE" << endl;

    output << "(" << LABEL << "_TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << "_FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=0" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << ")" << endl;

    return output.str();
}

string translateGt()
{
    stringstream output;

    srand(static_cast<unsigned int>(time(nullptr)));

    string LABEL = generateRandomLabel(8);

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@GT" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@GT" << endl;
    output << "M=D-M" << endl;
    output << "D=M" << endl;
    output << "@" << LABEL << "_TRUE" << endl;
    output << "D;JGT" << endl;
    output << "@" << LABEL << "_FALSE" << endl;
    output << "D;JLT" << endl;
    output << "@" << LABEL << "_FALSE" << endl;
    output << "D;JEQ" << endl;

    output << "(" << LABEL << "_TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << "_FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=0" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << ")" << endl;

    return output.str();
}

string translateLt()
{
    stringstream output;

    srand(static_cast<unsigned int>(time(nullptr)));

    string LABEL = generateRandomLabel(8);

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@LT" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@LT" << endl;
    output << "M=D-M" << endl;
    output << "D=M" << endl;
    output << "@" << LABEL << "_TRUE" << endl;
    output << "D;JLT" << endl;
    output << "@" << LABEL << "_FALSE" << endl;
    output << "D;JGT" << endl;
    output << "@" << LABEL << "_FALSE" << endl;
    output << "D;JEQ" << endl;

    output << "(" << LABEL << "_TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << "_FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=0" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;
    output << "@" << LABEL << endl;
    output << "0;JMP" << endl;

    output << "(" << LABEL << ")" << endl;

    return output.str();
}

string translateAnd()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@AND" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@AND" << endl;
    output << "M=D&M" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateOr()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@OR" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@OR" << endl;
    output << "M=D|M" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateNot()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=!D" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

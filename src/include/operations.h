#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Operation determineOperation(string operation)
{
    if (operation == "add")
        return Operation::ADD;
    if (operation == "sub")
        return Operation::SUB;
    if (operation == "neg")
        return Operation::NEG;
    if (operation == "eq")
        return Operation::EQ;
    if (operation == "gt")
        return Operation::GT;
    if (operation == "lt")
        return Operation::LT;
    if (operation == "and")
        return Operation::AND;
    if (operation == "or")
        return Operation::OR;
    if (operation == "not")
        return Operation::NOT;

    return Operation::NEG;
}

string translateAdd()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
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

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
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

    output << "@R" << endl;
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

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=M-D" << endl;
    output << "@TRUE" << endl;
    output << "M;JEQ" << endl;
    output << "@FALSE" << endl;
    output << "M;JNE" << endl;

    output << "(TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    output << "(FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateGt()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=M-D" << endl;
    output << "@TRUE" << endl;
    output << "M;JGT" << endl;
    output << "@FALSE" << endl;
    output << "M;JLT" << endl;

    output << "(TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    output << "(FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateLt()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=M-D" << endl;
    output << "@TRUE" << endl;
    output << "M;JLT" << endl;
    output << "@FALSE" << endl;
    output << "M;JGT" << endl;

    output << "(TRUE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    output << "(FALSE)" << endl;
    output << "@SP" << endl;
    output << "A=M" << endl;
    output << "M=-1" << endl;
    output << "@SP" << endl;
    output << "M=M+1" << endl;

    return output.str();
}

string translateAnd()
{
    stringstream output;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
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

    output << "@R" << endl;
    output << "M=D" << endl;

    output << "@SP" << endl;
    output << "M=M-1" << endl;
    output << "A=M" << endl;
    output << "D=M" << endl;

    output << "@R" << endl;
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

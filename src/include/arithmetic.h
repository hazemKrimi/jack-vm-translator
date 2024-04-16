#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ArithmeticOperator determineArithmeticOperator(string arithmeticOperator)
{
    if (arithmeticOperator == "add")
        return ArithmeticOperator::ADD;
    if (arithmeticOperator == "sub")
        return ArithmeticOperator::SUB;
    if (arithmeticOperator == "neg")
        return ArithmeticOperator::NEG;

    return ArithmeticOperator::NEG;
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
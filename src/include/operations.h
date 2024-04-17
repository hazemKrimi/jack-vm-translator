#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Operation determineOperation(string operation)
// {
//     if (operation == "add")
//         return Operation::ADD;
//     if (operation == "sub")
//         return Operation::SUB;
//     if (operation == "neg")
//         return Operation::NEG;

//     return Operation::NEG;
// }

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
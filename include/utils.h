#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <string>

using namespace std;

inline void ltrim(string &str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

inline void rtrim(string &str) {
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), str.end());
}

inline void trim(string &str) {
    rtrim(str);
    ltrim(str);
}

string generateRandomLabel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis('A', 'Z');
    string label;
    
    for (int i = 0; i < 8; ++i) {
        label += static_cast<char>(dis(gen));
    }

    return label;
}

NoArgumentCommand determineNoArgumentCommand(string command)
{
    if (command == "add")
        return NoArgumentCommand::ADD;
    if (command == "sub")
        return NoArgumentCommand::SUB;
    if (command == "neg")
        return NoArgumentCommand::NEG;
    if (command == "eq")
        return NoArgumentCommand::EQ;
    if (command == "gt")
        return NoArgumentCommand::GT;
    if (command == "lt")
        return NoArgumentCommand::LT;
    if (command == "and")
        return NoArgumentCommand::AND;
    if (command == "or")
        return NoArgumentCommand::OR;
    if (command == "not")
        return NoArgumentCommand::NOT;

    return NoArgumentCommand::NEG;
}

OneArgumentCommand determineOneArgumentCommand(string command)
{
    if (command == "label")
        return OneArgumentCommand::LABEL;
    if (command == "goto")
        return OneArgumentCommand::GOTO;
    if (command == "if-goto")
        return OneArgumentCommand::IFGOTO;

    return OneArgumentCommand::IFGOTO;
}

TwoArgumentCommand determineTwoArgumentCommand(string command)
{
    if (command == "push")
        return TwoArgumentCommand::PUSH;
    if (command == "pop")
        return TwoArgumentCommand::POP;

    return TwoArgumentCommand::POP;
}

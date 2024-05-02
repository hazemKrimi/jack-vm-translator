#include <iostream>
#include <regex>
#include "include/parser.h"
#include "include/code.h"

using namespace std;

string constructTranslatedPath(string path) {
    size_t position = path.rfind(".vm");

    return path.replace(position, 3, ".asm");
}

int main(int argc, char* argv[])
{
    if (!argv[1]) {
        cout << "You must specify a vm file path!" << endl;
        return 1;
    }
    
    string sourcePath = argv[1];

    if (!regex_match(sourcePath, regex("^.+\\.vm"))) {
        cout << "Wrong file extension!" << endl;
        return 1;
    }

    Parser parser(sourcePath);

    vector<vector<string>> commands = parser.getCommands();
    
    string translatedPath = constructTranslatedPath(sourcePath);

    Code code(translatedPath, commands);

    code.translate();
 
    return 0;
}
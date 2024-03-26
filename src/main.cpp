#include <iostream>
#include <regex>
#include <parser.h>
#include <code.h>

using namespace std;

string constructTranslatedPath(string path) {
    size_t position = path.rfind(".vm");

    return path.replace(position, 3, ".hack");
}

int main(int argc, char* argv[])
{
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

    parser.closeFile();    
    code.closeFile();    
    return 0;
}
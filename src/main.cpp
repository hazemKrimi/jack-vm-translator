#include <iostream>
#include <regex>
#include <parser.h>

using namespace std;

int main(int argc, char* argv[])
{
    string path = argv[1];

    if (!regex_match(path, regex("^.+\\.vm"))) {
        cout << "Wrong file extension!" << endl;
        return 1;
    }

    Parser parser(path);

    parser.printFile();
    
    return 0;
}
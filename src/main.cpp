#include <iostream>
#include <parser.h>

using namespace std;

int main(int argc, char *argv[])
{
    string path = argv[1];

    Parser parser(path);

    parser.printFile();

    return 0;
}
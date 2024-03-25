#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Code
{
private:
    ofstream file;
public:
    Code(string path)
    {
        file = ofstream(path);
    }

    void writeToFile() {
        file << "Hi!" << endl;
    }
};

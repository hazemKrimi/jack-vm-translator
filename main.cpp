#include <iostream>
#include <regex>
#include <filesystem>
#include <vector>
#include "include/parser.h"
#include "include/code.h"

using namespace std;
namespace fs = std::filesystem;

string constructTranslatedFilePath(string path)
{
    size_t position = path.rfind(".vm");

    return path.replace(position, 3, ".asm");
}

string constructTranslatedDirectoryPath(string path)
{
    string newPath = path;
    
    size_t position = path.rfind("/");

    if (position != string::npos && position == path.size() - 1)
    {
        newPath = path.replace(position, 1, "");
    }

    size_t slashIndex = path.find_last_of('/');

    newPath += "/" + path.substr(slashIndex + 1);

    return newPath + ".asm";
}

void processFile(string sourcePath)
{
    Parser parser(sourcePath);

    vector<vector<string>> commands = parser.getCommands();

    string translatedPath = constructTranslatedFilePath(sourcePath);

    Code code(translatedPath, commands, false);

    code.translate();
}

void processDirectory(string sourcePath, vector<string> files)
{
    string translatedPath = constructTranslatedDirectoryPath(sourcePath);
    bool isNew = true;

    for (const auto &file : files)
    {
        Parser parser(file);

        vector<vector<string>> commands = parser.getCommands();

        Code code(translatedPath, commands, isNew);

        code.translate();

        isNew = false;
    }
}

int main(int argc, char *argv[])
{
    if (!argv[1])
    {
        cout << "You must specify a vm file path!" << endl;
        return 1;
    }

    string sourcePath = argv[1];

    if (!regex_match(sourcePath, regex("^.+\\.vm")))
    {
        if (!fs::is_directory(sourcePath))
        {
            cerr << "Error: " << sourcePath << " is not a directory.\n";
            return 1;
        }

        vector<string> vmFiles;

        for (const auto &entry : fs::directory_iterator(sourcePath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".vm")
            {
                vmFiles.push_back(entry.path().string());
            }
        }

        if (vmFiles.empty())
        {
            cout << "Directory does not contain vm files!" << sourcePath << "\n";
        }
        else
        {
            processDirectory(sourcePath, vmFiles);
        }
    }
    else
    {
        processFile(sourcePath);
    }

    return 0;
}
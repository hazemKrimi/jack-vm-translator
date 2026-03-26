#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "parser.hpp"
#include "utils.hpp"

int process(std::string source) {
  std::ifstream ifs(source);
  std::string line;

  LinkedList<Command> *commands = nullptr;

  while (getline(ifs, line)) {
    if (isComment(line) || isEmptyLine(line))
      continue;

    int parseResult;

    if ((parseResult = parseCommand(commands, line)) != 0)
      return parseResult;
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "You must specify an argument for the vm file to translate!"
              << std::endl;
    exit(1);
  }

  std::string source = argv[1];

  if (!regex_match(source, std::regex("^.+\\.vm"))) {
    std::cerr << "Source file is not a vm file!" << std::endl;
    exit(1);
  }

  return process(source);
}

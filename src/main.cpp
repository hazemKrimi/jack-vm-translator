#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "code.hpp"
#include "parser.hpp"
#include "utils.hpp"

int process(std::string source) {
  std::ifstream ifs(source);
  std::string out = source.substr(0, source.find_last_of('.')) + ".asm";
  std::ofstream ofs(out);
  std::string line;
  std::string output;

  std::vector<Command> commands;

  while (getline(ifs, line)) {
    if (isComment(line) || isEmptyLine(line))
      continue;

    int parseResult;

    if ((parseResult = parseCommand(commands, line)) != 0) {
      return parseResult;
    }
  }

  for (const Command &cmd : commands) {
    int translateResult;

    if ((translateResult = translateCommand(output, cmd)) != 0) {
      return translateResult;
    }

    ofs << output;
  }

  ifs.close();
  ofs.close();
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

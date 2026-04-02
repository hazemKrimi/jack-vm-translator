#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "code.hpp"
#include "parser.hpp"
#include "utils.hpp"

int process(std::string path) {
  std::ifstream ifs(path);
  std::ofstream ofs(getOutputPath(path), std::ofstream::trunc);
  std::string programName = getFileNameFromPath(path);
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

    if ((translateResult = translateCommand(output, programName, cmd)) != 0) {
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

  if (!regex_match(argv[1], std::regex("^.+\\.vm"))) {
    std::cerr << "Source file is not a vm file!" << std::endl;
    exit(1);
  }

  return process(argv[1]);
}

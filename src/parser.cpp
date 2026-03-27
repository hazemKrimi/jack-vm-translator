#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "parser.hpp"

int parseCommand(std::vector<Command> &commands, std::string line) {
  std::smatch matched;

  if (regex_search(line, matched, std::regex("^(.*) (.*) (.*)"))) {
    Command cmd;

    if (matched.ready()) {
      cmd.line = line;
      cmd.type = commandTypes.at(matched[1]);
      cmd.segment = segmentTypes.at(matched[2]);
      cmd.index = std::stoi(std::string(matched[3]));
    }

    commands.push_back(cmd);
    return 0;
  }

  if (regex_search(line, matched, std::regex("^(.*)"))) {
    Command cmd;

    cmd.line = line;
    cmd.type = commandTypes.at(matched[1]);

    commands.push_back(cmd);
    return 0;
  }

  std::cerr << "Incorrect vm command!" << std::endl;
  return 1;
}

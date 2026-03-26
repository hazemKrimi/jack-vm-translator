#include <iostream>
#include <regex>
#include <string>

#include "parser.hpp"

int parseCommand(LinkedList<Command> *commands, std::string line) {
  std::smatch matched;

  if (regex_search(line, matched, std::regex("^(.*) (.*) (.*)"))) {
    Command cmd;
    int err;

    cmd.line = line;
    cmd.type = commandTypes.at(matched[0]);
    cmd.segment = segmentTypes.at(matched[1]);
    cmd.index = std::stoi(matched[2]);

    if ((err = insertNode(commands, cmd)) != 0) {
      std::cerr << "Unexpected error parsing vm command:" << line << std::endl;
      return 1;
    }
  }

  if (regex_search(line, matched, std::regex("^(.*)"))) {
    Command cmd;
    int err;

    cmd.line = line;
    cmd.type = matched[0];

    if ((err = insertNode(commands, cmd)) != 0) {
      std::cerr << "Unexpected error parsing vm command:" << line << std::endl;
      return 1;
    }
  }

  return 0;
}

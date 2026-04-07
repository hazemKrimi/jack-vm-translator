#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "parser.hpp"

int parseCommand(std::vector<Command> &commands, std::string line) {
  std::smatch matched;

  if (regex_search(line, matched, std::regex("^(\\S+)\\s+(\\S+)\\s+(\\S+)$"))) {
    Command cmd;

    if (matched.ready()) {
      std::string segment = matched[2];
      cmd.line = line;
      cmd.commandType = commandTypes.at(matched[1]);
      cmd.segmentType = segmentTypes.at(segment);
      cmd.segmentName = segmentNames.at(segment);
      cmd.index = std::stoi(std::string(matched[3]));
    }

    commands.push_back(cmd);
    return 0;
  }

  if (std::regex_search(line, matched, std::regex("^(\\S+)\\s+(\\S+)$"))) {
    Command cmd;

    if (matched.ready()) {
      cmd.line = line;
      cmd.commandType = commandTypes.at(matched[1]);
      cmd.label = matched[2];
    }

    commands.push_back(cmd);
    return 0;
  }

  if (regex_search(line, matched, std::regex("^(\\S+)$"))) {
    Command cmd;

    if (matched.ready()) {
      cmd.line = line;
      cmd.commandType = commandTypes.at(matched[1]);
    }

    commands.push_back(cmd);
    return 0;
  }

  std::cerr << "Incorrect vm command: " << line << std::endl;
  return 1;
}

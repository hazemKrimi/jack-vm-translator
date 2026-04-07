#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "code.hpp"
#include "parser.hpp"
#include "utils.hpp"

int process(std::string inputPath, std::string outputPath,
            std::ios_base::openmode outputStreamMode) {
  std::ifstream ifs(inputPath);
  std::ofstream ofs(outputPath, outputStreamMode);
  std::string fileName = getFileNameFromPath(inputPath);
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

    if ((translateResult = translateCommand(output, fileName, cmd)) != 0) {
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

  if (regex_match(argv[1], std::regex("^.+\\.vm")))
    return process(argv[1], getOutputPath(argv[1]), std::ofstream::trunc);

  if (!std::filesystem::is_directory(argv[1])) {
    std::cerr << "Argument is not a VM file!" << std::endl;
    exit(1);
  }

  std::string outputPath = getOutputPath(argv[1]);

  if (std::filesystem::exists(outputPath)) {
    std::filesystem::remove(outputPath);
  }

  for (const auto &entry : std::filesystem::directory_iterator(argv[1])) {
    if (entry.is_regular_file() && entry.path().extension() == ".vm") {
      if (process(entry.path().string(), outputPath, std::ofstream::app) != 0)
        exit(1);
    }
  }
}

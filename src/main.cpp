#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "code.hpp"
#include "parser.hpp"
#include "utils.hpp"

int process(std::string inputPath, std::string outputPath,
            std::ios_base::openmode outputStreamMode, bool &init) {
  std::ifstream ifs(inputPath);
  std::ofstream ofs(outputPath, outputStreamMode);
  std::string fileName = getFileNameFromFilePath(inputPath);
  std::string line;
  std::string output;

  if (init) {
    std::ostringstream initStream;
    Command cmd;

    initStream << "// " << "SP = 256" << std::endl;
    initStream << std::endl;

    initStream << "@256" << std::endl;
    initStream << "D=A" << std::endl;
    initStream << "@SP" << std::endl;
    initStream << "M=D" << std::endl;

    cmd.label = "Sys.init";
    cmd.commandType = CommandType::CALL;
    cmd.index = 0;

    initStream << std::endl;
    initStream << "// " << "call Sys.init 0" << std::endl;
    initStream << std::endl;

    if (translateFunctionCall(initStream, cmd) != 0)
      exit(1);

    initStream << std::endl;

    output = initStream.str();
    ofs << output;
    init = false;
  }

  std::vector<Command> commands;

  while (getline(ifs, line)) {
    if (cleanupLine(line) != 0)
      exit(1);

    if (isEmptyLine(line))
      continue;

    if (parseCommand(commands, line) != 0)
      exit(1);
  }

  for (const Command &cmd : commands) {
    if (translateCommand(output, fileName, cmd) != 0)
      exit(1);

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

  bool init = false;

  if (regex_match(argv[1], std::regex("^.+\\.vm")))
    return process(argv[1], getOutputPath(argv[1]), std::ofstream::trunc, init);

  if (!std::filesystem::is_directory(argv[1])) {
    std::cerr << "Argument is not a VM file!" << std::endl;
    exit(1);
  }

  std::string outputPath = getOutputPath(argv[1]);

  if (std::filesystem::exists(outputPath)) {
    std::filesystem::remove(outputPath);
  }

  for (const auto &entry : std::filesystem::directory_iterator(argv[1])) {
    if (entry.is_regular_file() && entry.path().filename() == "Sys.vm") {
      init = true;
    }
  }

  for (const auto &entry : std::filesystem::directory_iterator(argv[1])) {
    if (entry.is_regular_file() && entry.path().extension() == ".vm") {
      if (process(entry.path().string(), outputPath, std::ofstream::app,
                  init) != 0)
        exit(1);
    }
  }
}

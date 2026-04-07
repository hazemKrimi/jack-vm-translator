#include <filesystem>
#include <string>

bool isEmptyLine(const std::string &line) {
  for (char c : line) {
    if (!isspace(c))
      return false;
  }

  return true;
}

bool isComment(const std::string &line) {
  return line[0] == '/' && line[1] == '/';
}

std::string getFileNameFromPath(const std::string &path) {
  std::string fileName = path.substr(path.find_last_of("/\\") + 1);

  return fileName.substr(0, fileName.find_last_of('.'));
}

std::string getOutputPath(const std::string &path) {
  if (std::filesystem::is_directory(path)) {
    return path + "/" + path.substr(path.find_last_of("/\\") + 1) + ".asm";
  }

  return path.substr(0, path.find_last_of('.')) + ".asm";
}

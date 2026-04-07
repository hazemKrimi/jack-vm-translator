#include <filesystem>
#include <string>

bool isEmptyLine(const std::string &line) {
  for (char c : line) {
    if (!isspace(c))
      return false;
  }

  return true;
}

int cleanupLine(std::string &line) {
  size_t commentStartingPosition = line.find("//");

  if (commentStartingPosition != std::string::npos) {
    line = line.substr(0, commentStartingPosition);
  }

  size_t firstNonWhiteSpacePosition = line.find_first_not_of(" \t\n\r");

  if (firstNonWhiteSpacePosition == std::string::npos) {
    line = "";
    return 0;
  }

  size_t lastNonWhiteSpacePosition = line.find_last_not_of(" \t\n\r");
  line =
      line.substr(firstNonWhiteSpacePosition,
                  (lastNonWhiteSpacePosition - firstNonWhiteSpacePosition + 1));

  return 0;
}

std::string getFileNameFromFilePath(const std::string &path) {
  std::string fileName = path.substr(path.find_last_of("/\\") + 1);

  return fileName.substr(0, fileName.find_last_of('.'));
}

std::string getOutputPath(const std::string &path) {
  if (std::filesystem::is_directory(path)) {
    return path + "/" + path.substr(path.find_last_of("/\\") + 1) + ".asm";
  }

  return path.substr(0, path.find_last_of('.')) + ".asm";
}

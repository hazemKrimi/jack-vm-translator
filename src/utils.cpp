#include <cctype>
#include <string>

bool isEmptyLine(std::string line) {
  for (char c : line) {
    if (!isspace(c))
      return false;
  }

  return true;
}

bool isComment(std::string line) { return line[0] == '/' && line[1] == '/'; }

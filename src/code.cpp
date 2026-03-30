#include "types.hpp"
#include <iostream>
#include <sstream>

int translateCommand(std::string &output, Command cmd) {
  std::ostringstream stream;
  
  stream << "// " << cmd.line << std::endl;
  output = stream.str();
  return 0;
}

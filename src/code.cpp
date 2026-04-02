#include "types.hpp"
#include <iostream>
#include <sstream>

static int translateStackOperation(std::ostringstream &stream,
                                   const std::string programName, Command cmd) {
  switch (cmd.segmentType) {
  case SegmentType::LCL:
  case SegmentType::ARG:
  case SegmentType::THIS:
  case SegmentType::THAT:
    stream << "@" << cmd.index << std::endl;
    stream << "D=A" << std::endl;
    stream << "@" << cmd.segmentName << std::endl;

    if (cmd.commandType == CommandType::PUSH) {
      stream << "A=D+M" << std::endl;
      stream << "D=M" << std::endl;
    } else {
      stream << "D=D+M" << std::endl;
      stream << "@ADDR" << std::endl;
      stream << "M=D" << std::endl;
    }

    break;
  case SegmentType::POINTER:
    stream << (cmd.index == 0 ? "@THIS" : "@THAT") << std::endl;

    if (cmd.commandType == CommandType::PUSH) {
      stream << "D=M" << std::endl;
    } else {
      stream << "D=A" << std::endl;
      stream << "@ADDR" << std::endl;
      stream << "M=D" << std::endl;
    }

    break;
  case SegmentType::STATIC:
    stream << "@" << programName << "." << cmd.index << std::endl;

    if (cmd.commandType == CommandType::PUSH) {
      stream << "D=M" << std::endl;
    } else {
      stream << "D=A" << std::endl;
      stream << "@ADDR" << std::endl;
      stream << "M=D" << std::endl;
    }

    break;
  case SegmentType::TEMP:
    stream << "@" << cmd.index + 5 << std::endl;

    if (cmd.commandType == CommandType::PUSH) {
      stream << "D=M" << std::endl;
    } else {
      stream << "D=A" << std::endl;
      stream << "@ADDR" << std::endl;
      stream << "M=D" << std::endl;
    }

    break;
  case SegmentType::CONSTANT:
    if (cmd.commandType == CommandType::POP)
      return 1;

    stream << "@" << cmd.index << std::endl;
    stream << "D=A" << std::endl;
    break;
  default:
    break;
  }

  stream << "@SP" << std::endl;

  if (cmd.commandType == CommandType::PUSH) {
    stream << "A=M" << std::endl;
    stream << "M=D" << std::endl;
    stream << "@SP" << std::endl;
    stream << "M=M+1" << std::endl;
  } else {
    stream << "M=M-1" << std::endl;
    stream << "A=M" << std::endl;
    stream << "D=M" << std::endl;
    stream << "@ADDR" << std::endl;
    stream << "A=M" << std::endl;
    stream << "M=D" << std::endl;
  }

  return 0;
}

int translateArithmeticBinaryOperation(std::ostringstream &stream,
                                       Command cmd) {
  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@BINARY_ARITHMETIC" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@BINARY_ARITHMETIC" << std::endl;

  if (cmd.commandType == CommandType::ADD) {
    stream << "M=D+M" << std::endl;
  } else {
    stream << "M=D-M" << std::endl;
  }

  stream << "D=M" << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

int translateArithmeticUnaryOperation(std::ostringstream &stream) {
  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@NEGATE" << std::endl;
  stream << "M=D" << std::endl;
  stream << "M=M-D" << std::endl;
  stream << "M=M-D" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

int translateEqualityOperation(std::ostringstream &stream, Command cmd) {
  static int equalityCheckLabelCounter = 0;

  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@EQUALITY_CHECK" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@EQUALITY_CHECK" << std::endl;
  stream << "M=D-M" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_TRUE" << std::endl;
  stream << "D;" << (cmd.commandType == CommandType::GT ? "JGT" : cmd.commandType == CommandType::LT ? "JLT" : "JEQ") << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_FALSE" << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_TRUE)" << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=-1" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_FALSE)" << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=0" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << ")" << std::endl;
  equalityCheckLabelCounter++;

  return 0;
}

int translateBitwiseBinaryOperation(std::ostringstream &stream, Command cmd) {
  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@BINARY_BITWISE" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@BINARY_BITWISE" << std::endl;

  if (cmd.commandType == CommandType::AND) {
    stream << "M=D&M" << std::endl;
  } else {
    stream << "M=D|M" << std::endl;
  }

  stream << "D=M" << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

int translateBistwiseUnaryOperation(std::ostringstream &stream) {
  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=!D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

int translateCommand(std::string &output, const std::string programName,
                     Command cmd) {
  std::ostringstream stream;

  stream << "// " << cmd.line << std::endl;
  stream << std::endl;

  switch (cmd.commandType) {
  case CommandType::PUSH:
  case CommandType::POP:
    translateStackOperation(stream, programName, cmd);
    break;
  case CommandType::ADD:
  case CommandType::SUB:
    translateArithmeticBinaryOperation(stream, cmd);
    break;
  case CommandType::NEG:
    translateArithmeticUnaryOperation(stream);
    break;
  case CommandType::EQ:
  case CommandType::GT:
  case CommandType::LT:
    translateEqualityOperation(stream, cmd);
    break;
  case CommandType::AND:
  case CommandType::OR:
    translateBitwiseBinaryOperation(stream, cmd);
    break;
  case CommandType::NOT:
    translateBistwiseUnaryOperation(stream);
    break;
  default:
    break;
  }

  stream << std::endl;
  output = stream.str();
  return 0;
}

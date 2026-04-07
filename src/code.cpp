#include "types.hpp"
#include <iostream>
#include <sstream>

static int pushFromDRegisterToStack(std::ostringstream &stream) {
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

static int popFromStackToDRegister(std::ostringstream &stream) {
  stream << "@SP" << std::endl;
  stream << "M=M-1" << std::endl;
  stream << "A=M" << std::endl;
  stream << "D=M" << std::endl;

  return 0;
}

static int translateStackOperation(std::ostringstream &stream,
                                   const std::string fileName, Command cmd) {
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
    stream << "@" << fileName << "." << cmd.index << std::endl;

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

static int translateArithmeticBinaryOperation(std::ostringstream &stream,
                                              Command cmd) {
  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@BINARY_ARITHMETIC" << std::endl;
  stream << "M=D" << std::endl;

  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@BINARY_ARITHMETIC" << std::endl;

  if (cmd.commandType == CommandType::ADD) {
    stream << "M=D+M" << std::endl;
  } else {
    stream << "M=D-M" << std::endl;
  }

  stream << "D=M" << std::endl;

  return pushFromDRegisterToStack(stream);
}

static int translateArithmeticUnaryOperation(std::ostringstream &stream) {
  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@NEGATE" << std::endl;
  stream << "M=D" << std::endl;
  stream << "M=M-D" << std::endl;
  stream << "M=M-D" << std::endl;
  stream << "D=M" << std::endl;

  return pushFromDRegisterToStack(stream);
}

static int translateEqualityOperation(std::ostringstream &stream, Command cmd) {
  static int equalityCheckLabelCounter = 0;

  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@EQUALITY_CHECK" << std::endl;
  stream << "M=D" << std::endl;

  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@EQUALITY_CHECK" << std::endl;
  stream << "M=D-M" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_TRUE"
         << std::endl;
  stream << "D;"
         << (cmd.commandType == CommandType::GT   ? "JGT"
             : cmd.commandType == CommandType::LT ? "JLT"
                                                  : "JEQ")
         << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_FALSE"
         << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_TRUE)"
         << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=-1" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << "_FALSE)"
         << std::endl;
  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=0" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;
  stream << "@" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << std::endl;
  stream << "0;JMP" << std::endl;

  stream << "(" << "EQUALITY_CHECK_" << equalityCheckLabelCounter << ")"
         << std::endl;
  equalityCheckLabelCounter++;

  return 0;
}

static int translateBitwiseBinaryOperation(std::ostringstream &stream,
                                           Command cmd) {
  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@BINARY_BITWISE" << std::endl;
  stream << "M=D" << std::endl;

  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@BINARY_BITWISE" << std::endl;

  if (cmd.commandType == CommandType::AND) {
    stream << "M=D&M" << std::endl;
  } else {
    stream << "M=D|M" << std::endl;
  }

  stream << "D=M" << std::endl;

  return pushFromDRegisterToStack(stream);
}

static int translateBistwiseUnaryOperation(std::ostringstream &stream) {
  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@SP" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=!D" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=M+1" << std::endl;

  return 0;
}

static int translateLabel(std::ostringstream &stream, Command cmd) {
  stream << "(" << cmd.label << ")" << std::endl;

  return 0;
}

static int translateGoTo(std::ostringstream &stream, Command cmd) {
  stream << "@" << cmd.label << std::endl;
  stream << "0;JMP" << std::endl;

  return 0;
}

static int translateIfGoTo(std::ostringstream &stream, Command cmd) {
  if (popFromStackToDRegister(stream) != 0)
    return 1;

  stream << "@" << cmd.label << std::endl;
  stream << "D;JNE" << std::endl;

  return 0;
}

static int translateFunctionDefinition(std::ostringstream &stream,
                                       Command cmd) {
  stream << "(" << cmd.label << ")" << std::endl;

  for (int i = 0; i < cmd.index; ++i) {
    stream << "@0" << std::endl;
    stream << "D=A" << std::endl;

    if (pushFromDRegisterToStack(stream) != 0)
      return 1;
  }

  return 0;
}

int translateFunctionCall(std::ostringstream &stream, Command cmd) {
  static int callCounter = 0;
  std::string returnLabel = cmd.label + "$ret" + std::to_string(callCounter++);

  stream << "@" << returnLabel << std::endl;
  stream << "D=A" << std::endl;

  if (pushFromDRegisterToStack(stream) != 0)
    return 1;

  stream << "@LCL" << std::endl;
  stream << "D=M" << std::endl;

  if (pushFromDRegisterToStack(stream) != 0)
    return 1;

  stream << "@ARG" << std::endl;
  stream << "D=M" << std::endl;

  if (pushFromDRegisterToStack(stream) != 0)
    return 1;

  stream << "@THIS" << std::endl;
  stream << "D=M" << std::endl;

  if (pushFromDRegisterToStack(stream) != 0)
    return 1;

  stream << "@THAT" << std::endl;
  stream << "D=M" << std::endl;

  if (pushFromDRegisterToStack(stream) != 0)
    return 1;

  stream << "@SP" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@5" << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "@" << cmd.index << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "@ARG" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@SP" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@LCL" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@" << cmd.label << std::endl;
  stream << "0;JMP" << std::endl;
  stream << "(" << returnLabel << ")" << std::endl;

  return 0;
}

static int translateFunctionReturn(std::ostringstream &stream) {
  stream << "@LCL" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@FRAME" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@5" << std::endl;
  stream << "D=A" << std::endl;
  stream << "@FRAME" << std::endl;
  stream << "D=M-D" << std::endl;
  stream << "A=D" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@RETURN_ADDRESS" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@ARG" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@ADDR" << std::endl;
  stream << "M=D" << std::endl;

  if (popFromStackToDRegister(stream) != 0)
    return 1;
  
  stream << "@ADDR" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@ARG" << std::endl;
  stream << "D=M+1" << std::endl;
  stream << "@SP" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@FRAME" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@1" << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "A=D" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@THAT" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@FRAME" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@2" << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "A=D" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@THIS" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@FRAME" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@3" << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "A=D" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@ARG" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@FRAME" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@4" << std::endl;
  stream << "D=D-A" << std::endl;
  stream << "A=D" << std::endl;
  stream << "D=M" << std::endl;
  stream << "@LCL" << std::endl;
  stream << "M=D" << std::endl;

  stream << "@RETURN_ADDRESS" << std::endl;
  stream << "A=M" << std::endl;
  stream << "M;JMP" << std::endl;

  return 0;
}

int translateCommand(std::string &output, const std::string fileName,
                     Command cmd) {
  std::ostringstream stream;

  stream << "// " << cmd.line << std::endl;
  stream << std::endl;

  switch (cmd.commandType) {
  case CommandType::PUSH:
  case CommandType::POP:
    translateStackOperation(stream, fileName, cmd);
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
  case CommandType::LABEL:
    translateLabel(stream, cmd);
    break;
  case CommandType::GOTO:
    translateGoTo(stream, cmd);
    break;
  case CommandType::IFGOTO:
    translateIfGoTo(stream, cmd);
    break;
  case CommandType::FUNCTION:
    translateFunctionDefinition(stream, cmd);
    break;
  case CommandType::CALL:
    translateFunctionCall(stream, cmd);
    break;
  case CommandType::RETURN:
    translateFunctionReturn(stream);
    break;
  default:
    break;
  }

  stream << std::endl;
  output = stream.str();
  return 0;
}

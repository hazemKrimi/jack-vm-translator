#include <string>
#include <unordered_map>

#ifndef TYPES

enum class CommandType {
  ADD,
  SUB,
  NEG,
  EQ,
  GT,
  LT,
  AND,
  OR,
  NOT,
  PUSH,
  POP,
  LABEL,
  GOTO,
  IFGOTO,
  FUNCTION,
  CALL,
  RETURN
};

enum class SegmentType {
  LCL,
  ARG,
  THIS,
  THAT,
  STATIC,
  CONSTANT,
  TEMP,
  POINTER,
};

std::unordered_map<std::string, CommandType> const commandTypes = {
    {"add", CommandType::ADD},
    {"sub", CommandType::SUB},
    {"neg", CommandType::NEG},
    {"eq", CommandType::EQ},
    {"gt", CommandType::GT},
    {"lt", CommandType::LT},
    {"and", CommandType::AND},
    {"or", CommandType::OR},
    {"not", CommandType::NOT},
    {"push", CommandType::PUSH},
    {"pop", CommandType::POP},
    {"label", CommandType::LABEL},
    {"goto", CommandType::GOTO},
    {"if-goto", CommandType::IFGOTO},
    {"function", CommandType::FUNCTION},
    {"call", CommandType::CALL},
    {"return", CommandType::RETURN}};

std::unordered_map<std::string, SegmentType> const segmentTypes = {
    {"local", SegmentType::LCL},     {"argument", SegmentType::ARG},
    {"this", SegmentType::THIS},     {"that", SegmentType::THAT},
    {"static", SegmentType::STATIC}, {"constant", SegmentType::CONSTANT},
    {"temp", SegmentType::TEMP},     {"pointer", SegmentType::POINTER},
};

std::unordered_map<std::string, std::string> const segmentNames = {
    {"local", "LCL"}, {"argument", "ARG"}, {"this", "THIS"},
    {"that", "THAT"}, {"static", "NONE"},  {"constant", "NONE"},
    {"temp", "NONE"}, {"pointer", "NONE"},
};

typedef struct {
  std::string line;
  CommandType commandType;
  SegmentType segmentType;
  std::string segmentName;
  std::string label;
  int index;
} Command;

#define TYPES
#endif

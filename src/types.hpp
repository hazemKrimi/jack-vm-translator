#include <string>
#include <unordered_map>

enum CommandType {
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
};

enum SegmentType {
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
    {"add", CommandType::ADD}, {"sub", CommandType::SUB},
    {"neg", CommandType::NEG}, {"eq", CommandType::EQ},
    {"gt", CommandType::GT},   {"lt", CommandType::LT},
    {"and", CommandType::AND}, {"or", CommandType::OR},
    {"not", CommandType::NOT}, {"push", CommandType::PUSH},
    {"pop", CommandType::POP},
};

std::unordered_map<std::string, SegmentType> const segmentTypes = {
    {"local", SegmentType::LCL},     {"argument", SegmentType::ARG},
    {"this", SegmentType::THIS},     {"that", SegmentType::THAT},
    {"static", SegmentType::STATIC}, {"constant", SegmentType::CONSTANT},
    {"temp", SegmentType::TEMP},     {"pointer", SegmentType::POINTER},
};

typedef struct {
  std::string line;
  std::string type;
  std::string segment;
  int index;
} Command;

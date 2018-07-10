#include "clara.hpp"
#include <iostream>
#include <regex>

using namespace clara;

struct Options {
  int width = 0;
  std::string name;
  bool doIt = false;
  std::string subcommand;
  std::vector<std::string> command;
  std::string direction;
};

int main(int argc, char **argv) {

  bool showHelp = false;
  Options options;

  // clang-format off
  auto cli
            = Help(showHelp)
            | Opt(options.width, "width")["-w"]["--width"]("How wide should it be?")
            | Opt([&](std::string s) {
                if (std::regex_match(s, std::regex("^(North|South|East|West)$"))) {
                  options.direction = s;
                  return ParserResult::ok(ParseResultType::Matched);
                } else {
                  return ParserResult::runtimeError("Direction must match : North|South|East|West");
                }
              } , "direction")["--direction"]("Direction can be : North, South, East, West")
            | Opt(options.name, "name")["-n"]["--name"]("By what name should I be known").required()
            | Opt(options.doIt)["-d"]["--doit"]("Do the thing")
            | Arg([&](std::string s) {
                if (std::regex_match(s, std::regex("^(init|update|add)$"))) {
                  options.subcommand = s;
                  return ParserResult::ok(ParseResultType::Matched);
                } else {
                  return ParserResult::runtimeError("Direction must match : init|update|add");
                }
              }, "subcommand")("can be init|update|add")
            | Arg(options.command, "command")("which command to run");
  // clang-format on

  auto result = cli.parse(Args(argc, argv));

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    exit(1);
  }
  if (showHelp) {
    std::cout << cli << std::endl;
    exit(1);
  }
  std::cout << "width :" << options.width << std::endl;
  std::cout << "name :" << options.name << std::endl;
  std::cout << "doIt :" << options.doIt << std::endl;
  for (auto &&i : options.command) {
    std::cout << "command :" << i << std::endl;
  }
  std::cout << "showHelp :" << showHelp << std::endl;
}

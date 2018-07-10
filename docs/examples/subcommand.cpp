#include "clara.hpp"
#include <experimental/filesystem>
#include <iostream>
#include <regex>

using namespace clara;

struct Config {

  std::string subcommand;
  std::vector<std::string> command;
  // Options
  int width;
  std::string name;
  bool doIt = false;
  std::string direction;
};

int main(int argc, char *argv[]) {
  bool showHelp = false;
  Config config;

  for (int i = 0; i < argc; ++i) {
    std::string arg(argv[i]);
    std::cout << "arg :" << arg << std::endl;
  }

  // clang-format off
  auto subcli = Help(showHelp)
            | Arg([&](std::string s) {
                if (std::regex_match(s, std::regex("^(init|update|add)$"))) {
                  config.subcommand = s;
                  return ParserResult::ok(ParseResultType::Matched);
                } else {
                  return ParserResult::runtimeError("Direction must match : init|update|add");
                }
              }, "subcommand")("can be init|update|add");
  // clang-format on
  auto subresult = subcli.parse(Args(2, argv));
  if (!subresult) {
    std::cerr << "Error in command line: " << subresult.errorMessage() << std::endl;
    exit(1);
  }

  // clang-format off
  auto cli
            = Help(showHelp)
            | Opt(config.width, "width")["-w"]["--width"]("How wide should it be?")
            | Opt([&](std::string s) {
                if (std::regex_match(s, std::regex("^(North|South|East|West)$"))) {
                  config.direction = s;
                  return ParserResult::ok(ParseResultType::Matched);
                } else {
                  return ParserResult::runtimeError("Direction must match : North|South|East|West");
                }
              } , "direction")["--direction"]("Direction can be : North, South, East, West")
            | Opt(config.name, "name")["-n"]["--name"]("By what name should I be known").required()
            | Opt(config.doIt)["-d"]["--doit"]("Do the thing")
            | Arg(config.command, "command")("which command to run");
  // clang-format on
  auto result = cli.parse(Args(argc - 1, argv + 1));
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    exit(1);
  }
  if (showHelp) {
    std::cout << cli << std::endl;
    exit(1);
  }

  std::cout << "width :" << config.width << std::endl;

  std::cout << "name :" << config.name << std::endl;
  std::cout << "doIt :" << config.doIt << std::endl;
  for (auto &&i : config.command) {
    std::cout << "command :" << i << std::endl;
  }
  std::cout << "showHelp :" << showHelp << std::endl;
}

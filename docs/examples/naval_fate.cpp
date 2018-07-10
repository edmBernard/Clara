#include "clara.hpp"
#include <string>
#include <iostream>

struct Options {
  int width = 0;
  std::string name;
  bool doIt = false;
  std::string command;
};

int main(int argc, char **argv) {

  bool showHelp = false;
  Options options;

  auto cli = clara::detail::Help(showHelp) |
             clara::detail::Opt(options.width, "width")["-w"]["--width"]("How wide should it be?") |
             clara::detail::Opt(options.name, "name")["-n"]["--name"]("By what name should I be known") |
             clara::detail::Opt(options.doIt)["-d"]["--doit"]("Do the thing") |
             clara::detail::Arg(options.command, "command")("which command to run").required();

  auto result = cli.parse(clara::detail::Args(argc, argv));

  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    exit(1);
  }

  std::cerr << "Show Help:" << showHelp << std::endl;
  std::cerr << "Width:" << options.width << std::endl;
  std::cerr << "Name:" << options.name << std::endl;
  std::cerr << "Doit:" << options.doIt << std::endl;
  std::cerr << "Command:" << options.command << std::endl;

  if (showHelp)
    std::cerr << cli << std::endl;

  return 0;
}

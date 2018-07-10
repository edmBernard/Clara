#include "clara.hpp"
#include <iostream>
#include <string>

// usage:
//   clara-arguments_example [<files> ... ] options

// where options are:
//   -?, -h, --help       display usage information
//   -v, --verbose        verbose mode
//   -q, --quiet          quiet mode

// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  std::string arg1;
  int arg2;
  std::string arg3;
  std::vector<std::string> extras;
};

int main(int argc, const char *argv[]) {

  Clo options;
  bool showHelp = false;

  // clang-format off
    auto cli
        = Help(showHelp)
        | Opt(options.verbose)["-v"]["--verbose"]("verbose mode")
        | Opt(options.quiet)["-q"]["--quiet"]("quiet mode")
        | Arg(options.arg1, "arg1")("positional arguments 1")
        | Arg(options.arg2, "arg2")("positional arguments 2")
        | Arg(options.arg3, "arg3")("positional arguments 3")
        | Arg(options.extras, "extra")("extra positional arguments");
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

  std::cout << "===================================================" << std::endl;
  std::cout << "   verbose : " << options.verbose << std::endl;
  std::cout << "   quiet   : " << options.quiet << std::endl;
  std::cout << "   arg1   : " << options.arg1 << std::endl;
  std::cout << "   arg2   : " << options.arg2 << std::endl;
  std::cout << "   arg3   : " << options.arg3 << std::endl;
  std::cout << "   extras   : ";
  for (auto &&i : options.extras) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

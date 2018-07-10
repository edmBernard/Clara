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
  std::vector<std::string> files;
};

int main(int argc, const char *argv[]) {

  Clo options;
  bool showHelp = false;

  // clang-format off
    auto cli
        = Help(showHelp)
        | Opt(options.verbose)
            ["-v"]["--verbose"]
            ("verbose mode")
        | Opt(options.quiet)
            ["-q"]["--quiet"]
            ("quiet mode")
        | Arg(options.files, "files")
            ("optional input file");
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
  std::cout << "   files   : ";
  for (auto &&i : options.files) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

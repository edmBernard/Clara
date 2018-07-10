#include "clara.hpp"
#include <iostream>
#include <string>

// usage:
//   clara-list_example [<numbers> ... ] options

// where options are:
//   -?, -h, --help        display usage information
//   -v, --verbose         verbose mode
//   -q, --quiet           quiet mode
//   -f, --file <files>    optional files

// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  std::vector<std::string> files;
  std::vector<int> numbers;
};

int main(int argc, const char *argv[]) {

  Clo options;
  bool showHelp = false;

  // clang-format off
    auto cli
        = Help(showHelp)
        | Opt(options.verbose)["-v"]["--verbose"]("verbose mode")
        | Opt(options.quiet)["-q"]["--quiet"]("quiet mode")
        | Opt(options.files, "files")["-f"]["--file"]("optional files")
        | Arg(options.numbers, "numbers")("optional numbers");
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
  std::cout << "   numbers   : ";
  for (auto &&i : options.numbers) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

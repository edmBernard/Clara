#include "clara.hpp"
#include <iostream>
#include <string>
#include <regex>

// usage:
//   clara-choices_example  options

// where options are:
//   -?, -h, --help                 display usage information
//   -v, --verbose                  verbose mode
//   -q, --quiet                    quiet mode
//   -d, --direction <direction>    Direction can be : North, South, East, West

// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  std::string cardinal_direction;
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
        | Opt([&](std::string s) {
            if (std::regex_match(s, std::regex("^(North|South|East|West)$"))) {
                options.cardinal_direction = s;
                return ParserResult::ok(ParseResultType::Matched);
            } else {
                return ParserResult::runtimeError("Direction must match : North|South|East|West");
            }
        } , "direction")["-d"]["--direction"]("Direction can be : North, South, East, West").required();
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
  std::cout << "   verbose              : " << options.verbose << std::endl;
  std::cout << "   quiet                : " << options.quiet << std::endl;
  std::cout << "   cardinal_direction   : " << options.cardinal_direction << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

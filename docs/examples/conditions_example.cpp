#include "clara.hpp"
#include <iostream>
#include <string>

// usage:
//   clara-conditions_example [<even_number>] options

// where options are:
//   -?, -h, --help                      display usage information
//   -v, --verbose                       verbose mode
//   -q, --quiet                         quiet mode
//   -p, --positive-number <positive>    A positive number

// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  double positive_number;
  int even_number;
};

int main(int argc, const char *argv[]) {

  Clo options;
  bool showHelp = false;

  // clang-format off
    auto cli
        = Help(showHelp)
        | Opt(options.verbose)["-v"]["--verbose"]("verbose mode")
        | Opt(options.quiet)["-q"]["--quiet"]("quiet mode")
        | Opt([&](double i) {
            // Tips: to enter negative number as argument use the following line: ./clara-conditions_example -p=-2
            if (i < 0)
                return ParserResult::runtimeError("positive number must be positive");
            else {
                options.positive_number = i;
                return ParserResult::ok(ParseResultType::Matched);
            }
        }, "positive")["-p"]["--positive-number"]("A positive number" )
        | Arg([&](int i) {
            if (i % 2 != 0)
                return ParserResult::runtimeError("even number must be even");
            else {
                options.even_number = i;
                return ParserResult::ok(ParseResultType::Matched);
            }
        }, "even_number")("an even number");
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
  std::cout << "   positive_number   : " << options.positive_number << std::endl;
  std::cout << "   even_number   : " << options.even_number << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

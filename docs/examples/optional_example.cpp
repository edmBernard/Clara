#include <optional>
#include "clara.hpp"
#include <iostream>
#include <string>

// usage:
//   clara-optional_example  options

// where options are:
//   -?, -h, --help               display usage information
//   -v, --verbose                verbose mode
//   -q, --quiet                  quiet mode
//   --with-default <value>       option with a default value
//   --without-default <value>    options without default value
//   -r, --repeated <value>       repeated arguments

// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  std::string with_default = "MyDefaultValue";
  std::optional<std::string> without_default;
  std::vector<std::string> repeated;
};

int main(int argc, const char *argv[]) {

  Clo options;
  bool showHelp = false;

  // clang-format off
    auto cli
        = Help(showHelp)
        | Opt(options.verbose)["-v"]["--verbose"]("verbose mode")
        | Opt(options.quiet)["-q"]["--quiet"]("quiet mode")
        | Opt(options.with_default, "value")["--with-default"]("option with a default value")
        | Opt(options.without_default,"value")["--without-default"]("options without default value")
        | Opt(options.repeated, "value")["-r"]["--repeated"]("repeated arguments");
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
  std::cout << "   with_default  : " << options.with_default << std::endl;
  if (options.without_default.has_value()) {
    std::cout << "   without_default  : " << options.without_default.value() << std::endl;
  }
  if (!options.repeated.empty())
  {
    std::cout << "   repeated   : ";
    for (auto &&i : options.repeated) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << "===================================================" << std::endl;

  return 1;
}

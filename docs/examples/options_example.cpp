#include "clara.hpp"
#include <iostream>
#include <string>

// Example of program with many options using docopt.
// Usage:
//   options_example.py [-hvqrf NAME] [--exclude=PATTERNS]
//                      [--select=ERRORS | --ignore=ERRORS] [--show-source]
//                      [--statistics] [--count] [--benchmark] PATH...
// Arguments:
//   PATH  destination path
// Options:
//   -h --help            show this help message and exit
//   --version            show version and exit
//   -v --verbose         print status messages
//   -q --quiet           report only file names
//   -r --repeat          show all occurrences of the same error
//   --exclude=PATTERNS   exclude files or directories which match these comma
//                        separated patterns [default: .svn,CVS,.bzr,.hg,.git]
//   -f NAME --file=NAME  when parsing directories, only check filenames matching
//                        these comma separated patterns [default: *.py]
//   --select=ERRORS      select errors and warnings (e.g. E,W6)
//   --ignore=ERRORS      skip errors and warnings (e.g. E4,W)
//   --show-source        show source code for each error
//   --statistics         count errors and warnings
//   --count              print total number of errors and warnings to standard
//                        error and set exit code to 1 if total is not null
//   --benchmark          measure processing speed
//   --testsuite=DIR      run regression tests from dir
//   --doctest            run doctest on myself


// for convenience
using namespace clara;

struct Clo {
  bool verbose;
  bool quiet;
  std::string with_default = "MyDefaultValue";
  std::string without_default;
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
  std::cout << "   without_default  : " << options.without_default << std::endl;
  std::cout << "   repeated   : ";
  for (auto &&i : options.repeated) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  std::cout << "===================================================" << std::endl;

  return 1;
}

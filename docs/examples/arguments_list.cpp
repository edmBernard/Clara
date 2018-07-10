#include "clara.hpp"
#include <iostream>
#include <string>

using namespace clara;

struct clo {
    std::string filename = "my_test";
    std::string start_date = "2018-03-28 11:10:00.000";
    std::string end_date = "2018-03-29 11:15:00.000";
    float frame_step = 120;
    float accu_step = 120;
    float utc = 0;
    int radius = 7;
    std::vector<std::string> address;
};


int main(int argc, const char *argv[])
{
    clo config;
    bool showHelp = false;
    // clang-format off
    auto cli
                = Help(showHelp)
                | Opt(config.filename, "filename")["-f"]["--filename"]("output filename suffix").required()
                | Opt(config.start_date, "start_date")["--start-date"]("Start date : YYYY-MM-SS HH:MM:SS.fff")
                | Opt(config.end_date, "end_date")["--end-date"]("End date : YYYY-MM-SS HH:MM:SS.fff")
                | Opt(config.frame_step, "frame_step")["--time-step"]("Frame Time step")
                | Opt(config.accu_step, "accu_step")["--accu-step"]("Accumulation Time step")
                | Opt(config.utc, "utc")["--utc"]("UTC for overlay")
                | Opt(config.radius, "radius")["--radius"]("Circle radius")
                | Opt(config.address, "address")["--address"]("host");
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

    if (config.address.size() == 0)
        config.address = {"localhost"};

    std::cout << "===================================================" << std::endl;
    std::cout << "   filename : " <<  config.filename << std::endl;
    std::cout << "   start_date : " <<  config.start_date << std::endl;
    std::cout << "   end_date : " <<  config.end_date << std::endl;
    std::cout << "   frame_step : " << config.frame_step << std::endl;
    std::cout << "   accu_step : " << config.accu_step << std::endl;
    std::cout << "   utc : " << config.utc << std::endl;
    std::cout << "   radius : " << config.radius << std::endl;

    std::cout << "   address : ";
    for (auto&& i : config.address) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    std::cout << "===================================================" << std::endl;

    return 1;
}

// 326627635 | adi.peisach@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../Constants.hpp"
using namespace doctest;

int return_code = -1;

struct ReporterCounter : public ConsoleReporter
{
    ReporterCounter(const ContextOptions &input_options)
            : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats &run_stats) override
    {
        std::cout << "You have " << run_stats.numAsserts << " tests." << std::endl;
        std::cout << Constants::GREEN << "Number of tests passed: " << run_stats.numAsserts-run_stats.numAssertsFailed << std::endl;
        std::cout << Constants::RED << "Number of tests failed: " << run_stats.numAssertsFailed << Constants::RESET << std::endl;
        if (run_stats.numAssertsFailed == 0)
        {
            std::cout << Constants::GREEN << "All tests passed!" << Constants::RESET << std::endl;
            return_code = 0;
        }
        else
        {
            std::cout << Constants::RED << "Some tests failed." << Constants::RESET << std::endl;
            return_code = -1;
        }
    }
};

REGISTER_REPORTER("counter", 1, ReporterCounter);

int main(int argc, char **argv)
{
    Context context;
    context.addFilter("reporters", "counter");
    context.run();
    return return_code;
}
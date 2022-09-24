#include <iostream>

#include "logging/logging.hh"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    // Experimental
    logging::init("example");

    logging::addSinks(std::vector<logging::Sink>{logging::Sink::STDOUT, logging::Sink::FILE, logging::Sink::SYSLOG});

    logging::info("Example project");
    logging::error("Error message with arg: {}", 1);
    logging::warn("Easy padding in numbers like: {:08d}", 12);
    logging::critical("Support for int: {0:d}, hex: {0:x}, oct: {0:o}, bin: {0:b}", 69);
    logging::info("Support for floats {:03.2f}", 1.23456);
    logging::info("Positional args are {1} {0}", "supported", "also");
    logging::info("{:<30}", "left aligned");

    // Set global log level to debug
    logging::setLevel(logging::Level::DEBUG);
    logging::debug("This message should be displayed...");

    // Change log pattern
    logging::setPattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    logging::debug("This message should be displayed as well...");

    return 0;
}

#include <iostream>

#include "logging.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    logging::info("Example {}", "project");

    return 0;
}

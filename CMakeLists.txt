cmake_minimum_required(VERSION 3.16...3.23)

# Set the project name and language
project(logging
    VERSION 0.2.0
    DESCRIPTION "C++ logging wrapper library."
    HOMEPAGE_URL "https://github.com/laFette21/logging"
    LANGUAGES CXX C
)

# Include cmake files
include(cmake/settings.cmake)
include(cmake/compilerWarnings.cmake)
include(cmake/conanConfig.cmake)

run_conan()

# Enable project warnings
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings TRUE)

# Add the src directory
add_subdirectory(src)

# Enable testing
enable_testing()

cmake_minimum_required(VERSION 3.0.0)
project(cpp-extras VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Check if the platform is Windows
if(WIN32)
    message(STATUS "Building on Windows. Disabling Curses.")
else()
    find_package(Curses REQUIRED)
    add_executable(interface tests/interface.cpp)
    target_link_libraries(interface ${CURSES_LIBRARIES})
endif()

add_executable(fstring tests/fstring.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

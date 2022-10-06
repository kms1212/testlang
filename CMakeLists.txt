cmake_minimum_required(VERSION 3.12)

project("TestLanguage")

find_package(BISON REQUIRED)

set(REFLEX_PATH false CACHE FILEPATH "the path of Re-Flex executable")

if(BISON_FOUND)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)
    bison_target(parser ${CMAKE_SOURCE_DIR}/src/parser.yxx ${CMAKE_BINARY_DIR}/generated/parser.tab.cpp)
    add_executable(${PROJECT_NAME} ${BISON_parser_OUTPUTS})
else(BISON_FOUND)

endif(BISON_FOUND)

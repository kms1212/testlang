cmake_minimum_required(VERSION 3.12)

project("TestLanguage")

# Package Configurations

include(ExternalProject)

externalproject_add(re-flex
    GIT_REPOSITORY    "https://github.com/Genivia/RE-flex.git"
    GIT_TAG           "v3.2.11"
    PREFIX            "${CMAKE_BINARY_DIR}/re-flex"
    CONFIGURE_COMMAND bash clean.sh
    BUILD_COMMAND     bash build.sh 
    INSTALL_COMMAND   ""
    BUILD_IN_SOURCE   1
    BUILD_ALWAYS      NO
)

set(REFLEX_INCLUDE_DIR "${CMAKE_BINARY_DIR}/re-flex/src/re-flex/include")
set(REFLEX_LIB_DIR "${CMAKE_BINARY_DIR}/re-flex/src/re-flex/lib")
set(REFLEX_PATH "${CMAKE_BINARY_DIR}/re-flex/src/re-flex/bin/reflex")

find_package(BISON REQUIRED)

set(REFLEX_PATH false CACHE FILEPATH "the path of Re-Flex executable")

if(BISON_FOUND)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS NO)

    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)

    # Generate the parser
    bison_target(parser ${CMAKE_SOURCE_DIR}/src/parser.yxx ${CMAKE_BINARY_DIR}/generated/parser.tab.cpp)

    # Generate the lexer
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/generated/lexer.cpp ${CMAKE_BINARY_DIR}/generated/lexer.hpp
        COMMAND ${REFLEX_PATH} -o ${CMAKE_BINARY_DIR}/generated/lexer.cpp --header-file=${CMAKE_BINARY_DIR}/generated/lexer.hpp ${CMAKE_SOURCE_DIR}/src/lexer.lxx
        DEPENDS ${CMAKE_SOURCE_DIR}/src/lexer.lxx
    )
    add_custom_target(lexer DEPENDS ${CMAKE_BINARY_DIR}/generated/lexer.cpp)

    # Source files
    file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" ${BISON_parser_OUTPUTS})

    add_executable(${PROJECT_NAME}
        ${BISON_parser_OUTPUTS} ${CMAKE_BINARY_DIR}/generated/lexer.cpp ${SOURCES}
    )

    add_dependencies(${PROJECT_NAME} lexer)

    target_include_directories(${PROJECT_NAME} PRIVATE ${REFLEX_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/generated)
    target_link_libraries(${PROJECT_NAME} ${REFLEX_LIB_DIR}/libreflex.a)
else(BISON_FOUND)

endif(BISON_FOUND)

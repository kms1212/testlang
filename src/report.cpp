#include "report.hpp"

#include <iostream>

void report::error(yy::location const& loc, std::string const& msg) {
    if (loc.begin.line == loc.end.line)
        std::cerr << "Error in (" << loc.begin.line << "l, " << loc.begin.column << "c~" << loc.end.column << "c): " << msg << std::endl;
    else
        std::cerr << "Error in (" << loc.begin.line << "l, " << loc.begin.column << "c)~(" << loc.end.line << "l, " << loc.end.column << "c): " << msg << std::endl;
}

void report::error(std::string const& msg) {
    std::cerr << msg << std::endl;
}
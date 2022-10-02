#ifndef REPORT_HPP_
#define REPORT_HPP_

#include <string>

#include "location.hh"

namespace report {
    void error(yy::location const& loc, std::string const& msg);
    void error(std::string const& msg);
}  // namespace report

#endif  // REPORT_HPP_

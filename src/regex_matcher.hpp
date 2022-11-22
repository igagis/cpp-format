#pragma once

#include <regex>

#include "matcher.hpp"

namespace cpp_format{

class regex_matcher : public matcher{
    std::regex regex;

public:
    regex_matcher(std::string_view regex_str) :
            regex(regex_str.data(), regex_str.size(), std::regex_constants::optimize)
    {}

    match_result match(std::string_view str, bool line_begin)const override;
};

}

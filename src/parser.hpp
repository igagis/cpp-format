#pragma once

#include <string>
#include <regex>

#include <utki/span.hpp>

#include "model.hpp"

namespace cpp_format{

class parser{
public:
    std::vector<element> model;

    void feed(std::string_view line);

    void end_of_data();
};

}

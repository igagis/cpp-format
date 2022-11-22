#pragma once

#include <string>
#include <regex>

#include <utki/span.hpp>

#include "model.hpp"

namespace cpp_format{

class context{
public:

};

class parser{
    std::vector<std::reference_wrapper<context>> context_stack;
public:
    container_element root;

    void feed(std::string_view line);

    void end_of_data();
};

}

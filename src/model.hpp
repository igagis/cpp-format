#pragma once

#include <string>

namespace cpp_format{

struct text_location{
    unsigned line;
    unsigned pos;
};

class element{
public:
    const text_location loc;

    element(const text_location& loc) :
        loc(loc)
    {}
};

class empty_line : public element{
public:
    empty_line(text_location loc) :
        element(loc)
    {}
};

class preprocessor_directive : public element{
public:
    const std::string name;
    const std::string arg;

    preprocessor_directive(
        std::string name,
        std::string arg,
        const text_location& loc
    ) :
        element(loc),
        name(std::move(name))
    {}
};



}

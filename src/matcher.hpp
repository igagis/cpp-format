#pragma once

#include <string>
#include <vector>
#include <memory>

#include <utki/span.hpp>

namespace cpp_format{

struct capture_group{
    bool matched;
    size_t offset;
    std::string str;
};

struct match_result{
    size_t begin;
    size_t size;

    std::vector<capture_group> capture_groups;
};

class matcher{
public:
    const bool is_preprocessed;

    matcher(bool is_preprocessed = false) :
            is_preprocessed(is_preprocessed)
    {}

    virtual ~matcher(){}

    virtual match_result match(std::string_view str, bool line_begin)const = 0;

    virtual std::shared_ptr<const matcher> preprocess(
            utki::span<const capture_group> capture_groups
        )const
    {
        return nullptr;
    }
};

}

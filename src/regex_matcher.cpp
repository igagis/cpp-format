#include "regex_matcher.hpp"

#include <utki/debug.hpp>

using namespace cpp_format;

match_result regex_matcher::match(std::string_view str, bool line_begin)const{
    std::match_results<decltype(str)::const_iterator> m;

    auto regex_flags = std::regex_constants::match_default;
    if(!line_begin){
        regex_flags |= std::regex_constants::match_not_bol;
    }

    if(!std::regex_search(str.begin(), str.end(), m, this->regex, regex_flags)){
        return match_result{
            .begin = str.size(),
            .size = 1
        };
    }

    ASSERT(!m.empty())

    std::vector<capture_group> capture_groups;

    ASSERT(m.size() >= 1)
    for(size_t i = 1; i != m.size(); ++i){
        if(!m[i].matched){
            capture_groups.push_back(capture_group{
                    .matched = false,
                    .offset = size_t(std::distance(m[0].first, m[0].second))
                });
        }else{
            capture_groups.push_back(capture_group{
                    .matched = true,
                    .offset = size_t(std::distance(m[0].first, m[i].first)),
                    .str = std::string(m[i].first, m[i].second)
                });
        }
    }

    return match_result{
        .begin = size_t(std::distance(str.cbegin(), m[0].first)),
        .size = size_t(std::distance(m[0].first, m[0].second)),
        .capture_groups = std::move(capture_groups)
    };
}

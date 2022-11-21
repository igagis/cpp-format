#include "parser.hpp"

using namespace cpp_format;

namespace{
class matcher{
public:
    const bool is_preprocessed;

    matcher(bool is_preprocessed = false) :
            is_preprocessed(is_preprocessed)
    {}

    virtual ~matcher(){}

    struct match_result{
        size_t begin;
        size_t size;

        struct capture_group{
            bool matched;
            size_t offset;
            std::string str;
        };
        std::vector<capture_group> capture_groups;
    };
    virtual match_result match(std::string_view str, bool line_begin)const = 0;

    virtual std::shared_ptr<const matcher> preprocess(
            utki::span<const match_result::capture_group> capture_groups
        )const
    {
        return nullptr;
    }
};
}

namespace{
class regex_matcher : public matcher{
    std::regex regex;

public:
    regex_matcher(std::string_view regex_str) :
            regex(regex_str.data(), regex_str.size(), std::regex_constants::optimize)
    {}
    match_result match(std::string_view str, bool line_begin)const override{
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

        std::vector<match_result::capture_group> capture_groups;

        ASSERT(m.size() >= 1)
        for(size_t i = 1; i != m.size(); ++i){
            if(!m[i].matched){
                capture_groups.push_back(match_result::capture_group{
                        .matched = false,
                        .offset = size_t(std::distance(m[0].first, m[0].second))
                    });
            }else{
                capture_groups.push_back(match_result::capture_group{
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
};
}

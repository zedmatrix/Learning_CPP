#include <format>
#include <vector>
#include <string>
#include <algorithm>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    std::string s1 {"big light in the sky slated to appear in the east"};
    std::string s2 {};
    std::string s3 {};

    // char_upper operator
    auto char_upper = [](char c) ->char {
        if(c >= 'a' && c <= 'z') return c - ('a' - 'A');
        else return c;
    };
  
    // oringal string
    print("s1: {}\n", s1);
  
    // char_upper transform
    std::transform(s1.begin(), s1.end(), std::back_inserter(s2), char_upper );
    print("s2: {}\n", s2);

    // title_case operator
    auto title_case = [&char_upper](char c) {
        static char prev_c {' '};
        char new_c {prev_c == ' ' ? char_upper(c) : c};
        prev_c = c;
        return new_c;
    };

    // title_case transform
    std::transform(s1.begin(), s1.end(), std::back_inserter(s3), title_case);
    print("s3: {}\n", s3);
}

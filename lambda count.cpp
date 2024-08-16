#include <iostream>
#include <vector>
#include <algorithm>
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    int x = 5;
    auto is_div = [x](int i) { return i % x == 0; };

    std::vector<int> v1 = {10, 15, 22, 25, 30, 12, 24};

    // Correct usage of std::count_if
    auto count = std::count_if(v1.begin(), v1.end(), is_div);

    // Correct print statement using your custom print function
    print("div by {} count is {}\n", x, count);

    return 0;
}

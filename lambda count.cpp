#include <iostream>
#include <vector>
#include <algorithm>
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}
// display the vector
void disp_v(const auto& v) {
    print("{}", "Vector: ");
    if (!v.size()) return;
    for(auto e : v) print("{} ", e);
    print("\n");
}

int main() {
    int x = 5;
    auto is_div = [x](int i) { return i % x == 0; };

    std::vector<int> v1 = {10, 15, 22, 25, 30, 12, 24};
    std::vector<int> v2{};
    print("Original ");
    disp_v(v1);
    // Correct usage of std::count_if
    auto count = std::count_if(v1.begin(), v1.end(), is_div);

    // Correct print statement using your custom print function
    print("div by {} count is {}\n", x, count);

    //copy numbers div by 'x'
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v2), is_div);
    disp_v(v2);
    return 0;
}

#include <print>
#include <format>
#include <string>

template<typename...A>
void prnt(std::format_string<A...> fmt, A&&... args) {
    std::print(fmt, std::forward<A>(args)...);
}

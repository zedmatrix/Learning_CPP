#ifndef COLORIZE_H
#define COLORIZE_H

#include <string>
#include <format>

constexpr const char* ANSI_START = "\x1b[";

enum class Colors {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37
};

struct ANSICode {
    int code;
    bool bright;
    bool bold;

    [[nodiscard]] std::string str() const;
};

// Custom formatter for ANSICode
template <>
struct std::formatter<ANSICode> : std::formatter<std::string> {
    auto format(const ANSICode& ansi, std::format_context& ctx) const {
        return std::formatter<std::string>::format(ansi.str(), ctx);
    }
};

// Overload for `colorize` to support format-style arguments
template <typename... Args>
std::string colorize(std::format_string<Args...> fmt, Colors color, bool bright, bool bold, Args&&... args) {
    std::string formatted_text = std::format(fmt, std::forward<Args>(args)...);
    ANSICode start_code{static_cast<int>(color), bright, bold};
    ANSICode reset_code{0, false, false};
    return std::format("{}{}{}", start_code, formatted_text, reset_code);
}

#endif // COLORIZE_H

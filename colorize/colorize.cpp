#include "colorize.h"

std::string ANSICode::str() const {
    int color_code = code + (bright ? 60 : 0);
    std::string bold_str = bold ? ";1" : "";
    return std::format("{}{}{}m", ANSI_START, color_code, bold_str);
}

std::string colorize(const std::string& text, Colors color, bool bright, bool bold) {
    ANSICode start_code{static_cast<int>(color), bright, bold};
    ANSICode reset_code{0, false, false};
    return std::format("{}{}{}", start_code, text, reset_code);
}

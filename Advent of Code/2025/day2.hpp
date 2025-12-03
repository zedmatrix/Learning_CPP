/*
 * day two - gift shop
 * invalid 55 (5 twice), 6464 (64 twice), and 123123 (123 twice)
 * and 0101 but not 101
 *
 *
 *
 */
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

std::string day_two_loader(std::filesystem::path file) {
    std::string m_data;

    bool mode = false;
    std::fstream m_filestream = open_file(file, mode);
    m_data = read_line(m_filestream);

    if (close_file(m_filestream)) {
        std::println("Close Successful");
        return m_data;
    } else {
        std::println("Close Error");
        return {};
    }
}
bool invalid_part_one(long long n) {
    std::string s = std::to_string(n);
    if (s.size() % 2 != 0) return false;

    long long half = s.size() / 2;
    return s.substr(0, half) == s.substr(half, half);
}
bool invalid_part_two(long long n) {
    std::string s = std::to_string(n);
    int len = s.size();

    for (int sub = 1; sub <= len / 2; ++sub) {
        if (len % sub != 0)
            continue;

        std::string pattern = s.substr(0, sub);
        std::string built;

        for (int i = 0; i < len / sub; ++i)
            built += pattern;

        if (built == s)
            return true;
    }
    return false;
}

void day_two_part_one(std::string& m_data) {
    std::string delim1 = ",";
    std::string delim2 = "-";

    long long token_one{0};
    long long token_two{0};
    long long result{0};

    for (auto range : std::views::split(m_data, delim1)) {
        std::string_view one_range{ std::string_view(range) };

        auto parts = one_range | std::views::split('-');
        auto it = parts.begin();

        std::string_view start = std::string_view(*it++);
        std::string_view end   = std::string_view(*it);

        token_one = std::stoll(std::string(start));
        token_two = std::stoll(std::string(end));

        prnt(" token one: {} and token two: {} \n", token_one, token_two);
        for (long long n = token_one; n <= token_two; ++n) {
            if (invalid_part_one(n)) {
                prnt(" => Invalid:{}\n", n);
                result += n;
            }
        }
    }
    prnt("\n Password: {}\n", result);
}
void day_two_part_two(std::string& m_data) {
    std::string delim1 = ",";
    std::string delim2 = "-";

    long long token_one{0};
    long long token_two{0};
    long long result{0};

    for (auto range : std::views::split(m_data, delim1)) {
        std::string_view one_range{ std::string_view(range) };

        auto parts = one_range | std::views::split('-');
        auto it = parts.begin();

        std::string_view start = std::string_view(*it++);
        std::string_view end   = std::string_view(*it);

        token_one = std::stoll(std::string(start));
        token_two = std::stoll(std::string(end));

        prnt(" token one: {} and token two: {} \n", token_one, token_two);
        for (long long n = token_one; n <= token_two; ++n) {
            if (invalid_part_two(n)) {
                prnt(" => Invalid:{}\n", n);
                result += n;
            }
        }
    }
    prnt("\n Password: {}\n", result);
}

void day_two(bool test, int part) {
    std::filesystem::path m_daytwo;
    if (test) {
        // Test Data: Password: 4174379265
        prnt("Loading Day Two Test Data");
        m_daytwo = "day2-test.txt";
    } else {
        // Actual Data: Password: 35950619148
        prnt("Loading Day Two Actual Data");
        m_daytwo = "day2.txt";
    }
    std::string ranges = day_two_loader(m_daytwo);
    if (part == 1) {
        //Actual Password: 23039913998
        prnt("Day Two - Part One");
        day_two_part_one(ranges);
    } else {
        prnt("Day Two - Part Two");
        day_two_part_two(ranges);
    }

}

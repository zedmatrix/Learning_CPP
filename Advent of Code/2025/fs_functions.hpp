/*
 * open_file ( filesystem file, bool mode [ true = write | false = read ] )
 * close_file ( fstream stream )
 * read_line ( fstream stream ) returns std::string
 * write_line ( fstream stream , std::string text ) returns true or false
 */

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

std::fstream open_file(const fs::path& file, bool mode = true/*for output*/) {
    std::ios_base::openmode open_mode = mode ? std::ios::out : std::ios::in;

    if (!mode && !fs::exists(file)) {
        std::cerr << "File not found: " << file << "\n";
        return {};
    }
    std::fstream stream(file, open_mode);
    if (!stream.is_open()) {
        std::cerr << "Failed to open: " << file << "\n";
    }
    return stream;
}

bool close_file(std::fstream& stream) {
    if (!stream.is_open()) {
        return false;
    }
    stream.close();
    return !stream.is_open();
}

std::string read_line(std::fstream& stream) {
    if (!stream.is_open()) {
        return {};
    }

    std::string line;
    if (std::getline(stream, line)) {
        return line;
    }

    return {};
}

bool write_line(std::fstream& stream, const std::string& text) {
    if (!stream.is_open()) {
        return false;
    }

    stream << text << '\n';
    if (!stream.good()) {
        return false;
    }

    return true; // success
}

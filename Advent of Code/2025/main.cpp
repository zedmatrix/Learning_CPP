#include "print.hpp"
#include "fs_functions.hpp"
#include "day1.hpp"
#include "day2.hpp"

int main(int argc, char* argv[], char* env[]) {

    std::string env_string;
    //std::cout << "Environment: " << std::endl;
    // for (int i=0; env[i]!=NULL; i++) {
    //     env_string = std::string(env[i]);
    //     if (env_string.find("advent") != std::string::npos) {
    //         prnt("Found Advent Environment: {}\n", env[i]);
    //
    //     }
    // }

    if (argc > 1) {
        std::string_view cmd_arg = argv[1];
        prnt("Command Line: {}\n", cmd_arg);

        if (cmd_arg == "1") day_one_test();
        if (cmd_arg == "11") day_one_part_one();
        if (cmd_arg == "12") day_one_part_two();

        if (cmd_arg == "2") day_two(true, 1);
        if (cmd_arg == "20") day_two(true, 2);
        if (cmd_arg == "21") day_two(false, 1);
        if (cmd_arg == "22") day_two(false, 2);
    } else {
        return 127;
    }
    return 0;
}

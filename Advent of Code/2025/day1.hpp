/* advent day 1 - dial 0 - 99
 *
 * L = Left : turn to lower number
 * R = Right : turn to higher numbers
 *
 * Part Two:
 * You remember from the training seminar that "method 0x434C49434B" means
 * you're actually supposed to count the number of times any click causes
 * the dial to point at 0, regardless of whether it happens during a rotation or at the end of one.
 *
*/

#include <vector>
#include <cstdlib>
#include <cmath>

int mod(int x, int N) {
    int r = x % N;              //sign reminder
    return (r < 0) ? r + N : r; //compensate for sign
}
std::vector<std::string> day_one_loader() {
    std::filesystem::path m_dayone = "day1.txt";
    std::string m_datastr;
    std::vector<std::string> m_data;

    bool mode = false;
    std::fstream m_filestream = open_file(m_dayone, mode);
    while (!m_filestream.eof()) {
        m_datastr = read_line(m_filestream);
        if (!m_datastr.empty()) {
            //std::println("Line: {}", m_datastr);
            m_data.emplace_back(m_datastr);
        }
    }

    if (close_file(m_filestream)) {
        std::println("Close Successful");
        return m_data;
    } else {
        std::println("Close Error");
        return {};
    }
}

void sol_one_part_one(std::vector<std::string>& m_data) {
    int m_dial{50};
    int m_direction{0};
    int m_amount{0};
    int m_count{0};

    prnt("  => Dir:{} Amt:{} Dial:{} Count:{}\n", m_direction, m_amount, m_dial, m_count);

    for (auto line : m_data) {
        m_direction = (line[0]=='R') ? 1 : -1;      //short if to convert direction
        m_amount = stoi(line.substr(1));            //convert string amt to int
        prnt(" -> dir:{} amt:{}", m_direction, m_amount);

        m_dial = mod(m_dial + m_direction * m_amount, 100);
        prnt(" Dial:{}", m_dial);

        m_count += (m_dial==0) ? 1 : 0;
        prnt(" Count:{} \n", m_count);
    }
    prnt("  Password:{}\n", m_count);
}

void sol_one_part_two(std::vector<std::string>& m_data) {
    int m_dial{50};
    int m_direction{0};
    int m_amount{0};
    int m_count{0};
    int m_delta{0};
    int m_next{0};

    prnt(" =>  Dir:{}  Amt:{}  Dial:{}  Count:{}\n", m_direction, m_amount, m_dial, m_count);

    for (auto line : m_data) {
        m_direction = (line[0]=='R') ? 1 : -1;      //short if to convert direction
        m_amount = stoi(line.substr(1));            //convert string amt to int
        prnt(" --> Dir:{} Amt:{}", m_direction, m_amount);

        m_delta = m_direction * m_amount;
        m_next = m_dial + m_delta;
        int m_clicks{0};

        if (m_next > 0) {
            m_clicks = m_next / 100;
            //prnt(" >0 clicks:{} ", m_clicks);
        } else if (m_next < 0) {
            m_clicks = ((-m_next + 100) / 100);
            if (m_dial == 0) m_clicks -= 1;
            //prnt(" <0 clicks:{}", m_clicks);
        } else {
            m_clicks = 1;
            //prnt(" ==0 clicks: {}", m_clicks);
        }

        m_count += m_clicks;
        m_dial = mod(m_next, 100);
        prnt(" Dial:{}  Count:{}  Next:{}\n", m_dial, m_count, m_next);
    }

    prnt("\n Password:{}\n", m_count);
}

void day_one_test() {
    std::vector<std::string> m_data = {"L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"};
    sol_one_part_one(m_data);
    sol_one_part_two(m_data);
}
void day_one_part_one() {
    std::vector<std::string> m_data = day_one_loader();
    sol_one_part_one(m_data);
}

void day_one_part_two() {
    std::vector<std::string> m_data = day_one_loader();
    sol_one_part_two(m_data);
}

#include "Player.h"
#include "Room.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

using std::string;

// ---------- helpers  ----------
string Player::to_lower(string s) { for (char& c : s) c = (char)std::tolower((unsigned char)c); return s; }
string Player::trim(string s) {
    const auto sp = [](unsigned char ch) {return std::isspace(ch) != 0;};
    auto a = std::find_if_not(s.begin(), s.end(), sp);
    auto b = std::find_if_not(s.rbegin(), s.rend(), sp).base();
    return (a >= b) ? string() : string(a, b);
}
string Player::canonical_dir(string d) {
    d = to_lower(std::move(d));
    if (d == "n" || d == "north") return "north";
    if (d == "s" || d == "south") return "south";
    if (d == "e" || d == "east")  return "east";
    if (d == "w" || d == "west")  return "west";
    return d;
}

// ---------- show location ----------
void Player::show_location() const {
    if (!room_) { std::cout << "You are not in any room.\n"; return; }
    std::cout << "\n[" << room_->name() << "]\n";
}

// ---------- look ----------
void Player::look() const {
    if (!room_) { std::cout << "You are not in any room.\n"; return; }

    std::cout << "\n[" << room_->name() << "]\n" << room_->description() << "\n";
    const auto& ex = room_->exits();
    if (ex.empty()) {
        std::cout << "You see no exits.\n";
    }
    else {
        std::cout << "Exits: ";
        bool first = true;
        for (const auto& kv : ex) {
            if (!first) std::cout << ", ";
            std::cout << kv.first;
            first = false;
        }
        std::cout << "\n";
    }
}

// ---------- go ----------
void Player::go(const std::string& dir_raw) {
    if (!room_) { std::cout << "You can't move right now.\n"; return; }

    const string dir = canonical_dir(dir_raw);
    if (Room* next = room_->get_exit(dir)) {
        room_ = next;
        show_location();         
    }
    else {
        std::cout << "There is no exit towards \"" << dir_raw << "\".\n";
    }
}

// ---------- commands  ----------
void Player::print_help() {
    std::cout
        << "Commands:\n"
        << "  help                - show this help\n"
        << "  look                - describe the current room\n"
        << "  go <dir>            - move (north/south/east/west or n/s/e/w)\n"
        << "  quit/exit           - exit\n";
}
bool Player::handle_command(const std::string& line_in) {
    string line = trim(to_lower(line_in)); if (line.empty()) return true;
    std::istringstream iss(line); string cmd; iss >> cmd;
    if (cmd == "quit" || cmd == "exit") { std::cout << "See you later!\n"; return false; }
    if (cmd == "help") { print_help(); return true; }
    if (cmd == "look") { look(); return true; }
    if (cmd == "go") { string d; iss >> d; if (d.empty()) std::cout << "Usage: go <north|south|east|west>\n"; else go(d); return true; }
    std::cout << "I don't understand. Type 'help'.\n"; return true;
}

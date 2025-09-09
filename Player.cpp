#include "Player.h"
#include "Room.h"
#include "Item.h"
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

// ---------- ACTIONS ----------------
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

void Player::look_item(const std::string& name) const {
    if (!room_) { std::cout << "You are not in any room.\n"; return; }

    if (Item* it = find_in_inventory(name)) {
        std::cout << "\n[" << it->name() << "]\n" << it->description() << "\n";
        return;
    }
    if (Item* it = room_->find_item(name)) {
        std::cout << "\n[" << it->name() << "]\n" << it->description() << "\n";
        return;
    }
    auto print_container = [](const Item& cont) {
        const auto & vec = cont.contents();
        if (vec.empty()) {
            if (cont.name() == std::string("bagpack"))
                std::cout << "The bagpack is empty\n";
            else
                std::cout << "The " << cont.name() << " is empty\n";
            return;
        }
        std::cout << "[" << cont.name() << "] contains: ";
        bool first = true;
        for (Item* x : vec) {
            if (!first) std::cout << ", ";
            std::cout << x->name();
            first = false;
        }
        std::cout << "\n";
    };
    if (Item* it = find_in_inventory(name)) {
        if (it->is_container()) { print_container(*it); return; }
        std::cout << "\n[" << it->name() << "]\n" << it->description() << "\n"; return;
    }
    if (Item* it = room_->find_item(name)) {
        if (it->is_container()) { print_container(*it); return; }
        std::cout << "\n[" << it->name() << "]\n" << it->description() << "\n"; return;
    }
    std::cout << "You don't see that item.\n";
}

Item* Player::find_in_inventory(const std::string& name) const {
    const string needle = to_lower(name);
    for (Item* it : bag_) {
        if (to_lower(it->name()) == needle) return it;
    }
    return nullptr;
}

Item * Player::bagpack_in_inventory() const {
    return find_in_inventory("bagpack");
}

void Player::inventory() const {
    if (bag_.empty()) {
        std::cout << "Inventory: (empty)\n";
        return;
    }
    std::cout << "Inventory (" << bag_.size() << "/" << kMaxInventory << "): ";
    bool first = true;
    for (Item* it : bag_) {
        if (!first) std::cout << ", ";
        std::cout << it->name();
        first = false;
    }
    std::cout << "\n";

    if (Item* bag = bagpack_in_inventory()) {
        const auto & inside = bag->contents();
        if (!inside.empty()) {
            std::cout << "Bagpack: ";
            bool f = true;
            for (Item* x : inside) {
                if (!f) std::cout << ", ";
                std::cout << x->name();
                f = false;
            }
            std::cout << "\n";
        }
    }
}

bool Player::has_item(const std::string& name) const {
    return find_in_inventory(name) != nullptr;
}

// ---------- go ----------
void Player::go(const std::string& dir_raw) {
    if (!room_) {
        std::cout << "You can't move right now.\n";
        return;
    }

    const string dir = canonical_dir(dir_raw);
    Room* next = room_->get_exit(dir);
    if (!next) {
        std::cout << "There is no exit towards \"" << dir_raw << "\".\n";
        return;
    }

    // If this exit is locked, require the needed item in inventory
    if (const std::string* needed = room_->required_item_for(dir)) {
        if (!has_item(*needed)) {
            std::cout << "The door is locked. You need the " << *needed << ".\n";
            return;
        }
    }

    if (const std::string* needed = room_->required_item_for(dir)) {
        if (!has_item(*needed)) {
            std::cout << "The door is locked. You need the " << *needed << ".\n";
            return;
        }
        room_->unlock_exit(dir);
    }

    room_ = next;
    show_location();
}

bool Player::add_to_inventory(Item& it) {
    if (std::find(bag_.begin(), bag_.end(), &it) != bag_.end()) return true;
    if (bag_.size() >= kMaxInventory) return false;
    bag_.push_back(&it);
    return true;
}

bool Player::remove_from_inventory(Item & it) {
    auto itp = std::find(bag_.begin(), bag_.end(), &it);
    if (itp == bag_.end()) return false;
    bag_.erase(itp);
    return true;
}

bool Player::take(const std::string& name) {
    if (!room_) return false;
    Item* it = room_->find_item(name);
    if (!it) { std::cout << "You don't see that item here.\n"; return false; }
    return take_item(*this, *room_, *it); 
}

bool Player::drop(const std::string & name) {
    Item * it = find_in_inventory(name);

    if (!it) {
        std::cout << "You are not carrying that.\n";
        return false;
    }

    if (to_lower(it->name()) == "bagpack" && it->is_container()) {
        it->clear_contents();
    }
    auto itp = std::find(bag_.begin(), bag_.end(), it);
    if (itp != bag_.end()) bag_.erase(itp);
    remove_from_inventory(*it);
    std::cout << "You drop the " << it->name() << ". It vanishes.\n";
    return true;
}

bool Player::place(const std::string & itemName) {
    Item * bag = bagpack_in_inventory();

    if (!bag || !bag->is_container()) {
        std::cout << "You need to be carrying the bagpack.\n";
        return false;
    }

    if (to_lower(itemName) == "bagpack") {
        std::cout << "You can't place the bagpack into itself.\n";
        return false;
    }
    
    Item * it = find_in_inventory(itemName);
    if (!it) {
        std::cout << "You are not carrying that.\n";
        return false;
    }

    remove_from_inventory(*it);
    bag->add_to_contents(*it);
    std::cout << "You place the " << it->name() << " into the bagpack.\n";
    return true;
}

// ---------- commands  ----------
void Player::print_help() {
    std::cout
        << "Commands:\n"
        << "  help/h              - show this help\n"
        << "  look                - describe the current room\n"
        << "  look <item>         - describe an item (room or inventory)\n"
        << "  inventory/inv/i     - list inventory (max 5 items)\n"
        << "  take <item>         - pick up an item from this room\n"
        << "  place <item>        - put an item into your bagpack (cannot be retrieved)\n"
        << "  drop <item>         - drop an item (it disappears)\n"
        << "  go <dir>            - move (north/south/east/west or n/s/e/w)\n"
        << "  quit/exit           - exit\n";
}
bool Player::handle_command(const std::string& line_in) {
    string line = trim(to_lower(line_in));
    if (line.empty()) return true;

    std::istringstream iss(line);
    string cmd; iss >> cmd;

    if (cmd == "quit" || cmd == "exit") { std::cout << "See you later!\n"; return false; }
    if (cmd == "help" || cmd == "h") { print_help(); return true; }

    if (cmd == "look") {
        string arg; if (iss >> arg) look_item(arg); else look();
        return true;
    }

    if (cmd == "inventory" || cmd == "inv" || cmd == "i") { inventory(); return true; }

    if (cmd == "go") {
        string dir; iss >> dir;
        if (dir.empty()) std::cout << "Usage: go <north|south|east|west>\n";
        else go(dir);
        return true;
    }

    if (cmd == "take" || cmd == "get" || cmd == "pick") {
        string what; iss >> what;
        if (what.empty()) std::cout << "Usage: take <item>\n";
        else take(what);
        return true;
    }

    if (cmd == "place") {
        string what; iss >> what;
        if (what.empty()) std::cout << "Usage: place <item>\n";
        else place(what);
        return true;
    }

    if (cmd == "drop") {
        string what; iss >> what;
        if (what.empty()) std::cout << "Usage: drop <item>\n";
        else drop(what);
        return true;
    }

    std::cout << "I don't understand. Type 'help'.\n";
    return true;
}

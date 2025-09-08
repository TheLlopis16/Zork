#pragma once
#include <string>

class Room;

class Player {
public:
    explicit Player(Room& start) : room_(&start) {}

    void show_location() const; 
    void look() const;           
    void go(const std::string& dir);

    bool handle_command(const std::string& line);

private:
    Room* room_ = nullptr;

    static std::string trim(std::string s);
    static std::string to_lower(std::string s);
    static std::string canonical_dir(std::string d);

    static void print_help();
};

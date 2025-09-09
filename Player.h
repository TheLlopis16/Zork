#pragma once
#include <string>
#include <vector>
#include <cstddef>

class Room;
class Item;

class Player {
public:
    explicit Player(Room& start) : room_(&start) {}

    void show_location() const; 
    void look() const;  
    void look_item(const std::string& name) const;
    void inventory() const;                 
    void go(const std::string& dir);
    bool take(const std::string& name);    
    bool add_to_inventory(Item& it);
    bool drop(const std::string& name);   

    bool handle_command(const std::string& line);

private:
    static constexpr std::size_t kMaxInventory = 5;

    Room* room_ = nullptr;
    std::vector<Item*> bag_;     

    static std::string trim(std::string s);
    static std::string to_lower(std::string s);
    static std::string canonical_dir(std::string d);

    Item* find_in_inventory(const std::string& name) const;
    static void print_help();

    bool has_item(const std::string& name) const;
};

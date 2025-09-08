#pragma once
#include <string>

class Player;
class Room;

class Item {
public:
    Item(std::string name, std::string description);

    const std::string& name() const noexcept { return name_; }
    const std::string& description() const noexcept { return description_; }

private:
    std::string name_;
    std::string description_;
};

// Implemented in item.cpp: move item from room to player's inventory (with capacity check).
bool take_item(Player& player, Room& from, Item& item);

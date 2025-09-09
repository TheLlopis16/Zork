#include "Item.h"
#include "Player.h"
#include "Room.h"
#include <iostream>

Item::Item(std::string name, std::string description)
    : name_(std::move(name)), description_(std::move(description)) {}

bool take_item(Player& player, Room& from, Item& item) {
    if (!player.add_to_inventory(item)) {
        std::cout << "Your inventory is full (5 items).\n";
        return false;
    }

    if (!from.remove_item(item)) {
        std::cout << "You can't take that right now.\n";
        return false;
    }
    std::cout << "You take the " << item.name() << ".\n";
    return true;
}

void Item::add_to_contents(Item & it) {
    if (std::find(contents_.begin(), contents_.end(), &it) == contents_.end())
        contents_.push_back(&it);
}

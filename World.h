#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Room.h"
#include "Item.h"

class World {
public:
    World() = default;

    Room& make_room(std::string name, std::string description);
    Item& make_item(std::string name, std::string description);

    Room& bootstrap();

    const std::vector<std::unique_ptr<Room>>& rooms() const noexcept { return rooms_; }
    const std::vector<std::unique_ptr<Item>>& items() const noexcept { return items_; }

private:
    std::vector<std::unique_ptr<Room>> rooms_;
    std::vector<std::unique_ptr<Item>> items_;
};

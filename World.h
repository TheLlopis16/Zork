#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Room.h"

class World {
public:
    World() = default;

    Room& make_room(std::string name, std::string description);
    Room& bootstrap();

    const std::vector<std::unique_ptr<Room>>& rooms() const noexcept { return rooms_; }

private:
    std::vector<std::unique_ptr<Room>> rooms_;
};

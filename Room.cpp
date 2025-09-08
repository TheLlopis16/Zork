#include "Room.h"
#include <utility>

Room::Room(std::string name, std::string description)
    : name_(std::move(name)), description_(std::move(description)) {}

void Room::add_exit(const std::string& canonical_dir, Room& destination) noexcept {
    exits_[canonical_dir] = &destination;
}

Room* Room::get_exit(const std::string& canonical_dir) const noexcept {
    auto it = exits_.find(canonical_dir);
    return (it == exits_.end()) ? nullptr : it->second;
}

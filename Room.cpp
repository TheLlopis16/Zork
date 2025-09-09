#include "Room.h"
#include "Item.h"
#include <utility>
#include <algorithm>
#include <cctype>

static std::string lower_copy(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

Room::Room(std::string name, std::string description)
    : name_(std::move(name)), description_(std::move(description)) {}

void Room::add_exit(const std::string& canonical_dir, Room& destination) noexcept {
    exits_[canonical_dir] = &destination;
}

Room* Room::get_exit(const std::string& canonical_dir) const noexcept {
    auto it = exits_.find(canonical_dir);
    return (it == exits_.end()) ? nullptr : it->second;
}

void Room::add_locked_exit(const std::string & canonical_dir, Room & destination, std::string required_item) noexcept {
    exits_[canonical_dir] = &destination;
    locks_[canonical_dir] = lower_copy(std::move(required_item));
}

const std::string * Room::required_item_for(const std::string & canonical_dir) const noexcept {
    auto it = locks_.find(canonical_dir);
    return (it == locks_.end()) ? nullptr : &it->second;
}

void Room::unlock_exit(const std::string& canonical_dir) noexcept {
    locks_.erase(canonical_dir);
}

// Items
void Room::add_item(Item& it) noexcept {
    if (std::find(items_.begin(), items_.end(), &it) == items_.end())
        items_.push_back(&it);
}

bool Room::remove_item(const Item& it) noexcept {
    auto itp = std::find(items_.begin(), items_.end(), &it);
    if (itp == items_.end()) return false;
    items_.erase(itp);
    return true;
}

Item* Room::find_item(const std::string& name) const {
    const std::string needle = lower_copy(name);
    for (Item* it : items_) {
        if (lower_copy(it->name()) == needle) return it;
    }
    return nullptr;
}

#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Item;

class Room {
public:
    Room(std::string name, std::string description);

    const std::string& name() const noexcept { return name_; }
    const std::string& description() const noexcept { return description_; }

    void add_exit(const std::string& canonical_dir, Room& destination) noexcept;
    Room* get_exit(const std::string& canonical_dir) const noexcept;
    const std::unordered_map<std::string, Room*>& exits() const noexcept { return exits_; }

    void add_locked_exit(const std::string& canonical_dir, Room& destination, std::string required_item) noexcept;
    const std::string* required_item_for(const std::string& canonical_dir) const noexcept;
    void unlock_exit(const std::string& canonical_dir) noexcept;

    // Items
    void add_item(Item& it) noexcept;
    bool remove_item(const Item& it) noexcept;
    Item* find_item(const std::string& name) const;
    const std::vector<Item*>& items() const noexcept { return items_; }

private:
    std::string name_;
    std::string description_;
    std::unordered_map<std::string, Room*> exits_;
    std::vector<Item*> items_;
    std::unordered_map<std::string, std::string> locks_;
};

#pragma once
#include <string>
#include <unordered_map>

class Room {
public:
    Room(std::string name, std::string description);

    const std::string& name() const noexcept { return name_; }
    const std::string& description() const noexcept { return description_; }

    void add_exit(const std::string& canonical_dir, Room& destination) noexcept;
    Room* get_exit(const std::string& canonical_dir) const noexcept;

    const std::unordered_map<std::string, Room*>& exits() const noexcept { return exits_; }

private:
    std::string name_;
    std::string description_;
    std::unordered_map<std::string, Room*> exits_;
};

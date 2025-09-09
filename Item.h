#pragma once
#include <string>
#include <vector>

class Player;
class Room;

class Item {
public:
    Item(std::string name, std::string description);

    const std::string& name() const noexcept { return name_; }
    const std::string& description() const noexcept { return description_; }

    // --- Container (simple) ---
    bool is_container() const noexcept { return is_container_; }
    void make_container() noexcept { is_container_ = true; }
    void add_to_contents(Item & it);         // añadir a la mochila
    void clear_contents() { contents_.clear(); }  // vaciar (p.ej. al soltar la mochila)
    const std::vector<Item*>&contents() const noexcept { return contents_; }

private:
    std::string name_;
    std::string description_;
    bool is_container_ = false;
    std::vector<Item*> contents_;
};

bool take_item(Player& player, Room& from, Item& item);

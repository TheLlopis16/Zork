#include "Item.h"
#include "Player.h"
#include "Room.h"
#include <iostream>

Item::Item(std::string name, std::string description)
    : name_(std::move(name)), description_(std::move(description)) {}

bool take_item(Player& player, Room& from, Item& item) {
    // Primero comprobamos si hay espacio de inventario.
    if (!player.add_to_inventory(item)) {
        std::cout << "Your inventory is full (5 items).\n";
        return false;
    }
    // Si se añadió al inventario, retiramos el objeto de la sala.
    if (!from.remove_item(item)) {
        std::cout << "You can't take that right now.\n";
        return false;
    }
    std::cout << "You take the " << item.name() << ".\n";
    return true;
}

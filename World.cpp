#include "World.h"

Room& World::make_room(std::string name, std::string description) {
    rooms_.push_back(std::make_unique<Room>(std::move(name), std::move(description)));
    return *rooms_.back();
}

Item& World::make_item(std::string name, std::string description) {
    items_.push_back(std::make_unique<Item>(std::move(name), std::move(description)));
    return *items_.back();
}

Room& World::bootstrap() {
    // --- Rooms ---
    Room& hall = make_room("Hall",
        "A small entry hall, with a door and a little table. To the west you see the living room.");
    Room& living = make_room("Living Room",
        "A big room with a sofa, a television, a ps4 and a coffee table with a key on it. To the east you return to the hall.");

    // --- Connections ---
    hall.add_exit("west", living);
    living.add_exit("east", hall);

    Item& key = make_item("key", "A small key with a label that says 'H1'.");
    living.add_item(key);

    return hall; // starting room
}

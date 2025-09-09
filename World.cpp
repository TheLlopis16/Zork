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
        "A small entry hall, with a door and a little table. To the west you see the living room; to the east a hallway.");
    Room& living = make_room("Living Room",
        "A big room with a sofa, a television, a ps5 and a coffee table with a key on it. To the east you return to the hall.");
    Room& hallway = make_room("Hallway",
        "A narrow corridor connecting rooms.");
    Room& room1 = make_room("Room 1",
        "A tidy bedroom with a small window.");

    // --- Connections ---
    // Hall <-> Living Room
    hall.add_exit("west", living);
    living.add_exit("east", hall);

    Item& key = make_item("key", "A small key with a label that says 'H1'.");
    living.add_item(key);

    // Hall <-> Hallway
    hall.add_exit("east", hallway);
    hallway.add_exit("west", hall);
    
    // Hallway -> Room 1 (LOCKED: requires "key"); Room 1 -> Hallway (free)
    hallway.add_locked_exit("north", room1, "key");
    room1.add_exit("south", hallway);

    return hall; // starting room
}

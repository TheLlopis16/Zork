#include "World.h"

Room& World::make_room(std::string name, std::string description) {
    rooms_.push_back(std::make_unique<Room>(std::move(name), std::move(description)));
    return *rooms_.back();
}

Room& World::bootstrap() {
    // --- Rooms ---
    Room& hall = make_room("Hall",
        "A small entry hall, with a door and a little table. To the west you see the living room.");
    Room& living = make_room("Living Room",
        "A big room with a sofa, a television, a ps4 and a coffee table. To the east you return to the hall.");

    // --- Connections ---
    hall.add_exit("west", living);
    living.add_exit("east", hall);

    return hall; // starting room
}

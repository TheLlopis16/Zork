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
        "A big room with a sofa, a television, a ps5 and a coffee table with a key on it.");
    Room& hallway = make_room("Hallway",
        "A narrow corridor connecting two rooms.");
    Room& room1 = make_room("Room 1",
        "A tidy bedroom with a small window. There is a bagpack in the bed");
    Room& room2 = make_room("Room 2",
        "A children's bedroom. Toys are scattered around (a ball, a teddybear and a little car).");

    // --- Connections ---
    // Hall <-> Living Room
    hall.add_exit("west", living);
    living.add_exit("east", hall);

    Item& key = make_item("key", "A small key with a label that says 'H1'.");
    living.add_item(key);

    // Hall <-> Hallway
    hall.add_exit("east", hallway);
    hallway.add_exit("west", hall);
    
    // Hallway -> Room 1 (requires "key")
    hallway.add_locked_exit("north", room1, "key");
    room1.add_exit("south", hallway);

    // Hallway <-> Room 2 (libre, sin llave)
    hallway.add_exit("south", room2);
    room2.add_exit("north", hallway);

    // Toys in Room 2
    Item & ball = make_item("ball", "A red rubber ball.");
    Item & teddy = make_item("teddybear", "A worn-out teddy bear with a missing eye.");
    Item & car = make_item("car", "A small blue toy car.");

    // Bagpack in Room 1 (container)
    Item & bagpack = make_item("bagpack", "A sturdy canvas bagpack with wide straps.");
    bagpack.make_container();

    room1.add_item(bagpack);
    room2.add_item(ball);
    room2.add_item(teddy);
    room2.add_item(car);

    return hall; // starting room
}

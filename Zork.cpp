#include <iostream>
#include "World.h"
#include "Player.h"

int main() {
    std::ios::sync_with_stdio(false);

    World world;
    Room& start = world.bootstrap(); 
    Player player(start);

    std::cout << "Welcome traveler. Type 'help' for commands.\n";
    player.show_location(); 

    std::string line;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, line)) break;
        if (!player.handle_command(line)) break;
    }
    return 0;
}

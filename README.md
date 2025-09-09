# Zork

Tiny text adventure in C++17. The game UI and commands are in English; this README explains everything you can do.

🗺️ World map

Hall (start)
west ⇄ Living Room
east ⇄ Hallway

Living Room: a key lies on the table.

Hallway
north ⇄ Room 1 (locked; first time requires the key, then it stays unlocked forever)
south ⇄ Room 2

Room 1: a bagpack (a simple container you can put items into, but not take out).

Room 2: ball, teddy, car (pickable).

When you move, only the room name is printed. The description is shown by look.

▶️ Build & run
Visual Studio (Windows)
Install the Desktop development with C++ workload
Download zip form Realease

Project Properties → C/C++ → Language: C++17.

Build and run.

🎮 Commands

help/h	                Show this help summary.
go <dir>	              Move: north/south/east/west or n/s/e/w.
look	                  Describe the current room (text, exits, visible items).
look <item>	            Describe an item. If it’s the bagpack, list its contents (or show “The bagpack is empty”).
inventory / inv / i	    Show your inventory (max 5 items). If you carry a bagpack with items inside, prints a second line listing them.
take <item>	            Pick up an item from the room (if there’s space in your inventory).
place <item>	          Put an item from your inventory into your bagpack. Items placed in the bagpack cannot be retrieved.
drop <item>	            Drop an item and it vanishes. Dropping the bagpack makes it disappear with all its contents.
quit	                  Exit the game.

Notes

Item names and directions are case-insensitive (Key = key).
Items inside the bagpack don’t count toward the 5-slot inventory (because place removes them from your inventory).
The Hallway → Room 1 door needs the key the first time; once opened, that exit is permanently unlocked.

🧠 Rules & behavior

Movement: entering a room prints only [Room Name].
look (room): prints description, exits, and visible items.

look <item>:
If the item is in your inventory or in the room: prints its description.
If it’s the bagpack: shows its contents or “The bagpack is empty”.

Inventory: up to 5 items.

Bagpack:
Simple container: you can place items into it, but cannot take them out.
You must carry the bagpack to use place.
drop bagpack deletes the bagpack and everything inside.

Key:
Found in Living Room.
Unlocks north exit in Hallway to Room 1.
After the first successful entry, the door remains unlocked forever.

🏁 Quick walkthrough
> look
(read Hall description)
> go west
[Living Room]
> look
(you see "key")
> take key
> go east
[Hall]
> go east
[Hallway]
> go north
[Room 1]     (first time required the key; now this exit stays unlocked)
> look
(you see a bagpack)
> take bagpack
> go south
[Hallway]
> go south
[Room 2]
> look
(you see ball, teddy, car)
> take ball
> inventory
Inventory (2/5): key, bagpack
> place ball
You place the ball into the bagpack.
> inventory
Inventory (2/5): key, bagpack
Bagpack: ball
> look bagpack
[bagpack] contains: ball
> drop bagpack
You drop the bagpack. It vanishes.
> inventory
Inventory (1/5): key

🗂️ Project layout
include/
  Item.h      // Item definition (also optional container behavior for bagpack)
  Player.h    // Commands and command parser
  Room.h      // Room, exits, items, and locks
  World.h     // Builds the map and initial items
src/
  Item.cpp    // Take logic and simple container helpers (add/clear)
  Player.cpp  // Command implementations
  Room.cpp    // Exits, permanent unlocks, item lookup
  World.cpp   // Map: Hall, Living Room, Hallway, Room 1, Room 2; key, bagpack, toys
  main.cpp    // Minimal loop delegating to Player

Links Github and Licence
  https://github.com/TheLlopis16/Zork
  https://choosealicense.com/licenses/gpl-3.0/

Have fun!

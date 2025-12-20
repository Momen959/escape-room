#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "../core/room.cpp"

using namespace std;

int roomID = 0;
bool seeded = false;

// Helper to pick a random room type, should not be called directly
// INTERMEDIATE = ~85%, TRAP = 10%, EXIT = 5% (at high depth)
// EXIT chance increases as depth decreases, reaching 100% at depth 1
RoomType pickRoomType(int depth) {
    if (depth <= 1) return EXIT;
    
    int roll = rand() % 100;
    // At higher depths: 85% INTERMEDIATE, 10% TRAP, 5% EXIT
    // As depth decreases, EXIT chance grows
    int exitChance = 5 + (5 - depth) * 5;  // depth 5+: 5%, depth 2: 20%
    if (exitChance < 5) exitChance = 5;
    if (exitChance > 30) exitChance = 30;
    
    if (roll < exitChance) {
        return EXIT;
    } else if (roll < exitChance + 10) {
        return TRAP;
    } else {
        return INTERMEDIATE;
    }
}

// Helper to recursively generate rooms, this is only called by createRooms, do not call this directly
Room* generateRoom(int depth, Room* parent = nullptr) {
    if (depth <= 0) return nullptr;

    string difficulties[] = {"EASY", "HARD"};
    string difficulty = difficulties[rand() % 2];
    
    RoomType type = pickRoomType(depth);
    
    Room* room = createRoom(roomID++, type, difficulty);

    // TRAP rooms lead back to parent room
    if (type == TRAP && parent->difficulty != "HARD") {
        room->next1 = parent;
        return room;
    } else if (type == TRAP && parent->difficulty == "HARD") {
        room->next1 = generateRoom(depth - 1, room);
    }

    // EXIT rooms don't lead anywhere
    if (type == EXIT) {
        return room;
    }

    room->next1 = generateRoom(depth - 1, room);

    // EASY rooms get a second path
    if (difficulty == "EASY") {
        room->next2 = generateRoom(depth - 1, room);
    }

    return room;
}

// This function creates the initial rooms starting from the entrance
// Use this function to intialize the "map" only ONCE at the beginning of the game
// This function deletes any existing rooms starting from entrance before creating a new map ONTO the entrance pointer, do not give it a copy of the entrance and expect it to modify the original pointer
void createRooms(Room*& entrance, int depth) {
    if (depth == 0) return;

    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    
    deleteAllRooms(entrance);
    entrance = createRoom(roomID++, ENTRANCE, "");

    // Entrance always has two paths
    entrance->next1 = generateRoom(depth);
    entrance->next2 = generateRoom(depth);
}
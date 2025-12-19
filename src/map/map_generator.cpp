#include <string>
#include <cstdlib>
#include "../core/room.cpp"

using namespace std;

int roomID = 0;

// Helper to pick a random room type, should not be called directly
// INTERMEDIATE = 80%, TRAP = 10%, EXIT = 10% (at high depth)
// EXIT chance increases as depth decreases, reaching 100% at depth 1
RoomType pickRoomType(int depth) {
    if (depth <= 1) return EXIT;
    
    int exitChance = 100 / depth;
    int roll = rand() % 100;
    if (roll < exitChance) {
        return EXIT;
    } else if (roll < exitChance + 80) {  // 80% of remaining goes to INTERMEDIATE
        return INTERMEDIATE;
    } else {
        return TRAP; 
    }
}

// Helper to recursively generate rooms, this is only called by createRooms, do not call this directly
Room* generateRoom(int depth, Room* parent = nullptr) {
    if (depth <= 0) return nullptr;

    string difficulties[] = {"EASY", "HARD"};
    string difficulty = difficulties[rand() % 2];
    
    RoomType type = pickRoomType(depth);
    int clueCount;

    // Determine clue count based on room type and difficulty, Easy rooms get 3, Hard rooms get 2, Others get none.
    switch (type) {
        case INTERMEDIATE:
            clueCount = (difficulty == "EASY") ? 2 : 3;
            break;
        case TRAP:
            clueCount = 1;
            break;
        case EXIT:
            clueCount = 0;
            break;
        default:
            clueCount = 0;
    }
    
    Room* room = createRoom(roomID++, type, difficulty, clueCount);

    // TRAP rooms lead back to parent room
    if (type == TRAP) {
        room->next1 = parent;
        return room;
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
void createRooms(Room* entrance, int depth) {
    if (depth == 0) return;    
    deleteAllRooms(entrance);
    entrance = createRoom(roomID++, ENTRANCE, "", 0);

    // Entrance always has two paths
    entrance->next1 = generateRoom(depth);
    entrance->next2 = generateRoom(depth);
}
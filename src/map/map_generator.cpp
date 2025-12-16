#include <string>
#include <cstdlib>
#include "../core/room.cpp"

using namespace std;

int roomID = 0;

// Helper to pick a random room type
// INTERMEDIATE = 70%, TRAP = 20%, EXIT = 10%
RoomType pickRoomType() {
    int roll = rand() % 100;
    if (roll < 70) return INTERMEDIATE;
    else if (roll < 90) return TRAP;
    else return EXIT;
}

Room* generateRoom(int depth) {
    if (depth <= 0) return nullptr;

    string difficulties[] = {"EASY", "HARD"};
    string difficulty = difficulties[rand() % 2];
    
    RoomType type = pickRoomType();
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

    // TRAP and EXIT rooms don't lead anywhere
    if (type == TRAP || type == EXIT) {
        return room;
    }

    room->next1 = generateRoom(--depth);

    // EASY rooms get a second path
    if (difficulty == "EASY") {
        room->next2 = generateRoom(--depth);
    }

    return room;
}

void createRooms(Room* entrance, int depth) {
    if (depth == 0) return;    
    deleteAllRooms(entrance);
    entrance = createRoom(roomID++, ENTRANCE, "", 0);

    // Entrance always has two paths
    entrance->next1 = generateRoom(depth);
    entrance->next2 = generateRoom(depth);
}
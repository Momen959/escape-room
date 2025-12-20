#ifndef ROOM_CPP
#define ROOM_CPP

#include <iostream>
#include <string>

using namespace std;

/******************************************************
 *  CORE DATA STRUCTURES – DO NOT CHANGE LIGHTLY
 *
 *  This file defines the fundamental building blocks
 *  of the Escape Room game. ALL other files depend on
 *  these structures.
 *
 *  IMPORTANT RULES FOR THE TEAM:
 *  - Do NOT redefine Room or Clue elsewhere
 *  - Do NOT use vectors, maps, or STL containers here
 *  - All room connections MUST use pointers only
 ******************************************************/

/***********************
 * CLUE STRUCTURE
 ***********************/
struct Clue {
    string problem;   // The question/puzzle shown to the player
    string solution;  // The correct answer
};

/***********************
 * ROOM TYPE ENUM
 * (Using enum for safety instead of raw strings)
 ***********************/
enum RoomType {
    ENTRANCE,
    INTERMEDIATE,
    EXIT,
    TRAP
};

/***********************
 * ROOM STRUCTURE (NODE)
 ***********************/
struct Room {
    int roomID;                // Unique ID for debugging & display
    RoomType roomType;         // ENTRANCE / INTERMEDIATE / EXIT / TRAP
    string difficulty;         // "EASY" or "HARD" (used only for INTERMEDIATE)

    // Linked-list pointers (doors)
    Room* next1;               // Always used
    Room* next2;               // Used ONLY for EASY rooms

    // Clue data
    Clue* clues;               // Dynamically allocated array of clues
    int clueCount;             // Number of clues (depends on room type)

    // State flags
    bool visited;              // Used for traversal & memory cleanup
    bool cleared;              // True if room puzzle already solved
};

/******************************************************
 * FUNCTION: createRoom
 *
 * Purpose:
 * - Dynamically allocates and initializes a Room node
 * - Used by the map generator ONLY
 *
 * Parameters:
 * - id         → unique room ID
 * - type       → room type enum
 * - difficulty → "EASY" / "HARD" or empty for non-intermediate
 * - clueCount  → number of clues required in this room
 *
 * Returns:
 * - Pointer to newly created Room
 ******************************************************/
Room* createRoom(int id, RoomType type, string difficulty, int clueCount) {
    Room* room = new Room;

    room->roomID = id;
    room->roomType = type;
    room->difficulty = difficulty;

    // Initialize pointers (doors closed initially)
    room->next1 = nullptr;
    room->next2 = nullptr;

    // Allocate clues dynamically
    room->clueCount = clueCount;
    room->clues = new Clue[clueCount];

    // Initialize state
    room->visited = false;
    room->cleared = false;

    return room;
}

/******************************************************
 * FUNCTION: resetVisitedFlags
 *
 * Purpose:
 * - Clears the visited flag for all rooms
 * - Useful before starting gameplay traversal
 *
 * Logic:
 * - Depth-first traversal using pointers
 * - Stops if room already unvisited
 ******************************************************/
void resetVisitedFlags(Room* room) {
    if (room == nullptr || room->visited == false)
        return;

    room->visited = false;

    resetVisitedFlags(room->next1);
    resetVisitedFlags(room->next2);
}

/******************************************************
 * FUNCTION: deleteAllRooms
 *
 * Purpose:
 * - Safely deallocates ALL rooms in the maze
 * - Prevents double deletion when multiple entrances
 *   point to the same room
 *
 * VERY IMPORTANT:
 * - Call this ONLY ONCE using ANY entrance pointer
 ******************************************************/
void deleteAllRooms(Room* room) {
    if (room == nullptr || room->visited)
        return;

    // Mark as visited to avoid double delete
    room->visited = true;

    // Recursively delete connected rooms
    deleteAllRooms(room->next1);
    deleteAllRooms(room->next2);

    // Free clue memory
    delete[] room->clues;

    // Free room itself
    delete room;
}

/******************************************************
 * GUIDANCE FOR OTHER MODULES (READ THIS)
 ******************************************************/

/*
==================== MAP GENERATOR ====================
File: src/map/map_generator.cpp

- Use createRoom(...) ONLY to create rooms
- Store entrance rooms as an array of Room* (size 4)
- All entrances must eventually point into the SAME maze

Example:
    Room* mazeStart = createRoom(...);
    entrance1->next1 = mazeStart;
    entrance2->next1 = mazeStart;

======================================================

==================== CLUE SYSTEM ======================
File: src/puzzle/clues.cpp

- Use room->clues[i].problem and solution
- room->clueCount tells you how many clues to ask
- Do NOT allocate or delete clues here

======================================================

==================== GAMEPLAY =========================
File: src/gameplay/gameplay.cpp

- Traverse rooms ONLY using next1 / next2
- EASY room → let player choose next1 or next2
- HARD/TRAP → auto go to next1
- EXIT room → end game

======================================================

==================== MAIN =============================
File: src/main.cpp

- Call map generator
- Let player select entrance
- Start gameplay loop
- Call deleteAllRooms(...) at the end

======================================================
*/

#endif
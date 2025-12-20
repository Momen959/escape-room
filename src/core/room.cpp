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
 * PUZZLE STRUCTURE
 ***********************/
struct Puzzle {
    string problem;   // The question/puzzle shown to the player
    string solution;  // The correct answer
    string hint;
    int points;
    int attempts;
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

    // Puzzle data
    Puzzle puzzle;             // Single puzzle for this room

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
 *
 * Returns:
 * - Pointer to newly created Room
 ******************************************************/
Room* createRoom(int id, RoomType type, string difficulty) {
    Room* room = new Room;

    room->roomID = id;
    room->roomType = type;
    room->difficulty = difficulty;

    // Initialize pointers (doors closed initially)
    room->next1 = nullptr;
    room->next2 = nullptr;

    // Initialize puzzle with empty values
    room->puzzle = {"", "", "", 0, 0};

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

==================== PUZZLE SYSTEM ======================
File: src/puzzle/clues.cpp

- Use room->puzzle.problem and solution
- Each room has exactly 1 puzzle
- Do NOT allocate or delete puzzles here

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
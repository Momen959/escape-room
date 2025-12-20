#include <iostream>
#include <string>
#include "../core/room.cpp"
#include "../puzzle/clues.cpp"

using namespace std;

/******************************************************
 * FUNCTION: displayRoomInfo
 *
 * Purpose:
 * - Shows current room information to player
 * - Displays room type, ID, and difficulty
 ******************************************************/
void displayRoomInfo(Room* room) {
    cout << "\n========================================" << endl;
    cout << "ROOM #" << room->roomID << endl;
    
    switch (room->roomType) {
        case ENTRANCE:
            cout << "Type: ENTRANCE" << endl;
            break;
        case INTERMEDIATE:
            cout << "Type: INTERMEDIATE (" << room->difficulty << ")" << endl;
            break;
        case TRAP:
            cout << "Type: TRAP ROOM" << endl;
            break;
        case EXIT:
            cout << "Type: EXIT - YOU ESCAPED" << endl;
            break;
    }
    
    cout << "========================================\n" << endl;
}

/******************************************************
 * FUNCTION: selectDoor
 *
 * Purpose:
 * - Let player choose between two doors in EASY room
 * - Returns pointer to selected room (next1 or next2)
 *
 * Parameters:
 * - room: Current EASY room with 2 doors
 *
 * Returns:
 * - Pointer to chosen next room
 ******************************************************/
Room* selectDoor(Room* room) {
    int choice;
    
    cout << "\nThis is an EASY room with TWO doors!" << endl;
    cout << "Choose your path:" << endl;
    cout << "  1. Door 1" << endl;
    cout << "  2. Door 2" << endl;
    cout << "Enter your choice (1 or 2): ";
    
    while (true) {
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input-Please enter 1 or 2: ";
            continue;
        }
        
        if (choice == 1 || choice == 2) {
            break;
        }
        
        cout << "Invalid choice! Please enter 1 or 2: ";
    }
    
    if (choice == 1) {
        cout << "You chose Door 1!" << endl;
        return room->next1;
    } else {
        cout << "You chose Door 2!" << endl;
        return room->next2;
    }
}

/******************************************************
 * FUNCTION: handleTrapRoom
 *
 * Purpose:
 * - Displays trap room message
 * - Applies penalty (optional - but we can extend it)
 * - Returns players to parent room automatically
 *
 * Parameters:
 * - room: Current TRAP room
 *
 * Returns:
 * - Pointer to parent room (room->next1)
 ******************************************************/
Room* handleTrapRoom(Room* room) {
    cout << "\n--TRAP ACTIVATED!--" << endl;
    cout << "You've triggered a trap!" << endl;
    cout << "You must solve a puzzle to escape." << endl;
    
    // The puzzle solving will be handled by the clues system
    // After solving, return to parent room
    solvePuzzle(room->puzzle);
    cout << "\nYou've been sent back to the previous room!" << endl;
    return room->next1;  // TRAP rooms point back to parent
}

/******************************************************
 * FUNCTION: playRoom
 *
 * Purpose:
 * - Main room interaction function
 * - Handles different room types appropriately
 * - Called by the main game loop
 *
 * Parameters:
 * - room: Current room being played
 *
 * Returns:
 * - Pointer to next room to visit
 *
 * IMPORTANT:
 * /// ya Youssef You are responsible for this part ///
 * - This function will call the clue system (not implemented yet)
 * - For now, it assumes rooms are automatically cleared
 ******************************************************/
Room* playRoom(Room* room) {
    displayRoomInfo(room);
    
    // Handle EXIT room
    if (room->roomType == EXIT) {
        cout << "\nCONGRATULATIONS MY FRIND!" << endl;
        cout << "You have successfully escaped the room!" << endl;
        return nullptr;  // Game ends
    }
    
    // Handle ENTRANCE room
    if (room->roomType == ENTRANCE) {
        cout << "You step through the entrance" << endl;
        cout << "The maze awaits you ahead.\n" << endl;
        
        // Entrance always has two paths, let player choose
        return selectDoor(room);
    }
    
    // Handle TRAP room
    if (room->roomType == TRAP) {
        /// ya Youssef You are responsible for this part ///
        // TODO: we will call clue system here to solve trap puzzle
        // For now, just handle the trap
        return handleTrapRoom(room);
    }
    
    // Handle INTERMEDIATE room
    if (room->roomType == INTERMEDIATE) {
        /// ya Youssef You are responsible for this part ///
        // TODO: Call clue system here to solve room puzzles
        // For now, I will assume that the room is cleared automatically
        
        cout << "You must solve the puzzle in this room to proceed." << endl;
        solvePuzzle(room->puzzle);
        // Mark room as cleared
        room->cleared = true;
        
        // Check difficulty and handle doors
        if (room->difficulty == "EASY") {
            // EASY rooms have 2 doors - let player choose
            return selectDoor(room);
        } else {
            // HARD rooms have only 1 door - automatic progression
            cout << "\nThere is only one way forward." << endl;
            return room->next1;
        }
    }
    
    // Default fallback (should never reach here)
    return room->next1;
}

/******************************************************
 * FUNCTION: startGame
 *
 * Purpose:
 * - Main game loop that orchestrates the entire gameplay
 * - Handles entrance selection and room progression
 *
 * Parameters:
 * - entrances: Array of 4 entrance room pointers
 *
 * Game Flow:
 * 1. Player selects entrance
 * 2. Loop through rooms until EXIT is reached
 * 3. Each room is played via playRoom()
 ******************************************************/
void startGame(Room* entrance) {
    Room* currentRoom = entrance;
    // Main game loop
    while (currentRoom != nullptr && currentRoom->roomType != EXIT) {
        currentRoom = playRoom(currentRoom);
    }
    
    // Handle exit room display
    if (currentRoom != nullptr && currentRoom->roomType == EXIT) {
        displayRoomInfo(currentRoom);
        cout << "\nCONGRATULATIONS!" << endl;
        cout << "You have successfully escaped the room!" << endl;
        cout << "Your total points: " << getUserPoints() << endl;
    }
    
    cout << "\nTHANK U FOR PLAYING" << endl;
}


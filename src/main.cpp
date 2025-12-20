#include <iostream>
#include "gameplay/gameplay.cpp"
#include "map/map_generator.cpp"

using namespace std;

void start() {
    cout << "Welcome to the Puzzle Adventure Game!" << endl;
    cout << "Enter your desired depth" << endl;
    int depth;
    cin >> depth;
    cout << "Generating map..." << endl;

    Room* entrance = createRoom(-1, ENTRANCE, "");
    createRooms(entrance, depth);
    setupPuzzles();
    // setupAllPuzzles(entrance);
  

    startGame(entrance);
}

int main() {
    start();
    return 0;
}
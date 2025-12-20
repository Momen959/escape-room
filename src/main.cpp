#include <iostream>
#include "puzzle/clues.cpp"
#include "gameplay/gameplay.cpp"
#include "map/map_generator.cpp"

using namespace std;

void start() {
    cout << "Welcome to the Puzzle Adventure Game!" << endl;
    cout << "Enter your desired depth" << endl;
    int depth;
    cin >> depth;
    cout << "Generating map..." << endl;

    Room* entrance1 = createRoom(-1, ENTRANCE, "", 0);
    Room* entrance2 = createRoom(-1, ENTRANCE, "", 0);
    Room* entrance3 = createRoom(-1, ENTRANCE, "", 0);
    Room* entrance4 = createRoom(-1, ENTRANCE, "", 0);

    Room* entrances[4] = {entrance1, entrance2, entrance3, entrance4};

    for (auto & entrance : entrances) {
        createRooms(entrance, depth);
        setupAllPuzzles(entrance);
    }

    startGame(entrances);
}

int main() {
    start();
    return 0;
}
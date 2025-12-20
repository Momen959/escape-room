#include <iostream>
#include <string>
#include <random>
#include "../core/room.cpp"

using namespace std;

random_device rd;
mt19937 gen(rd());
int userPoints = 0;

struct node {
    Puzzle data;
    node *next;
};

class Linkedlist {
public:
    node *head;
    int length = 0;

    Linkedlist() : head(nullptr), length(0) {}

    ~Linkedlist() {
        clear();
    }

    void addPuzzle(Puzzle value) {
        node *nodep = new node();
        nodep->data = value;
        nodep->next = head;
        head = nodep;
        length++;
    }

    Puzzle getRandomPuzzle(int position) {
        if (isEmpty() || position < 1 || position > length) return {"", "", "", 0, 0};

        Puzzle valueToReturn;
        if (position == 1) {
            node* deleter = head;
            valueToReturn = head->data;
            head = head->next;
            delete deleter;
            length--;
            return valueToReturn;
        }

        node* element_before = head;
        int counter = 1;
        while (counter != position - 1 && element_before != nullptr) {
            counter++;
            element_before = element_before->next;
        }

        if (element_before == nullptr || element_before->next == nullptr)
            return {"", "", "", 0, 0};

        node* deleted_node = element_before->next;
        valueToReturn = deleted_node->data;
        element_before->next = deleted_node->next;

        delete deleted_node;
        length--;
        return valueToReturn;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void clear() { 
        node* current = head;
        while (current != nullptr) {
            node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        length = 0;
    }
};

Puzzle easyBank[20] = {
    {"I have hands but cannot clap. What am I?", "clock", "I tell time", 10, 3},
    {"What has keys but no locks?", "piano", "It makes music", 10, 3},
    {"What has a head and a tail but no body?", "coin", "You spend it", 10, 3},
    {"What gets wetter the more it dries?", "towel", "You use it after a shower", 10, 3},
    {"What can you catch but not throw?", "cold", "Achoo!", 10, 3},
    {"What has words but never speaks?", "book", "You read it", 10, 3},
    {"What runs but never walks?", "water", "It flows", 10, 3},
    {"What can travel around the world while staying in a corner?", "stamp", "Put it on a letter", 10, 3},
    {"What has a neck but no head?", "bottle", "You drink from it", 10, 3},
    {"What comes down but never goes up?", "rain", "It falls from clouds", 10, 3},
    {"What is full of holes but still holds water?", "sponge", "You clean with it", 15, 3},
    {"What can you break without touching it?", "promise", "You make it with words", 15, 3},
    {"What has an eye but cannot see?", "needle", "Used for sewing", 15, 3},
    {"What begins with T, ends with T, and has T in it?", "teapot", "You brew tea in it", 15, 3},
    {"What has four fingers and a thumb but is not alive?", "glove", "You wear it on your hand", 15, 3},
    {"What building has the most stories?", "library", "Full of books", 15, 3},
    {"What invention lets you look right through a wall?", "window", "Made of glass", 15, 3},
    {"What has teeth but cannot bite?", "comb", "Used on hair", 15, 3},
    {"What is always in front of you but cannot be seen?", "future", "Tomorrow is part of it", 15, 3},
    {"What can fill a room but takes up no space?", "light", "Turn off the darkness", 15, 3}
};

Puzzle hardBank[20] = {
    {"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?", "echo", "Sound bouncing back", 25, 2},
    {"The more you take, the more you leave behind. What am I?", "footsteps", "You make them when walking", 25, 2},
    {"I am not alive, but I grow; I don't have lungs, but I need air; I don't have a mouth, but water kills me. What am I?", "fire", "Hot and bright", 25, 2},
    {"What disappears as soon as you say its name?", "silence", "Shh...", 25, 2},
    {"I have cities, but no houses. I have mountains, but no trees. I have water, but no fish. What am I?", "map", "Shows locations", 25, 2},
    {"What can run but never walks, has a mouth but never talks, has a head but never weeps, has a bed but never sleeps?", "river", "Flows to the ocean", 30, 2},
    {"I am taken from a mine, and shut up in a wooden case, from which I am never released. What am I?", "pencil", "Contains graphite", 30, 2},
    {"What word in the English language does the following: the first two letters signify a male, the first three letters signify a female, the first four letters signify a great, while the entire word signifies a great woman?", "heroine", "A female hero", 30, 2},
    {"What is seen in the middle of March and April that can't be seen at the beginning or end of either month?", "r", "It's a letter", 30, 2},
    {"A man is looking at a photograph of someone. His friend asks who it is. He replies: Brothers and sisters I have none. But that man's father is my father's son. Who is in the photograph?", "son", "His child", 30, 2},
    {"What English word has three consecutive double letters?", "bookkeeper", "Works with finances", 35, 2},
    {"I am a word of six letters. My first three letters refer to an automobile. My last three letters refer to a household animal. My whole word is a room used for study. What am I?", "carpet", "On the floor", 35, 2},
    {"What 5-letter word becomes shorter when you add two letters to it?", "short", "The opposite of long", 35, 2},
    {"Forward I am heavy, but backward I am not. What am I?", "ton", "A unit of weight", 35, 2},
    {"What comes once in a minute, twice in a moment, but never in a thousand years?", "m", "Look at the letters", 35, 2},
    {"I have branches, but no fruit, trunk or leaves. What am I?", "bank", "Where you keep money", 40, 2},
    {"The person who makes it, sells it. The person who buys it never uses it. The person who uses it never knows they're using it. What is it?", "coffin", "For the deceased", 40, 2},
    {"What word becomes smaller when you add the letters 'er' to it?", "small", "Opposite of big", 40, 2},
    {"I turn polar bears white and make you cry. I make guys have to pee and girls comb their hair. What am I?", "time", "Always moving forward", 40, 2},
    {"What has roots that nobody sees, is taller than trees, up up it goes, yet it never grows?", "mountain", "Very tall formation", 40, 2}
};

void fillRoomWithPuzzle(Room* room, Linkedlist& Easylist, Linkedlist& Hardlist) {
    if (room == nullptr || room->visited) return;

    room->visited = true;

    if ((room->difficulty == "HARD" || room->roomType == TRAP) && !Hardlist.isEmpty()) {
        uniform_int_distribution<int> dist(1, Hardlist.length);
        int randomIndex = dist(gen);
        room->puzzle = Hardlist.getRandomPuzzle(randomIndex);
    } else if (!Easylist.isEmpty()) {
        uniform_int_distribution<int> dist(1, Easylist.length);
        int randomIndex = dist(gen);
        room->puzzle = Easylist.getRandomPuzzle(randomIndex);
    }

    fillRoomWithPuzzle(room->next1, Easylist, Hardlist);
    fillRoomWithPuzzle(room->next2, Easylist, Hardlist);
}

void solvePuzzle(Puzzle puzzle) {
    cout << "\nPuzzle: " << puzzle.problem << endl;
    cout << "Enter your answer, enter h for hint: ";
    string answer;
    cin.ignore();
    cin >> answer;
    
    while (answer != puzzle.solution && puzzle.attempts > 0) {
        if (answer == "h") {
            cout << "Hint: " << puzzle.hint << endl;
            cin >> answer;
            continue;
        } 

        puzzle.attempts--;
        
        cout << "Incorrect! You have " << puzzle.attempts << " attempts left." << endl;
        if (puzzle.attempts == 1) {
            cout << "Hint: " << puzzle.hint << endl;
        }
        cout << "Try again: ";
        cin >> answer;
    }

    if (answer == puzzle.solution) {
        cout << "Correct! You've earned " << puzzle.points << " points." << endl;
        userPoints += puzzle.points;
        userPoints -= 10 * (3 - puzzle.attempts);
    } else {
        cout << "Incorrect! The correct answer was: " << puzzle.solution << endl;
    }
}

int getUserPoints() {
    return userPoints;
}

void setupAllPuzzles(Room* entrance) {
    Linkedlist Easy, Hard;

    for(int i = 0; i < 20; i++) {
        Easy.addPuzzle(easyBank[i]);
        Hard.addPuzzle(hardBank[i]);
    }

    fillRoomWithPuzzle(entrance, Easy, Hard);
    resetVisitedFlags(entrance);
}
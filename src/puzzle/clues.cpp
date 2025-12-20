#include <iostream>
#include <string>
#include <random>
#include "../core/room.cpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

struct node {
    Clue data;
    node *next;
};

class Linkedlist {
public:
    int length = 0;
    node *head;

    Linkedlist() : head(nullptr), length(0) {}

    ~Linkedlist() {
        clear();
    }

    void addClue(Clue value) {
        node *nodep = new node();
        nodep->data = value;
        nodep->next = head;
        head = nodep;
        length++;
    }

    Clue searchRandom(int position) {
        if (isEmpty() || position < 1 || position > length) return {"", ""};

        Clue valueToReturn;
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
            return {"", ""};

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

Clue easyBank[10] = {
    {"What has to be broken before you can use it?", "Egg"},
    {"I’m tall when I’m young, and I’m short when I’m old. What am I?", "Candle"},
    {"What month of the year has 28 days?", "All"},
    {"What is full of holes but still holds water?", "Sponge"},
    {"What question can you never answer yes to?", "Are you asleep"},
    {"What is always in front of you but can’t be seen?", "Future"},
    {"There’s a one-story house where everything is yellow. What color are the stairs?", "None"},
    {"What can you break, even if you never pick it up or touch it?", "Promise"},
    {"What goes up but never comes down?", "Age"},
    {"I shave every day, but my beard stays the same. Who am I?", "Barber"}
};

Clue hardBank[10] = {
    {"What has keys, but no locks; space, but no room; and allows you to enter, but never leave?", "Keyboard"},
    {"I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?", "Pencil lead"},
    {"What can run but never walks, has a mouth but never talks, has a head but never weeps, has a bed but never sleeps?", "River"},
    {"The more of this there is, the less you see. What is it?", "Darkness"},
    {"I follow you all day long, but when the night comes, I am gone. What am I?", "Shadow"},
    {"I have cities, but no houses. I have mountains, but no trees. I have water, but no fish. What am I?", "Map"},
    {"What belongs to you, but others use it more than you do?", "Your name"},
    {"I am first on earth, second in heaven, and I appear twice in a week. What am I?", "Letter E"},
    {"What has many teeth, but cannot bite?", "Comb"},
    {"What starts with T, ends with T, and has T in it?", "Teapot"}
};

void fillRoomWithClues(Room* room, Linkedlist& Easylist, Linkedlist& Hardlist) {
    if (room == nullptr || room->visited) return;

    room->visited = true;

    for (int i = 0; i < room->clueCount; i++) {
        if (room->difficulty == "HARD" && !Hardlist.isEmpty()) {
            uniform_int_distribution<int> dist(1, Hardlist.length);
            int randomIndex = dist(gen);
            room->clues[i] = Hardlist.searchRandom(randomIndex);
        } else if (!Easylist.isEmpty()) {
            uniform_int_distribution<int> dist(1, Easylist.length);
            int randomIndex = dist(gen);
            room->clues[i] = Easylist.searchRandom(randomIndex);
        }
    }

    fillRoomWithClues(room->next1, Easylist, Hardlist);
    fillRoomWithClues(room->next2, Easylist, Hardlist);
}

void setupAllPuzzles(Room* entrance) {
    Linkedlist Easy, Hard;

    for(int i = 0; i < 10; i++) {
        Easy.addClue(easyBank[i]);
        Hard.addClue(hardBank[i]);
    }

    resetVisitedFlags(entrance);
    fillRoomWithClues(entrance, Easy, Hard);
    resetVisitedFlags(entrance);
}
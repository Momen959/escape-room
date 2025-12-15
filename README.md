# 🧩 Escape Room Game (Linked List Based)

## 📌 Project Overview

This project is a **console-based Escape Room Game** designed for the **Data Structures** course. The core objective is to implement an escape room maze **entirely using linked-list nodes and pointers**, without relying on array-based maps or STL containers for navigation.

The game features:

* **4 Entrance Rooms** (multiple heads)
* **Randomly generated maze** of intermediate rooms
* **Difficulty-based navigation** (EASY / HARD)
* **2 Exit Rooms**
* Optional **Trap Rooms** for bonus marks

Each run of the program generates a **different maze layout**, ensuring replayability.

---

## 🧠 Core Data Structure Concept

* Each room is a **node** in a linked structure.
* Doors are implemented as **pointers** (`next1`, `next2`).
* EASY rooms have **two outgoing pointers**.
* HARD / TRAP / ENTRANCE rooms have **one outgoing pointer**.
* EXIT rooms have **no outgoing pointers**.

> The escape room is **not a single linked list**, but a **graph constructed using linked-list nodes**.

Multiple entrances point to the **same maze node**, allowing different starting points that merge into a shared maze.

---

## 📂 Project Folder Structure

```
escape-room-project/
│
├── src/
│   ├── core/
│   │   └── room.cpp          // Core structs & memory management
│   │
│   ├── map/
│   │   └── map_generator.cpp // Random maze creation & connections
│   │
│   ├── puzzle/
│   │   └── clues.cpp         // Clue logic, attempts, hints, scoring
│   │
│   ├── gameplay/
│   │   └── gameplay.cpp      // Game flow & room traversal
│   │
│   └── main.cpp              // Program entry point
│
└── README.md
```

> ⚠️ No `.h` files are used. All shared structures are defined in `room.cpp`.

---

## 👥 Team Roles & Responsibilities

### 👤 Member #1 — Data Structures & Memory (Foundation)

**Owner of:** `src/core/room.cpp`

Responsibilities:

* Define `Room` and `Clue` structs
* Implement dynamic memory allocation
* Handle safe deletion of shared rooms
* Ensure linked-list integrity

> This file is the **single source of truth** and must not be modified without team agreement.

---

### 👤 Member #2 — Map Generation & Randomization

**Owner of:** `src/map/map_generator.cpp`

Responsibilities:

* Create all rooms using `createRoom()`
* Assign room types (ENTRANCE / INTERMEDIATE / EXIT / TRAP)
* Randomly connect rooms using pointers
* Ensure all entrances eventually lead to exits

Key Concept:

* Multiple entrances point to the **same maze start room**.

---

### 👤 Member #3 — Clue & Puzzle System

**Owner of:** `src/puzzle/clues.cpp`

Responsibilities:

* Implement clue-solving logic
* Manage attempts and hint system
* Update player score

Rules:

* 3 attempts per clue
* Wrong answer → score penalty
* Hint → additional score penalty

---

### 👤 Member #4 — Gameplay Flow & Navigation

**Owner of:** `src/gameplay/gameplay.cpp`

Responsibilities:

* Handle entrance selection
* Traverse rooms using pointers
* Handle EASY room door choices
* Apply trap room penalties
* Detect EXIT and finish the game

---

### 👤 Member #5 — Integration, Testing & Documentation

**Owner of:** `src/main.cpp` and `README.md`

Responsibilities:

* Integrate all modules
* Ensure correct compilation
* Debug runtime issues
* Prepare final documentation

---

## 🔁 How All Parts Work Together

1. **Main Program** initializes the game
2. **Map Generator** creates and connects rooms
3. **Player chooses an entrance** (one of 4 heads)
4. **Gameplay loop** traverses rooms using pointers
5. **Clue system** controls door access
6. **Exit room** ends the game
7. **Memory cleanup** deletes all rooms safely

All navigation is done through `next1` and `next2` pointers.

---

## 🧹 Memory Management

Because multiple entrances can point to the same room:

* Each room contains a `visited` flag
* Recursive deletion deletes each room **once only**

Example cleanup:

```cpp
deleteAllRooms(entrances[0]);
```

---

## 🎮 Gameplay Summary

* Player selects an entrance
* Solves clues to unlock doors
* EASY rooms allow door choice
* HARD rooms force a single path
* TRAP rooms apply penalties
* EXIT room completes the game

---

## 🧪 Compilation & Running

Example (Linux / macOS):

```bash
g++ src/main.cpp -o escape_room
./escape_room
```

(Windows users may use MinGW or an IDE like Code::Blocks.)

---

## 🛠 Git Repository Setup Guide

### 1️⃣ Initialize Repository

```bash
git init
```

### 2️⃣ Create `.gitignore`

```
*.exe
*.out
*.o
.vscode/
.idea/
```

### 3️⃣ First Commit

```bash
git add .
git commit -m "Initial project structure and core data model"
```

### 4️⃣ Team Workflow (Recommended)

* Each member works on **their own file only**
* Commit messages should be clear:

  * `Add random map generation`
  * `Implement clue logic`
  * `Finish gameplay traversal`

---

## ✅ Academic Alignment

This project demonstrates:

* Correct linked list usage
* Dynamic memory management
* Pointer-based traversal
* Modular program design
* Randomized structure generation

---

## 📣 Final Notes

* Core requirements come first
* Bonus features are optional
* Simplicity and correctness are prioritized

Good luck — and enjoy building the escape room!

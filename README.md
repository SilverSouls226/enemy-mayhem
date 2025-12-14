# Enemy Mayhem
Enemy Mayhem is a **grid-based, turn-based C++ combat game** where the player must survive **10 escalating waves of enemies** on a constrained battlefield. Tactical lane selection, enemy positioning, and smart upgrades are key to victory.

---
## Index
* [Gameplay Overview](#gameplay-overview)
* [Enemy Types](#enemy-types)
* [Player Progression & Skills](#player-progression--skills)
* [Visual Interface](#visual-interface)
* [Screenshots](#screenshots)
* [Implementation Overview](#implementation-overview)
* [Run & Build](#run--build)
* [Notes](#notes)
* [License](#license)

---
## Gameplay Overview
* The battlefield is a fixed **3 × 8 grid**
* Enemies spawn on the **rightmost column** and advance left
* The player selects a **lane (row)** to attack each round
* Gameplay progresses in **turn-based rounds**:
  1. Player attacks
  2. Enemies move and/or attack
* The goal is to defeat all enemies across **10 waves**
* The game ends when the hero is defeated or all waves are cleared

---
## Enemy Types
Enemies behave differently based on class:
* **Melee Enemies**
  * Move one tile per round toward the player
  * Can only attack when they reach the player’s column
* **Archer Enemies**
  * Attack from range without moving
* **Mage Enemies**
  * Perform ranged, magic-enhanced attacks
Enemy composition changes with progression—early waves favor melee enemies, while later waves introduce more ranged threats.

---
## Player Progression & Skills
* Defeating enemies rewards **coins**
* Coins are spent in a **shop between waves**
* Upgrade paths include:
  * Health and max health
  * Damage and critical damage
  * Critical hit chance
  * Evasion (chance to dodge attacks)
  * Lifesteal (heal on hit)
  * Defence (damage reduction)
  * Looting (bonus coins)
* All skills have **hard caps** to maintain balance
* A bulk **combo upgrade** improves multiple stats at once
* The player can **switch hero class mid-game** (Archer ↔ Mage)

---
## Visual Interface
* The battlefield is rendered as a **text-based grid**
* Enemy types are represented symbolically:
  * `R` – Melee
  * `A` – Archer
  * `M` – Mage
* Each round displays:
  * Player stats
  * Enemy stats
  * Enemy positions
* Combat logs clearly show attacks, movement, and effects

---
## Screenshots
*(Placeholders — will be replaced with actual screenshots)*
```text
screenshots/
├── wave_1.png
├── mid_game.png
└── shop_screen.png
```
Example usage in this section once added:
```md
![Wave 1](screenshots/wave_1.png)
![Shop](screenshots/shop_screen.png)
```
Terminal screenshots are fully acceptable.

---
## Implementation Overview
* Built using **object-oriented C++**
* A shared `Character` base class defines core combat behavior
* Polymorphism is enforced through a pure virtual `attack()` method
* Behavior is composed using:
  * `Character` (combat stats)
  * `Skills` (passive abilities)
  * `Magic` (resource management)
* The battlefield is modeled as an explicit **2D grid**
* Enemies track their own spatial position and movement
* Difficulty scales per level using **mathematical progression**
* Enemy spawning uses **weighted randomness** based on level
* A centralized game loop manages combat rounds and progression
* A reusable table-rendering utility is used for terminal UI

---
## Run & Build
### Run (Windows)
A precompiled **Windows executable** is provided:
```text
enemy-mayhem.exe
```
Run it by double-clicking the file or from the command line.

---
### Build (Optional)
The current version is **Windows-specific** due to terminal handling
(e.g. use of `cls` to clear the console).
To build from source on Windows:
```bash
g++ main.cpp -o enemy_mayhem
```
Linux compatibility is planned, and a `.out` binary will be provided once
cross-platform terminal handling is implemented.

---
## Notes
* `TextTable.h` is an **AI-generated helper utility** used solely for formatting terminal output.
* All core gameplay logic, systems, and architecture were designed and implemented manually.

---
## License
This project is licensed under the **MIT License**.

---
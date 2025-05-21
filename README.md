![C/C++ CI](https://github.com/tommylin1212/AiFinal/workflows/C/C++%20CI/badge.svg)
# AiFinal Project

A simulation environment featuring agents with evolving traits, resource gathering, and survival mechanics.

## Core Features

*   **Agent System:**
    *   **Autonomous Agents:** Simulated entities with properties like position, velocity, health, and age.
    *   **Movement Behaviors:** Agents exhibit steering towards targets and a natural wandering behavior. Movement is governed by simulated physics (max speed, force).
    *   **Health & Sustenance:** Agents have health that changes based on interactions. They can consume items from the world.
    *   **DNA System:** Each agent possesses a "DNA" vector (a series of numbers). This system is foundational for heritable traits, potentially influencing movement, senses, or other behaviors.
    *   **Boundary Awareness:** Agents can detect and react to world boundaries.
*   **Player Control:**
    *   **Directly Controlled Agent:** Players take control of a special agent type.
    *   **Steering Input:** Players can directly steer their agent (left/right/straight).
    *   **Dead Reckoning:** The player agent can predict its near-future position.
*   **Item System:**
    *   **Consumable Items:** The world is populated with items that agents can interact with.
    *   **Types:** Items are distinguished by type, primarily "food" (beneficial) and "poison" (detrimental).
*   **World Management:**
    *   **Dynamic Environment:** The world initializes with a configurable number of agents and items (food/poison) within a set area.
    *   **Simulation Loop:** The world manages the simulation's progression, updating agent states and interactions.
    *   **Rendering:** Visual representation of agents and items using OpenGL/freeglut.
    *   **Multiple Players:** The simulation can support one or more player-controlled agents.

## Game Mechanics

*   **Objective (General):** The primary goal often revolves around survival. Players (and AI agents) need to manage their health by consuming food and avoiding poison.
*   **Win/Loss Conditions:** The simulation includes conditions for `playerWin` and `playerLost`, suggesting defined goals or failure states.
*   **Levels:** The system supports a `level` concept, allowing for progression through stages of potentially increasing difficulty or different environmental setups.
*   **Core Loop:** The game runs in a loop that processes agent actions, updates their states, handles interactions (like eating), and redraws the world.

## How to Play (Inferred)

1.  **Control:** As a player, you'll likely use specific keys to steer your agent (details to be confirmed from source or runtime).
2.  **Eat Food:** Navigate your agent to consume "food" items to replenish health.
3.  **Avoid Poison:** Steer clear of "poison" items, as these will likely deplete health.
4.  **Survive & Achieve Goals:** Try to keep your agent alive and achieve the specific objectives of the current level or game mode.

## Compilation & Running

To compile on Linux:

Ensure OpenGL is Installed:
```bash
sudo apt-get install freeglut3-dev
```

Clone this Repository (git must be installed):
```bash
git clone https://github.com/tommylin1212/AiFinal.git
```

Navigate to the Source Folder:
```bash
cd AiFinal/AiFinal/AiFinal/  # Note: This path might be AiFinal/AiFinal/ depending on where the makefile/solution is truly rooted for compilation
```

Compile and Run the Program:
```bash
g++ *.cpp -std=c++11 -lGL -lGLU -lglut && ./a.out
```
*(Ensure you are in the correct directory containing the .cpp files and makefile if one is used for compilation.)*

## Potential Future Features

*   **Advanced Agent AI:**
    *   Flocking, swarming, or schooling behaviors.
    *   Predator-prey dynamics.
    *   More sophisticated pathfinding (e.g., A* for complex environments).
*   **Evolutionary Algorithms:**
    *   Implement genetic algorithms where agent DNA is passed to offspring with mutation, allowing traits to evolve over generations.
    *   Selection mechanisms based on survival metrics (longevity, resources gathered, etc.).
*   **Expanded World & Items:**
    *   More item types with diverse effects (e.g., speed boosts, temporary invulnerability, vision enhancers).
    *   Environmental obstacles, different terrain types affecting movement or agent properties.
    *   Dynamic resource spawning and depletion.
*   **Enhanced Player Experience:**
    *   More complex and varied player objectives or quests.
    *   Unique player abilities or upgrades.
    *   Improved UI/HUD displaying more game state information (e.g., agent health, DNA summary, minimap).
*   **Technical Improvements:**
    *   Upgraded graphics (e.g., simple sprites or 3D models instead of basic geometric shapes).
    *   Sound effects for key game events.
    *   Save/load game functionality.
    *   Configuration files for game parameters.

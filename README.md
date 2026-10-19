# Educational Snake Game

A C++ and SFML game that combines grid-based Snake gameplay with multiplication challenges. Collect two numbers to form a question, then steer towards the correct answer while avoiding the walls and your own body.

**Author:** [Luke Warner](https://github.com/LukeWarner06)  
**Technologies:** C++20, SFML 3.0.0, Visual Studio 2022  
**Project context:** University project developed from a lecturer-provided starter framework.

## How to play

1. Collect a number to choose the first value in the multiplication question.
2. Collect another number to choose the second value.
3. Choose between the correct answer and two incorrect answers placed on the grid.
4. Continue answering questions as the game becomes more challenging.

A correct answer adds 100 points, grows the snake on its next movement and increases its speed. A wrong answer subtracts 100 points, shortens the snake and reduces its speed. Five consecutive correct answers double the current score. The range and quantity of numbers increase as you progress.

Hitting a wall or the snake's body ends the game. Losing too much length through wrong answers also ends the game.

## Controls

| Action | Key |
| --- | --- |
| Move | Arrow keys or W, A, S, D |
| Restart after game over | R |
| Quit | Close the game window |

## My contribution

The lecturer supplied the starter framework, initial main file and project setup. I wrote the following classes and their associated headers and source files:

| Class | Responsibility |
| --- | --- |
| [Snake](Snake/Snake.cpp) | Linked-list body representation, movement, direction handling, growth, shrinking and self-collision checks |
| [GameManager](Snake/GameManager.cpp) | Game flow, input handling, spawning, scoring, difficulty progression, rendering coordination and restart behaviour |
| [QuestionManager](Snake/QuestionManager.cpp) | Multiplication question states, answer calculation and on-screen question updates |
| [NumberManager](Snake/NumberManager.cpp) | Storage, drawing, lookup and removal of collectible numbers |
| [SoundManager](Snake/SoundManager.cpp) | Loading and playing named sound effects using SFML |

SFML provides the graphics, window, input and audio facilities.

## Technical highlights

- **Gameplay data structures:** The snake uses linked nodes, with explicit creation and deletion as its body changes.
- **State-based question logic:** An enum tracks whether the player is choosing the first number, second number or answer.
- **Gameplay and UI integration:** Question text, score and game-over information respond to gameplay state.
- **Random generation with constraints:** Generated number sets check for duplicate values, while spawn-position checks reject occupied grid cells.
- **Audio feedback:** Collection, correct answers, wrong answers and game over trigger sound effects.

### A development challenge

One challenge was preventing duplicate number values and overlapping spawn positions. I tracked generated values and checked candidate positions against occupied cells, generating alternatives when needed. I carried out repeated manual tests to check for duplicate values and overlapping numbers.

## Build and run on Windows

The repository contains a Visual Studio solution and bundled SFML 3.0.0 headers, libraries and DLLs.

### Requirements

- Visual Studio 2022 with the **Desktop development with C++** workload.
- MSVC v143 build tools and a Windows SDK.
- A build platform matching the bundled SFML libraries.

### Steps

1. Clone this repository or download and extract its ZIP.
2. Open `Snake.sln` in Visual Studio.
3. Select a configuration, starting with **Debug**, and the platform matching the bundled SFML libraries.
4. Set **Snake** as the startup project.
5. Under **Project Properties → Configuration Properties → Debugging**, set **Working Directory** to `$(ProjectDir)`. This allows the game to find `assets/` and `sounds/`.
6. Build the solution.
7. If Windows reports missing SFML DLLs, copy the matching DLLs from `Snake/SFML-3.0.0/bin/` beside the generated executable. Debug builds use the `-d-3.dll` files; Release builds use the corresponding files without `-d`.
8. Run from Visual Studio.

If running the executable outside Visual Studio, its working directory must contain the `assets/` and `sounds/` folders, or those folders must be copied into the launch directory.

These instructions reflect the checked-in project settings; a clean build on another computer has not yet been verified.

## Credits

- **Gameplay and supporting classes:** Luke Warner.
- **Starter framework and project setup:** Supplied by my university lecturer.
- **Graphics, windowing, input and audio library:** [SFML](https://www.sfml-dev.org/).
- Font and sound assets are included in the repository; asset creation is not claimed as part of my programming contribution.


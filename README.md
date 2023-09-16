# Pacman

This is a simple text-based implementation of the classic Pac-Man game in C++. It features a Pac-Man character that you control using the keyboard arrows ('A', 'S', 'D', 'W'). Your goal is to navigate Pac-Man through a maze, collect pellets, and avoid ghosts.

## How to Play

1. Clone or download this repository to your local machine.
2. Compile the code using your preferred C++ compiler.
3. Run the compiled executable to start the game.

## Gameplay

- Use the following keys to control Pac-Man:
  - 'A': Move left
  - 'S': Move down
  - 'D': Move right
  - 'W': Move up

- Collect pellets to earn points.
- Eating diamonds will make you invulnerable to the ghosts for 5 seconds.
- The game ends when you consume all of the pellets.
- You only have one life, so be careful not to get caught by the ghosts!

## Code Explanation

The code is organized into functions and provides the following functionalities:

- `startScreen()`: Displays game instructions at the beginning.
- `colorChange()`: Changes the console text color.
- `display()`: Handles the main game loop, including player movement, points, and ghost interactions.
- `clearScreen()`: Clears the console screen for smooth display updates.
- `endGame()`: Displays the final score and game duration upon completion.
- `check()`: Checks game conditions for victory or defeat.
- `direction()`: Handles ghost movement logic.
- `main()`: The entry point of the program, where the game is initialized.

## Screenshots

![image](https://github.com/WajeehaTahir/Pacman/assets/88159584/7ea4ae10-6499-4a2d-b692-ebb9942b7dab)

##
_Documented by ChatGPT._

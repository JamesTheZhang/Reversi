# Reversi Game and Bot README

## Introduction
This README provides an overview of a Reversi (Othello) game implementation in C, including a computer-controlled bot to play against. Reversi is a two-player strategy board game. The game is played on an 8x8 grid, where each player takes turns to place their color piece (black or white) on the board. The objective is to have the most pieces of your color on the board when the game ends.

## Game Features

### Game Initialization
The game initializes with an 8x8 game board, where the central four cells are occupied with two black and two white pieces. Players can choose their colors or have them assigned randomly. The game is played by entering row and column coordinates for each move.

### Legal Moves
The game checks for legal moves for each player, and only allows a player to make a move if a legal move is available. A legal move is one that results in flipping one or more opponent pieces to your color.

### Bot Player
The game includes a bot player that can make moves automatically. The bot uses the MiniMax algorithm with alpha-beta pruning to determine the best move. It evaluates game positions using a static evaluation function that considers factors such as piece parity, mobility, frontier disks, and stability.

### Time Control
The game includes a time control mechanism to limit the bot's thinking time for each move. If the bot exceeds a specified time limit, it makes the best move it has found up to that point.

### End of Game
The game ends when one of the players has no legal moves left or when the board is full. The player with the most pieces of their color on the board wins.

## Running the Game
To compile and run the game, you can use a C compiler such as `gcc`. Here's how to do it:

```bash
gcc -o reversi reversi.c
./reversi
```

Follow the on-screen instructions to play the game. You can specify whether you want to play as Black or White, and the bot will control the other color.

## Dependencies
The game does not have any external dependencies and should run on any system with a C compiler.

## Credits
This Reversi game and bot implementation was created by James Zhang, but it draws inspiration from various Reversi game algorithms and strategies found in online literature.

## License
This Reversi game implementation is provided under an open-source license. You are free to modify and distribute it as per the terms of the license.

For detailed information on how to play the game, its rules, and strategies, refer to the in-game instructions and comments within the source code. Enjoy playing Reversi!

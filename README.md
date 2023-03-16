# Reaction Game <!-- omit in toc -->
### A rendition of the basic Arduino starter project by [@BrownieMaar](https://github.com/BrownieMaar). <!-- omit in toc -->


### Table of contents <!-- omit in toc -->
- [About the project](#about-the-project)
- [Built with](#built-with)
- [Run the application](#run-the-application)
  - [Hardware Requirements](#hardware-requirements)
  - [Online Emulation](#online-emulation)
- [How to Play](#how-to-play)


## About the project

This project was the first larger-scale project I undertook after getting my Arduino Uno. In it, I not only managed to learn more about resistors, buttons, and LEDs, but also learned how to use classes in C++ and apply SOLID principles such as abstraction and composition.

## Built with

The application uses a modified version of __C++__ that includes libraries for controlling the __Arduino board__.

## Run the application

You can run the application either by building the necessary hardware or by emulating it online.

### Hardware Requirements

To run the program physically, you will need an Arduino Uno board and a breadboard (optional). For the score displays, two sets of 4 LEDs are required, along with matching resistors. (For my version, I used 2 green, 1 yellow, and 1 red LED per score display.) Another LED is required for the blinking light, along with a resistor, and two buttons, one for each player. 

Here's a summary of the required hardware:
* Arduino UNO board
* Breadboard (optional)
* 9 LEDs with resistors
* 2 pullup type buttons

Connect the main blinking lights to the board's 7th digital port. The A player's button goes to port 2, and their scoreboard to ports 3 to 6. Player B's button goes to port 12, and their scoreboard to ports 8 to 11. If you need an exact diagram, please refer to the [Online Emulation](#online-emulation) section.

### Online Emulation

To run the program without physical hardware, you can easily emulate it using various online applications. One such application is [wokwi.com](https://wokwi.com/projects/new/arduino-uno). You can try out the application [here](https://wokwi.com/projects/359376920100876289). To start the application, click on the green play icon above the board.

Note that in the online emulator, the very fast blinking of the LEDs may not be visible.

## How to Play

Each player can press their button when they are ready to play. If a player presses their button, the middle lights of their scoreboard light up. Once both players have pressed their buttons, the game begins.

The main light will light up randomly between 0 and 10 seconds. The first player to press their button after the light turns on gains a point. If a player presses their button before the light goes on, they lose a point if they have one. The first player to reach 4 points wins.

After a few seconds of the winner's scoreboard blinking, the game restarts, and the players can press their buttons again if they are ready to play another game.

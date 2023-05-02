#include <iostream>
#include "Game.h"
#include "SDL.h"

using namespace std;

/*
Final Project:
I hope this project fits your standards as I put a lot of time and effort into it.
Some things I could not add due to the time constraints I had and not knowing how I would
handle those aspects in the game. I tried to document my code to the best of my ability
and organize my code as well. As you stated I tried making a good piece of software and
worried less about the game part. Hope you enjoy!
*/

int main(int argc, char** argv) {
	Game game;
	game.init("Semester Project", 550, 250, 800, 600, false); // makes the game window and the base object to run the game

	while (game.running()) {
		game.handleEvents(); // handles the game events such as inputs from the player
		game.update(); // handles things happening in the game like gravity and moving the character and enemies
		game.render(); // handles rendering multiple objects to the screen
	}

	return 0;
}
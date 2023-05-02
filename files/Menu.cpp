#include "Menu.h"

Menu::Menu(string n, const char* path) { // makes the menu
	TTF_Init();
	name = n;
	font = TTF_OpenFont(path, 24);
}

void Menu::render(SDL_Renderer* rend) { // renders the menu
	for (auto& button : buttons) {
		button->draw(rend);
	}
	for (auto& text : texas) {
		SDL_RenderCopy(rend, text->getMessage(), NULL, text->getRect());
	}
}

void Menu::handleEvents(SDL_Event event) { // handles the menu events (Just the button being pressed nothing special)
	for (auto& button : buttons) {
		button->update(event);
	}
}

bool Menu::update() { // handles the updates of the menu such as waiting for the button to be pressed
	for (auto& button : buttons) {
		if (button->getPressed() && button->getName() == "start") {
			button->setPressed(false);
			return false;
		}
	}
	return true;
}

void Menu::addText(int xpos, int ypos, int width, int height, const char* text, SDL_Color color, SDL_Renderer* rend) { //adds text to the vector to be rendered
	Text* t = new Text(xpos, ypos, width, height, text, color, font, rend);
	texas.push_back(t);
}

void Menu::addButton(int xpos, int ypos, int width, int height, string name, SDL_Color color) { //adds button to the vector to be rendered
	Button* b = new Button(name, color, xpos, ypos, width, height);
	buttons.push_back(b);
}

string Menu::getName() { // gets the menu name
	return name;
}
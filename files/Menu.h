#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "Text.h"
#include <vector>
#include "Button.h"

using namespace std;

class Menu { // menu class, managed by menuManager
public:
	Menu(string n, const char* path);

	void render(SDL_Renderer* rend);
	void handleEvents(SDL_Event event);
	bool update();

	void addText(int xpos, int ypos, int width, int height, const char* text, SDL_Color color, SDL_Renderer* rend);
	void addButton(int xpos, int ypos, int width, int height, string name, SDL_Color color);

	string getName();


private:
	string name;
	TTF_Font* font;

	vector<Text*> texas;
	vector<Button*> buttons;
};
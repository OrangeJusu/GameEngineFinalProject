#pragma once
#include "SDL.h"
#include <string>

using namespace std;

class Button { // button class
public:
	Button(string n, SDL_Color c, int xpos, int ypos, int width, int height);

	void update(SDL_Event event);
	void draw(SDL_Renderer* rend);

	bool getPressed();
	void setPressed(bool val);

	string getName();
	SDL_Rect* getRect();
	SDL_Color getCurrentColor();
	SDL_Texture* getSprite();

private:
	string name;
	bool pressed;
	SDL_Rect* rect = new SDL_Rect;
	SDL_Color currentColor;
	SDL_Texture* sprite;
};
#pragma once
#include "SDL.h"
#include "Entity.h"

class Platform{ //platform class
public:
	Platform(float X, float Y, float W, float H);
	void draw(SDL_Renderer* rend);

	SDL_Rect* getRect();

private:
	int x, y, w, h;
	SDL_Rect* rect = nullptr;
};
#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"

class Bullet { // bullet class
public:

	Bullet(int x, int y, int s, SDL_Renderer* rend, bool e);
	~Bullet();

	void update();
	void render(SDL_Renderer* rend);

	int speed;
	Vector2D position;
	SDL_Rect* rect = new SDL_Rect{ 0, 0, 10, 10 };
	SDL_Texture* sprite;
	bool enemy;
};

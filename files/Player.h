#pragma once
#include "Entity.h"

class Player : public Entity { // player class, derived from entity
public:
	Player(int x, int y, int w, int h, float s, int hp, SDL_Renderer* rend);
	void jump();
	void moveLeft();
	void moveRight();
	void reset();
	bool isRunning = false;
};
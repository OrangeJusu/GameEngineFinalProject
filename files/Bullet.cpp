#include "Bullet.h"
#include <iostream>

using namespace std;

Bullet::Bullet(int x, int y, int s, SDL_Renderer* rend, bool e) { // makes the bullet
	position.x = x;
	position.y = y;
	speed = s;

	sprite = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);

	// set the render target to the texture so we can draw on it
	SDL_SetRenderTarget(rend, sprite);

	// set the drawing color to red
	SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);

	// draw a filled rectangle on the texture using the current drawing color
	SDL_RenderFillRect(rend, rect);

	// set the render target back to the default
	SDL_SetRenderTarget(rend, NULL);

	rect->x = position.x;
	rect->y = position.y;

	enemy = e;
}

Bullet::~Bullet() { // destroys the bullet and outputs where it died for testing purposes
	cout << position.x << endl;
}

void Bullet::update() { // moves the bullet forward and calls the deconstructor once it hits the wall
	position.x += 1 * speed;

	rect->x = position.x;

	if (position.x >= 800) {
		this->~Bullet();
	}
}

void Bullet::render(SDL_Renderer* rend) { // renders the bullet to the screen
	SDL_RenderCopy(rend, this->sprite, NULL, this->rect);
}

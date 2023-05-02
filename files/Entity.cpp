#include <iostream>
#include "SDL.h"
#include "Entity.h"
#include "SDL_image.h"

using namespace std;

Entity::Entity(float X, float Y, float W, float H, float S, SDL_Renderer* rend) { // makes the entity
	position = Vector2D(X, Y);
	velocity = Vector2D(0, 0);
	gravity = Vector2D(0, .05);

	width = W;
	height = H;
	speed = S;

	this->rect->x = X;
	this->rect->y = Y;
	this->rect->w = W;
	this->rect->h = H;

	setTexture(rend, 255, 0, 0);
}

bool Entity::update() { // update for the entity
	// Handle jumping
	if (isJumping && !isFalling) {
		velocity.y = -.5;
		isFalling = true;
		isJumping = false;
		onPlatform = false;
	}

	// Add gravity to velocity
	if (onPlatform == false) {
		velocity.y += .0005;
	}

	// Add velocity to position
	position = position + velocity;

	// Update the rect with the new position
	rect->x = static_cast<int>(position.x);
	rect->y = static_cast<int>(position.y);

	// Check if player is on the ground
	if (position.y > 600 - rect->h) {
		position.y = 600 - rect->h;
		velocity.y = 0;
		isFalling = false;
		onPlatform = false;
	}

	//Check if player is hitting the wall
	if (position.x > 800 - rect->w) {
		position.x = 800 - rect->w;
		velocity.x = 0;
	}
	else if (position.x < 0) {
		position.x = 0;
		velocity.x = 0;
	}

	return false;
}

void Entity::render(SDL_Renderer* rend) { // renders the entity
	if (this->sprite == NULL) {
		std::cout << "Error: sprite is null" << std::endl;
		return;
	}
	if (this->rect == NULL) {
		std::cout << "Error: rect is null" << std::endl;
		return;
	}
	SDL_RenderCopy(rend, this->sprite, NULL, this->rect);
}

// some getters

float Entity::getX() {
	return position.x;
}

float Entity::getY() {
	return position.y;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}

float Entity::getSpeed() {
	return speed;
}

SDL_Texture* Entity::getTexture() {
	return sprite;
}

SDL_Rect* Entity::getRect() {
	return rect;
}

// some setters

void Entity::setX(float X) {
	position.x = X;
	rect->x = X;
}

void Entity::setY(float Y) {
	position.y = Y;
	rect->y = Y;
}

void Entity::setWidth(float W) {
	width = W;
	rect->w = W;
}

void Entity::setHeight(float H) {
	height = H;
	rect->h = H;
}

void Entity::setSpeed(float S) {
	speed = S;
}

void Entity::setTexture(SDL_Renderer* rend, int r, int g, int b) { // sets the texture to be a square with whatever color it was given in params
	sprite = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

	// set the render target to the texture so we can draw on it
	SDL_SetRenderTarget(rend, sprite);

	// set the drawing color
	SDL_SetRenderDrawColor(rend, r, g, b, 255);

	// create a rectangle that covers the entire texture
	SDL_Rect rect = { 0, 0, width, height };

	// draw a filled rectangle on the texture using the current drawing color
	SDL_RenderFillRect(rend, &rect);

	// set the render target back to the default
	SDL_SetRenderTarget(rend, NULL);
}

bool Entity::collidesWith(const SDL_Rect* recA, const SDL_Rect* recB) { // called to see if it collides with anything and returns true if it did or is
	return SDL_HasIntersection(recA, recB);
}

void Entity::handleCollision() { // handles what happens after a collision with a platform
	velocity.y = 0;
	isFalling = false;
	isJumping = false;
	onPlatform = true;
}
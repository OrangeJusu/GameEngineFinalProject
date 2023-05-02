#pragma once
#include "Entity.h"
#include "Player.h"

Player::Player(int x, int y, int w, int h, float s, int hp, SDL_Renderer* rend) : Entity(x, y, w, h, speed, rend) { // makes the player
	position = Vector2D(x, y);
	velocity = Vector2D(0, 0);
	gravity = Vector2D(0, .05);

	width = w;
	height = h;
	speed = s;

	this->rect->x = x;
	this->rect->y = y;
	this->rect->w = w;
	this->rect->h = h;

	health = hp;

	enemy = false;

	setTexture(rend, 0, 0, 255);
}

void Player::jump() { // jump function for the player
	if (!isJumping) {
		isJumping = true;
		onPlatform = false;
	}
}

//moving left and right
void Player::moveLeft() {
	// Check if player is running
	if (isRunning) {
		speed = .275;
	}
	else {
		speed = .075;
	}

	// Move player left
	velocity.x = -speed;
}

void Player::moveRight() {
	// Check if player is running
	if (isRunning) {
		speed = .275;
	}
	else {
		speed = .075;
	}

	// Move player right
	velocity.x = speed;
}

// resets player position after every level
void Player::reset() {
	position.x = 50;
	position.y = 50;
}
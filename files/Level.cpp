#include <iostream>
#include "Level.h"
#include "SDL.h"
#include "Entity.h"
#include "Text.h"
#include <string>

using namespace std;

Level::Level(const char* n, SDL_Renderer* rend) {
	name = n;
	SDL_Color black = { 0, 0, 0 };
	TTF_Font* font = TTF_OpenFont("FreeSans.ttf", 24);
	pointText = new Text(750, 0, 50, 50, pointString.c_str(), black, font, rend);
}

// runs the update function for the level
bool Level::update(SDL_Renderer* rend) {
	// checks for collisions between each object current on the screen
	for (auto& entity : entities) {
		bool notCollided = true;
		entity->update();
		for (auto& platform : platforms) { // platform collision
			if (entity->collidesWith(entity->rect, platform->getRect())) {
				notCollided = false;
				entity->handleCollision();
			}
		}
		if (notCollided) {
			entity->onPlatform = false;
		}
		for (auto& bullet : bullets) { // bullet collision
			bullet->update();
			if (bullet->position.x >= 800) {
				RemoveBullet(bullet);
			}
			else {
				if (entity->collidesWith(entity->rect, bullet->rect)) { 
					if (entity->enemy != bullet->enemy) {
						entity->health -= 1;
						RemoveBullet(bullet);
						if (entity->health <= 0) {
							RemoveEntity(entity);
							addPoints(100, rend);
						}
					}
				}
			}
		}
	}
	for (auto& entity : entities) {
		for (auto& e : entities) {
			if (entity->enemy == false) {
				if (e->enemy == true) { // enemy collision
					if (entity->collidesWith(entity->rect, e->rect)) {
						entity->health -= 1;
						RemoveEntity(e);
						if (entity->health <= 0) {
							RemoveEntity(entity);
						}
					}
				}
			}
		}
	}
	for (auto& entity : entities) { // returns false if there are still enemies on the screen and returns true if there are none and loads the next level
		if (entity->enemy) {
			return false;
		}
	}
	return true;
}

void Level::render(SDL_Renderer* rend) {
	// renders everything in the platform vector, bullet vector, and entity vector
	if (entities.size() == 0) {
		return;
	}
	for (auto & entity : entities) {
		if (entity != nullptr) {
			entity->render(rend);
		}
	}
	for (auto& bullet : bullets) {
		if (bullet != nullptr) {
			bullet->render(rend);
		}
	}
	for (auto& plat : platforms) {
		if (plat != nullptr) {
			plat->draw(rend);
		}
	}
	
	// renders the points to the screen
	SDL_RenderCopy(rend, pointText->getMessage(), NULL, pointText->getRect());
}

const char* Level::GetName() { // name getter
	return name;
}

void Level::addPoints(int val, SDL_Renderer* rend) { // add points to the score
	points += val;
	pointString = to_string(points);
	pointText = new Text(750, 0, 50, 50, pointString.c_str(), { 0, 0, 0 }, TTF_OpenFont("FreeSans.ttf", 24), rend);
}

int Level::getPoints() { // gets points
	return points;
}

void Level::AddEntity(Entity* entity) { //add entity to the vector
	if (entity != nullptr) {
		entities.push_back(entity);
		cout << entity << endl;
	}
}

void Level::RemoveEntity(Entity* entity) { // removes entity from the vector
	auto it = find(entities.begin(), entities.end(), entity);
	if (it != entities.end()) {
		entities.erase(it);
		delete entity;
	}
}

vector<Entity*>& Level::GetEntities() { // getter for entity vector
	return entities;
}

void Level::AddPlatform(Platform* plat) { //add platform to the vector
	if (plat != nullptr) {
		platforms.push_back(plat);
	}
}

void Level::RemovePlatform(Platform* plat) { // removes platform from vector
	auto it = find(platforms.begin(), platforms.end(), plat);
	if (it != platforms.end()) {
		platforms.erase(it);
		delete plat;
	}
}

vector<Platform*>& Level::GetPlatforms() { // platform vector getter
	return platforms;
}

void Level::AddBullet(Bullet* b) { //add bullet to the vector
	bullets.push_back(b);
}

void Level::RemoveBullet(Bullet* b) { // removes bullet from the vector
	auto it = find(bullets.begin(), bullets.end(), b);
	if (it != bullets.end()) {
		bullets.erase(it);
		delete b;
	}
}

vector<Bullet*>& Level::GetBullets() { // gets the bullet vector
	return bullets;
}
#pragma once
#include <iostream>
#include "SDL.h"
#include "Vector2D.h"

using namespace std;

class Entity { // entity class and is the parent of player
public:
    Entity(float X, float Y, float W, float H, float S, SDL_Renderer* rend);

    bool update();
    void render(SDL_Renderer* rend);

    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getSpeed();
    SDL_Texture* getTexture();
    SDL_Rect* getRect();

    void setX(float X);
    void setY(float Y);
    void setWidth(float W);
    void setHeight(float H);
    void setSpeed(float S);
    void setTexture(SDL_Renderer* rend, int r, int g, int b);

    bool collidesWith(const SDL_Rect* recA, const SDL_Rect* recB);
    void handleCollision();

    float width;
    float height;
    float speed;
    int health = 1;
    SDL_Texture* sprite;
    SDL_Rect* rect = new SDL_Rect;
    Vector2D gravity;
    Vector2D velocity;
    Vector2D position;
    bool isFalling = false;
    bool isJumping = false;
    bool onPlatform = false;
    bool enemy = true;
};
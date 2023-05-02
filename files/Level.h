#pragma once
#include <vector>
#include "Entity.h"
#include "Platform.h"
#include "Bullet.h"
#include "Player.h"
#include "Text.h"

using namespace std;

// Basic level class

class Level {
public:
    Level(const char* n, SDL_Renderer* rend);

    bool update(SDL_Renderer* rend);
    void render(SDL_Renderer* rend);

    const char* GetName();

    void addPoints(int val, SDL_Renderer* rend);
    int getPoints();

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    vector<Entity*>& GetEntities();

    void AddPlatform(Platform* plat);
    void RemovePlatform(Platform* plat);
    vector<Platform*>& GetPlatforms();

    void AddBullet(Bullet* b);
    void RemoveBullet(Bullet* b);
    vector<Bullet*>& GetBullets();
    
    Level* next;
    Player* player;

private:
    const char* name;
    int points = 0;
    string pointString;
    Text* pointText;
    vector<Entity*> entities;
    vector<Platform*> platforms;
    vector<Bullet*> bullets;
};
#pragma once
#include "SDL.h"
#include "Level.h"
#include "Player.h"
#include "MenuManager.h"
#include "LevelManager.h"

using namespace std;

class Game {
public:
    Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // initializing the game window and starup tasks
    void handleEvents();
    void update();
    void render();
    bool running();
    // Variables for the game:
    SDL_Window* window; 
    SDL_Renderer* renderer;
    bool isRunning;
    Player* loadedPlayer;
    MenuManager menuManager;
    LevelManager levelManager;
    Menu* currentMenu;
    bool startingUp = true;
};
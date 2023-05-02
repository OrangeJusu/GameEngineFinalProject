#include "Game.h"
#include "SDL.h"
#include "Level.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "SDL_ttf.h"
#include "MenuManager.h"
#include "LevelManager.h"

Game::Game(){
    isRunning = false;
    renderer = nullptr;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    // checks if I want it in fullscreen or not (This game was not made for full screen I just added it for a base class for future projects)
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    //makes the screen

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }

    // Starts level generation

    levelManager.init(renderer);

    // Makes the player

    Player* p = new Player(50, 50, 50, 50, .075, 1, renderer);
    
    // Adds player to the starting level

    levelManager.getCurrentLevel()->AddEntity(p);
    levelManager.getCurrentLevel()->player = p;

    loadedPlayer = p;

    // sets up the menu screens for the game

    SDL_Color Red = { 255, 0, 0 };
    SDL_Color Green = { 0, 255, 0 };
    SDL_Color White = { 255, 255, 255 };
    
    menuManager.addMenu("deathScreen");
    menuManager.addMenu("main");
    menuManager.addMenu("winScreen");

    menuManager.setCurrentMenu("deathScreen");
    currentMenu = menuManager.getCurrentMenu();
    currentMenu->addText(150, 160, 500, 300, "You Died", Red, renderer);

    menuManager.setCurrentMenu("winScreen");
    currentMenu = menuManager.getCurrentMenu();
    currentMenu->addText(150, 160, 500, 300, "You Won", Green, renderer);

    menuManager.setCurrentMenu("main");
    currentMenu = menuManager.getCurrentMenu();
    currentMenu->addText(150, 10, 500, 300, "Grand Theft Blocko", Green, renderer);
    currentMenu->addText(290, 500, 200, 50, "Start", White, renderer);
    currentMenu->addButton(290, 500, 200, 50, "start", Red);
}

void Game::handleEvents() {

    // creates the base event to get input from the player
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // if at the starting menu only lets you click on the start button
        if (startingUp) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            }
            currentMenu->handleEvents(event);
        }
        else {
            // runs the basic inputs for the player such as moving side to side, running, jumping, and shooting
            switch (event.type) {
                // checks to see if window has been closed
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN: // checks for player input
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    loadedPlayer->moveLeft();
                    break;
                case SDLK_RIGHT:
                    loadedPlayer->moveRight();
                    break;
                case SDLK_UP:
                    loadedPlayer->jump();
                    break;
                case SDLK_f:
                    // makes a bullet to shoot at the enemy
                    levelManager.getCurrentLevel()->AddBullet(new Bullet((loadedPlayer->position.x + 20), (loadedPlayer->position.y + 20), 1, renderer, false));
                    break;
                case SDLK_LSHIFT:
                    loadedPlayer->isRunning = true;
                    break;
                }
                break;
            case SDL_KEYUP: // smooths out the movement by seeing when they player lets go
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    loadedPlayer->velocity.x = 0;
                    break;
                case SDLK_RIGHT:
                    loadedPlayer->velocity.x = 0;
                    break;
                case SDLK_LSHIFT:
                    loadedPlayer->isRunning = false;
                default:
                    break;
                }
            }
        }
    }
}

void Game::update() {
    // Like above locks in the game to only do this on the main menu until the start button is hit
    if (startingUp) {
        // updates the current menu until the button is clicked
        startingUp = currentMenu->update();
        if (startingUp == false) {
            levelManager.startTimer(renderer); // starts the game timer
        }
    }
    else {
        // runs the basic updates for the level
        levelManager.update(renderer);

        // what should happen when the player beats the game
        if (levelManager.getBeatGame()) {
            levelManager.stopTimer();
            menuManager.setCurrentMenu("winScreen");
            currentMenu = menuManager.getCurrentMenu();
            currentMenu->render(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(5000);
            // side note: I intended not to clear the screen for winning just to show the bullet hitting the final boss
            // to seem super cool

            // Sets up the main menu and resets the game
            menuManager.setCurrentMenu("main");
            currentMenu = menuManager.getCurrentMenu();
            startingUp = true;
            levelManager.reset(renderer);

            Player* p = new Player(50, 50, 50, 50, .075, 1, renderer);
            levelManager.getCurrentLevel()->AddEntity(p);
            levelManager.getCurrentLevel()->player = p;

            loadedPlayer = p;
        }
        // On losing clears the level of all entites, platforms, and bullets
        if (levelManager.getCurrentLevel()->GetEntities().empty() || loadedPlayer->health <= 0) {
            levelManager.getCurrentLevel()->GetEntities().clear();
            levelManager.getCurrentLevel()->GetPlatforms().clear();
            levelManager.getCurrentLevel()->GetBullets().clear();
        }
    }
}

void Game::render() {
    // renders all game objects to the screen

    // sets up the white backdrop
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (startingUp) {
        // renders the main menu
        currentMenu->render(renderer);
    }
    else {
        // renders the levels
        levelManager.render(renderer);

        // renders the death screen (I split the deathScreen and winScreen to different funtions so it looks a little cleaner)
        if (levelManager.getCurrentLevel()->GetEntities().empty() || loadedPlayer->health <= 0) {
            menuManager.setCurrentMenu("deathScreen");
            currentMenu = menuManager.getCurrentMenu();
            currentMenu->render(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);

            // Sets up the main menu and resets the game
            menuManager.setCurrentMenu("main");
            currentMenu = menuManager.getCurrentMenu();
            startingUp = true;
            levelManager.reset(renderer);

            Player* p = new Player(50, 50, 50, 50, .075, 1, renderer);
            levelManager.getCurrentLevel()->AddEntity(p);
            levelManager.getCurrentLevel()->player = p;

            loadedPlayer = p;
        }

    }
    SDL_RenderPresent(renderer);
}

// checks to see if game is running
bool Game::running() {
    return isRunning;
}
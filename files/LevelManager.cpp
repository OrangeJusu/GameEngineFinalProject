#include "LevelManager.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

LevelManager::LevelManager() {
	currentLevel = nullptr;
    font = TTF_OpenFont("FreeSans.ttf", 24);
    black = { 0, 0, 0 };
}

void LevelManager::init(SDL_Renderer* rend){
    // sets up the levels by reading it in from a file
    fstream file ("data.txt");
    string line;
    int levelNum = 0;
    Level* preLevel = nullptr;
    while (getline(file, line)) {
        if (line[0] == 'l') {
            addLevel(line.c_str(), rend);
            currentLevel = levels[levels.size() - 1];
            if (preLevel == nullptr) {
                preLevel = levels[0];
            }
            else {
                preLevel->next = levels[levels.size() - 1];
                preLevel = levels[levels.size() - 1];
            }
        }
        else if (line[0] == 'e') {
            vector<float> data;
            string number;
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == 'e') {
                    continue;
                }
                else if (c != ' ') {
                    number += c;
                }
                else {
                    data.push_back(stof(number));
                    number = "";
                }
            }
            if (number != "") {
                data.push_back(stof(number));
            }
            Entity* enemy = new Entity(data[0], data[1], data[2], data[3], data[4], rend);
            currentLevel->AddEntity(enemy);
        }
        else if (line[0] == 'p') {
            vector<float> data;
            string number;
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == 'p') {
                    continue;
                }
                else if (c != ' ') {
                    number += c;
                }
                else {
                    data.push_back(stof(number));
                    number = "";
                }
            }
            if (number != "") {
                data.push_back(stof(number));
            }
            Platform* platform = new Platform(data[0], data[1], data[2], data[3]);
            currentLevel->AddPlatform(platform);
        }
        else if (line[0] == 'b') {
            vector<float> data;
            string number;
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == 'b') {
                    continue;
                }
                else if (c != ' ') {
                    number += c;
                }
                else {
                    data.push_back(stof(number));
                    number = "";
                }
            }
            if (number != "") {
                data.push_back(stof(number));
            }
            Entity* enemy = new Entity(data[0], data[1], data[2], data[3], data[4], rend);
            enemy->health = 10;
            currentLevel->AddEntity(enemy);
        }
        else {
            continue;
        }
    }

    //sets the level pointer to level one
    getFirstLevel();
}

void LevelManager::reset(SDL_Renderer* rend) {
    // resets the level array to restart the game from a fresh state
    levels.clear();
    beatGame = false;
    init(rend);
}

void LevelManager::update(SDL_Renderer* rend) {
    // runs the updates the levels need and updates the timer
    updateTimer(rend);
    if (currentLevel->update(rend)) {
        getNextLevel(rend);
    }
}

void LevelManager::render(SDL_Renderer* rend) {
    // renders the current level and renders the timer on the screen
    currentLevel->render(rend);
    SDL_RenderCopy(rend, timerText->getMessage(), NULL, timerText->getRect());
}

void LevelManager::startTimer(SDL_Renderer* rend) {
    //starts the timer and sets up the timer to be shown on the screen
    startingTicks = SDL_GetTicks() / 1000;
    elapsedTicks = SDL_GetTicks() / 1000;

    string timeString = to_string(elapsedTicks - startingTicks);
    timerText = new Text(0, 0, 50, 50, timeString.c_str(), black, TTF_OpenFont("FreeSans.ttf", 24), rend);
}

void LevelManager::updateTimer(SDL_Renderer* rend) {
    // updates the timer once the second changes
    if (elapsedTicks != (SDL_GetTicks() / 1000)) {
        elapsedTicks = SDL_GetTicks() / 1000;
        timerText = new Text(0, 0, 50, 50, to_string(elapsedTicks - startingTicks).c_str(), black, TTF_OpenFont("FreeSans.ttf", 24), rend);
    }
}

void LevelManager::stopTimer() {
    // stops the timer
    finalTicks = elapsedTicks - startingTicks;
    elapsedTicks = 0;
    startingTicks = 0;
}

void LevelManager::addLevel(const char* n, SDL_Renderer* rend) {
    // adds a level to array
	Level* l = new Level(n, rend);
	levels.push_back(l);
}

void LevelManager::getFirstLevel() {
    // sets the pointer to the first level
	currentLevel = levels[0];
}

void LevelManager::getNextLevel(SDL_Renderer* rend) {
    // gets the next level in the sorted list and if there is no next level beat game is set equal to true
    if (currentLevel->next == nullptr) {
        beatGame = true;
        return;
    }
    Player* p = currentLevel->player;
    p->reset();
    int poi = currentLevel->getPoints();
	currentLevel = currentLevel->next;
    currentLevel->player = p;
    currentLevel->AddEntity(p);
    currentLevel->addPoints(poi, rend);
}

vector<Level*> LevelManager::getLevels() {
    // getter for the level array
	return levels;
}

Level* LevelManager::getCurrentLevel() {
    // getter for the current level
	return currentLevel;
}

bool LevelManager::getBeatGame() {
    // checks if player beat the game
    return beatGame;
}
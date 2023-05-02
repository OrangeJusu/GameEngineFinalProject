#pragma once
#include "Level.h"
#include <vector>

// Manages the levels and sets them up in a sorted list

class LevelManager {
public:
	LevelManager();

	void init(SDL_Renderer* rend);
	void reset(SDL_Renderer* rend);

	void update(SDL_Renderer* rend);
	void render(SDL_Renderer* rend);

	void startTimer(SDL_Renderer* rend);
	void updateTimer(SDL_Renderer* rend);
	void stopTimer();

	void addLevel(const char* n, SDL_Renderer* rend);
	void getFirstLevel();
	void getNextLevel(SDL_Renderer* rend);
	vector<Level*> getLevels();
	Level* getCurrentLevel();
	bool getBeatGame();

private:
	vector<Level*> levels;
	Level* currentLevel;
	bool beatGame = false;
	int startingTicks;
	int elapsedTicks;
	int finalTicks;
	Text* timerText;
	TTF_Font* font;
	SDL_Color black;
};
#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Text { // class for loading text to the screen
public:
	Text(int xpos, int ypos, int width, int height, const char* text, SDL_Color color, TTF_Font* font, SDL_Renderer* rend);

    SDL_Texture* getMessage();
    SDL_Rect* getRect();

private:
    SDL_Texture* message;
    SDL_Rect* message_rect = new SDL_Rect;
};
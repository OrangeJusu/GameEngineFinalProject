#include "Text.h"
#include <iostream>

using namespace std;

Text::Text(int xpos, int ypos, int width, int height, const char* text, SDL_Color color, TTF_Font* font, SDL_Renderer* rend) { // makes the text
	TTF_Init();

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
	message = SDL_CreateTextureFromSurface(rend, surfaceMessage);

	message_rect->x = xpos;
	message_rect->y = ypos;
	message_rect->w = width;
	message_rect->h = height;
}

// getters for text

SDL_Texture* Text::getMessage() { 
	return message;
}

SDL_Rect* Text::getRect() {
	return message_rect;
}
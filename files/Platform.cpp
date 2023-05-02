#include "Platform.h"
#include "SDL.h"

Platform::Platform(float X, float Y, float W, float H){ // makes a platform
	x = X;
	y = Y;
	w = W;
	h = H;

}

SDL_Rect* Platform::getRect() { // getter for the rect of the platform
	return rect;
}

void Platform::draw(SDL_Renderer* rend) { // renders the platform
	rect = new SDL_Rect{ x, y, w, h };

	SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
	SDL_RenderFillRect(rend, rect);
}

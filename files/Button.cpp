#include "Button.h"

Button::Button(string n, SDL_Color c, int xpos, int ypos, int width, int height) { // makes the button
	name = n;
	currentColor = c;

	rect->x = xpos;
	rect->y = ypos;
	rect->w = width;
	rect->h = height;
}

void Button::update(SDL_Event event) { // updates the button and sees if it has been clicked or not
	SDL_Point mousePosition;

	// Mouse click coords from event handler
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;

	if (SDL_PointInRect(&mousePosition, rect)) {
		currentColor = { 200, 0, 0 }; // if its being hovered adds a highlight to the button
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			setPressed(true); // once clicked it is pressed
		}
	}
	else {
		currentColor = { 255, 0, 0 }; // resets button color
	}
}

void Button::draw(SDL_Renderer* rend) { // renders the button
	SDL_SetRenderDrawColor(rend, currentColor.r, currentColor.g, currentColor.b, 255);
	SDL_RenderFillRect(rend, rect);
}

// its just getters and setters

bool Button::getPressed() {
	return pressed;
}

void Button::setPressed(bool val) {
	pressed = val;
}

string Button::getName() {
	return name;
}

SDL_Rect* Button::getRect() {
	return rect;
}

SDL_Color Button::getCurrentColor() {
	return currentColor;
}

SDL_Texture* Button::getSprite() {
	return sprite;
}
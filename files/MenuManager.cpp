#include "MenuManager.h"

MenuManager::MenuManager() { //makes menuManager
	currentMenu = nullptr;
}

Menu* MenuManager::getCurrentMenu() { // gets the current menu
	return currentMenu;
}

void MenuManager::setCurrentMenu(string name) { // sets the current menu
	for (auto& menu : menus) {
		if (menu->getName() == name) {
			currentMenu = menu;
			break;
		}
	}
}

void MenuManager::addMenu(string name) { // adds a menu to the menu vector
	TTF_Init();
	Menu* m = new Menu(name, "FreeSans.ttf");
	menus.push_back(m);
}

void MenuManager::deleteMenu(Menu* menu) { // deletes a menu from the vector
	auto it = find(menus.begin(), menus.end(), menu);
	if (it != menus.end()) {
		menus.erase(it);
		delete menu;
	}
}

vector<Menu*> MenuManager::getMenus() { // gets the menu vector
	return menus;
}
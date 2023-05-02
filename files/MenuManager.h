#pragma once
#include "Menu.h"
#include <vector>

class MenuManager { // class for managing the menus
public:
	MenuManager();

	Menu* getCurrentMenu();
	void setCurrentMenu(string name);

	void addMenu(string name);
	void deleteMenu(Menu* menu);
	vector<Menu*> getMenus();


private:
	Menu* currentMenu;

	vector<Menu*> menus;
};
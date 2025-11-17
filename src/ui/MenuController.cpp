#include "MenuController.hpp"

#include <SDL2/SDL.h>
#include <iostream>

MenuController::MenuController() : renderer_("Puyo Menu") {
	imageManager_.initTextures(renderer_.getSDLRenderer());
}

MenuOption	MenuController::run() {
	bool	quitRequested = false;

	while (!quitRequested) {
		renderer_.render(menu_, imageManager_);

		bool	shouldQuit = false;
		if (menu_.handleEvents(shouldQuit)) {
			if (shouldQuit) {
				return MenuOption::EXIT;
			}
			return menu_.getSelectedOption();
		}
		SDL_Delay(16);
	}
	return MenuOption::EXIT;
}

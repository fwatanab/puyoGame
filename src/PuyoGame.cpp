#include "PuyoGame.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Game.hpp"
#include "MenuController.hpp"
#include "Menu.hpp"

PuyoGame::PuyoGame() : sdlInitialized_(false), imgInitialized_(false) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
	}
	sdlInitialized_ = true;

	const int	imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		cleanup();
		throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
	}
	imgInitialized_ = true;
}

PuyoGame::~PuyoGame() {
	cleanup();
}

void	PuyoGame::cleanup() {
	if (imgInitialized_) {
		IMG_Quit();
		imgInitialized_ = false;
	}
	if (sdlInitialized_) {
		SDL_Quit();
		sdlInitialized_ = false;
	}
}

void	PuyoGame::run() {
	try {
		bool	isRunning = true;
		while (isRunning) {
			MenuController	menuController;
			MenuOption	choice = menuController.run();

			if (choice == MenuOption::EXIT) {
				break;
			}

			if (choice == MenuOption::DUO) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Duo Mode", "デュオモードは未実装です。", nullptr);
				continue;
			}

			Game	game;
			if (!game.init()) {
				std::cerr << "Game initialization failed." << std::endl;
				break;
			}
			game.run();
		}
	} catch (const std::exception& e) {
		std::cerr << "Unhandled exception: " << e.what() << std::endl;
	}
}

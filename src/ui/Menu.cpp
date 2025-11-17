#include "Menu.hpp"

#include <algorithm>

Menu::Menu() : selectedIndex_(0) {
	items_.push_back({MenuOption::SOLO, MENU_ITEM_SOLO_MODE});
	items_.push_back({MenuOption::DUO, MENU_ITEM_DUO_MODE});
	items_.push_back({MenuOption::EXIT, MENU_ITEM_EXIT});
}

MenuOption	Menu::getSelectedOption() const {
	if (items_.empty()) {
		return MenuOption::EXIT;
	}
	return items_[selectedIndex_].option;
}

int	Menu::getSelectedIndex() const {
	return selectedIndex_;
}

const std::vector<MenuItem>&	Menu::getItems() const {
	return items_;
}

bool	Menu::handleEvents(bool& quitRequested) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quitRequested = true;
			return true;
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_UP:
					selectedIndex_ = (selectedIndex_ - 1 + static_cast<int>(items_.size())) % static_cast<int>(items_.size());
					break;
				case SDLK_DOWN:
					selectedIndex_ = (selectedIndex_ + 1) % static_cast<int>(items_.size());
					break;
				case SDLK_ESCAPE:
					selectedIndex_ = static_cast<int>(items_.size()) - 1;
					return true;
				case SDLK_RETURN:
				case SDLK_SPACE:
					return true;
			}
		}
	}
	return false;
}

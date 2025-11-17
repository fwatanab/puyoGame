#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GeneratedConfig.hpp"

enum class	MenuOption {
	SOLO,
	DUO,
	EXIT
};

struct	MenuItem {
	MenuOption	option;
	std::string	label;
};

class	Menu {
	public:
		Menu();

		MenuOption	getSelectedOption() const;
		int	getSelectedIndex() const;
		const std::vector<MenuItem>&	getItems() const;

		bool	handleEvents(bool& quitRequested);

	private:
		std::vector<MenuItem>	items_;
		int	selectedIndex_;
};

#endif

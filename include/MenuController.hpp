#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "Menu.hpp"
#include "MenuRenderer.hpp"
#include "ImageManager.hpp"

class	MenuController {
	public:
		MenuController();

		MenuOption	run();
	private:
		MenuRenderer	renderer_;
		ImageManager	imageManager_;
		Menu	menu_;
};

#endif

#ifndef MENURENDERER_HPP
#define MENURENDERER_HPP

#include "Renderer.hpp"
#include "ImageManager.hpp"
#include "Menu.hpp"
#include "TextRenderer.hpp"
#include <string>

class	MenuRenderer : public Renderer {
	public:
		MenuRenderer(const std::string& title);

		void	render(const Menu& menu, const ImageManager& imageManager);

	private:
		void	renderOption(const MenuItem& item, const SDL_Rect& rect, bool isSelected, const ImageManager& imageManager);

		SDL_Color	highlightColor_;
		SDL_Color	textColor_;
};

#endif

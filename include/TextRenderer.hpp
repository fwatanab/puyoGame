#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <SDL2/SDL.h>
#include <string>

class	TextRenderer {
	public:
		static void	renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int scale, SDL_Color color);
};

#endif

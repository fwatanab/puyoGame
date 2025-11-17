#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "GeneratedConfig.hpp"

class	Renderer {
	public:
		Renderer(const std::string& title);
		virtual ~Renderer();

		void	present(); // 描画を反映
		void	clear();   // 描画領域をクリア

		SDL_Renderer*	getSDLRenderer() const;


	protected:
		SDL_Window*	window_;
		SDL_Renderer*	renderer_;
};

#endif

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Board.hpp"
#include "PuyoPair.hpp"
#include "SpriteSheet.hpp"
#include <stdexcept>

class	Renderer {
	public:
		Renderer(const std::string& title);
		~Renderer();

		// 描画関数
		void	renderBoard(const Board& board, const SpriteSheet& spriteSheet);
		void	renderPuyoPair(const PuyoPair& pair, const SpriteSheet& spriteSheet);
		void	present(); // 描画を反映
		void	clear();   // 描画領域をクリア

		SDL_Renderer*	getSDLRenderer() const;


	private:
		SDL_Window*	window_;
		SDL_Renderer*	renderer_;

		SDL_Rect	getDestRect(int x, int y) const;
};

#endif

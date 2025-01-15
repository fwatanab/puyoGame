#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Board.hpp"
#include "SpriteSheet.hpp"
#include "PuyoPair.hpp"
#include "PuyoClearer.hpp"
#include "ChainManager.hpp"

class	Game {
	public:
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;
		static const int PUYO_SIZE = 32;
		Game();
		~Game();
		bool	init();
		void	run();
		void	handleEvents();
		void	update();
		void	render();
		void	close();
	private:
		SDL_Window*	window_;
		SDL_Renderer*	renderer_;
		bool	isRunning_;

		Board*	board_;
		SpriteSheet	spriteSheet_;
		PuyoPair*	puyoPair_;
		ChainManager*	chainManager_;
		PuyoFinder	finder_;
		PuyoClearer	clearer_;
};

#endif

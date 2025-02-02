#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Board.hpp"
#include "GameRenderer.hpp"
#include "ImageManager.hpp"
#include "PuyoPair.hpp"
#include "PuyoClearer.hpp"
#include "ChainManager.hpp"
#include "GeneratedConfig.hpp"

class	Game {
	public:
		Game();
		~Game();
		bool	init();
		void	run();
		void	handleEvents();
		void	update();
		void	render();
		void	close();
	private:
		bool	isRunning_;

		GameRenderer*	renderer_;
		ImageManager	imageManager_;
		Board*	board_;
		PuyoPair*	puyoPair_;
		ChainManager*	chainManager_;
		PuyoFinder	finder_;
		PuyoClearer	clearer_;
};

#endif

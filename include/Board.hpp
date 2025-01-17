#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include <Puyo.hpp>
#include "SpriteSheet.hpp"
#include "PuyoPair.hpp"
#include "GeneratedConfig.hpp"
#include <random>

class	Board {
	public:
		Board();
		~Board();

		void	init();

		PuyoColor	getRandomColor();

		Puyo&	getGrid(int x, int y);
		const Puyo&	getGrid(int x, int y) const;

		bool	canMoveDown(const PuyoPair& pair) const;
		bool	canMoveDown(const Puyo& puyo, const Puyo& otherPuyo) const;
		bool	canMoveLeft(const PuyoPair& pair) const;
		bool	canMoveRight(const PuyoPair& pair) const;
		bool	canRotate(const PuyoPair& pair) const;

		void	forceDrop(Puyo& puyo, Puyo& otherPuyo);
		void	fixPuyo(const Puyo& puyo);
		bool	isGameOver() const;
	private:
		Puyo	grid_[BOARD_WIDTH][BOARD_HEIGHT];
};

#endif

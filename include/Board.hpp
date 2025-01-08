#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include <Puyo.hpp>
#include <SpriteSheet.hpp>
#include <PuyoPair.hpp>
#include <random>

class	Board {
	public:
		static const int	WIDTH = 6;
		static const int	HEIGHT = 13;
		static const int	PUYO_SIZE = 32;
		static const int	BLOCK_SIZE = 32;

		Board();
		~Board();

		void	init();
		SDL_Rect	getSrcRect(PuyoColor color, SpriteSheet& spriteSheet);
		SDL_Rect	getDestRect(int x, int y);
		void	draw(SDL_Renderer* renderer, SpriteSheet& spriteSheet);
		void	drawBlock(SDL_Renderer* renderer, SpriteSheet& spriteSheet);

		PuyoColor	getRandomColor();

		bool	canMoveDown(const PuyoPair& pair) const;
		bool	canMoveDown(const Puyo& puyo, const Puyo& otherPuyo) const;
		bool	canMoveLeft(const PuyoPair& pair) const;
		bool	canMoveRight(const PuyoPair& pair) const;
		bool	canRotate(const PuyoPair& pair) const;

		void	forceDrop(Puyo& puyo, Puyo& otherPuyo);
		void	fixPuyo(const Puyo& puyo);
		bool	isGameOver() const;
	private:
		Puyo	grid_[WIDTH][HEIGHT];
};

#endif

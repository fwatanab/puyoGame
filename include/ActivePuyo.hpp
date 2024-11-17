#ifndef ACTIVEPUYO_HPP
#define ACTIVEPUYO_HPP

#include <Puyo.hpp>

class	ActivePuyo : public Puyo {
	public:
		ActivePuyo(PuyoColor color = PuyoColor::EMPTY, int startX = 3, int startY = 0);

		// 移動処理
		void	moveLeft();
		void	moveRight();
		void	moveDown();

		// 回転処理
		void	rotate();
};

#endif

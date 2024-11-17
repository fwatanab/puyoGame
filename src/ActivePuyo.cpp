#include <ActivePuyo.hpp>

ActivePuyo::ActivePuyo(PuyoColor color, int startX, int startY) : Puyo(color, startX, startY) {}

void	ActivePuyo::moveLeft() {
	x_--;
}

void	ActivePuyo::moveRight() {
	x_++;
}

void	ActivePuyo::moveDown() {
	y_++;
}

void	ActivePuyo::rotate() {
	// 回転処理
}

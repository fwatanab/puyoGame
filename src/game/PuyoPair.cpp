#include <PuyoPair.hpp>
#include <Board.hpp>

PuyoPair::PuyoPair(PuyoColor color1, PuyoColor color2, int startX, int startY) : primaryPuyo_(Puyo(color1, startX, startY)), secondaryPuyo_(Puyo(color2, startX, startY - 1)), rotationState_(0) {}

void	PuyoPair::moveLeft() {
	primaryPuyo_.setX(primaryPuyo_.getX() - 1);
	secondaryPuyo_.setX(secondaryPuyo_.getX() - 1);
}

void	PuyoPair::moveRight() {
	primaryPuyo_.setX(primaryPuyo_.getX() + 1);
	secondaryPuyo_.setX(secondaryPuyo_.getX() + 1);
}

void	PuyoPair::moveDown() {
	primaryPuyo_.setY(primaryPuyo_.getY() + 1);
	secondaryPuyo_.setY(secondaryPuyo_.getY() + 1);
}

void	PuyoPair::rotate() {
	if (rotationState_ >= 3) {
		rotationState_ = 0;
	} else {
		rotationState_++;
	}
	switch(rotationState_) {
		case 0:
			secondaryPuyo_.setPosition(secondaryPuyo_.getX() + 1, secondaryPuyo_.getY() - 1);
			break;
		case 1:
			secondaryPuyo_.setPosition(secondaryPuyo_.getX() + 1, secondaryPuyo_.getY() + 1);
			break;
		case 2:
			secondaryPuyo_.setPosition(secondaryPuyo_.getX() - 1, secondaryPuyo_.getY() + 1);
			break;
		case 3:
			secondaryPuyo_.setPosition(secondaryPuyo_.getX() - 1, secondaryPuyo_.getY() - 1);
			break;
	}
}

bool	PuyoPair::areBothFixed(const Board& board) const {
	if (!board.canMoveDown(primaryPuyo_, secondaryPuyo_)
		&& !board.canMoveDown(secondaryPuyo_, primaryPuyo_)) {
		return true;
	}
	return false;
}

Puyo&	PuyoPair::getPrimaryPuyo() {
	return primaryPuyo_;
}

const Puyo&	PuyoPair::getPrimaryPuyo() const {
	return primaryPuyo_;
}

Puyo&	PuyoPair::getSecondaryPuyo() {
	return secondaryPuyo_;
}

const Puyo&	PuyoPair::getSecondaryPuyo() const {
	return secondaryPuyo_;
}

int	PuyoPair::getRotate() const {
	return rotationState_;
}

#include <PuyoPair.hpp>

PuyoPair::PuyoPair(PuyoColor color1, PuyoColor color2, int startX, int startY) : primaryPuyo_(Puyo(color1, startX, startY)), secondaryPuyo_(Puyo(color2, startX, startY - 1)), rotationState_(0) {}

void	PuyoPair::moveLeft() {
	primaryPuyo_.setX(primaryPuyo_.getX() - 1);
	secondaryPuyo_.setX(secondaryPuyo_.getX() - 1);
}

void	PuyoPair::moveRight() {
	primaryPuyo_.setX(primaryPuyo_.getX() + 1);
	secondaryPuyo_.setX(secondaryPuyo_.getX() + 1);
}

void	PuyoPair::moveDown(Puyo& puyo) {
	int	x = puyo.getX();
	int	y = puyo.getY();
	puyo.setPosition(x, y + 1);
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

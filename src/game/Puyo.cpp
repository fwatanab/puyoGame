#include <Puyo.hpp>

Puyo::Puyo() : color_(PuyoColor::EMPTY), x_(0), y_(0), fixed_(false) {}

Puyo::Puyo(PuyoColor color, int x, int y) : color_(color), x_(x), y_(y), fixed_(false) {}

Puyo::~Puyo() {}

PuyoColor	Puyo::getColor() const {
	return color_;
}

void	Puyo::setColor(PuyoColor color) {
	color_ = color;
}

int	Puyo::getX() const {
	return x_;
}

int	Puyo::getY() const {
	return y_;
}

void	Puyo::setX(int x) {
	x_ = x;
}

void	Puyo::setY(int y) {
	y_ = y;
}

void	Puyo::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

bool	Puyo::isFixed() const {
	return fixed_;
}

void	Puyo::fix() {
	fixed_ = true;
}

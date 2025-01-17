#include <Board.hpp>

Board::Board() {
	init();
}

Board::~Board() {}

void	Board::init() {
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			grid_[x][y] = Puyo(PuyoColor::EMPTY, x, y);
		}
	}
}

PuyoColor	Board::getRandomColor() {
	static std::random_device	rd; // ランダムデバイス
	static std::mt19937	gen(rd()); // メルセンヌ・ツイスタ生成器
	static std::uniform_int_distribution<>	dist(0, 4); // 0から3の範囲でランダムな整数

	// インデックスに基づいて色を返す
	return static_cast<PuyoColor>(dist(gen));
}

Puyo&	Board::getGrid(int x, int y) {
	return grid_[x][y];
}

const Puyo&	Board::getGrid(int x, int y) const {
	return grid_[x][y];
}

bool	Board::canMoveDown(const PuyoPair& pair) const {
	// ペアのぷよを取得
	const Puyo&	p1 = pair.getPrimaryPuyo();
	const Puyo&	p2 = pair.getSecondaryPuyo();

	int	x1 = p1.getX();
	int	y1 = p1.getY();
	int	x2 = p2.getX();
	int	y2 = p2.getY();

	if (y1 + 1 >= HEIGHT || grid_[x1][y1 + 1].getColor() != PuyoColor::EMPTY) {
		return false;
	}
	if (y2 + 1 >= HEIGHT || grid_[x2][y2 + 1].getColor() != PuyoColor::EMPTY) {
		return false;
	}

	return true;
}

bool	Board::canMoveDown(const Puyo& puyo, const Puyo& otherPuyo) const {
	int	x = puyo.getX();
	int	y = puyo.getY();

	// 他方のぷよが真下にいる場合でも、さらに下が空いていれば移動可能
	if (x == otherPuyo.getX() && y + 1 == otherPuyo.getY()) {
		return otherPuyo.getY() + 1 < HEIGHT && grid_[x][otherPuyo.getY() + 1].getColor() == PuyoColor::EMPTY;
	}

	if (y + 1 >= HEIGHT || grid_[x][y + 1].getColor() != PuyoColor::EMPTY) {
		return false;
	}
	return true;
}

bool	Board::canMoveLeft(const PuyoPair& pair) const {
	int	x1 = pair.getPrimaryPuyo().getX();
	int	y1 = pair.getPrimaryPuyo().getY();
	int	x2 = pair.getSecondaryPuyo().getX();
	int	y2 = pair.getSecondaryPuyo().getY();
	if ((x1 - 1 >= 0 && grid_[x1 - 1][y1].getColor() == PuyoColor::EMPTY)
		&& (x2 - 1 >= 0 && grid_[x2 - 1][y2].getColor() == PuyoColor::EMPTY)) {
		return true;
	}
	return false;
}

bool	Board::canMoveRight(const PuyoPair& pair) const {
	int	x1 = pair.getPrimaryPuyo().getX();
	int	y1 = pair.getPrimaryPuyo().getY();
	int	x2 = pair.getSecondaryPuyo().getX();
	int	y2 = pair.getSecondaryPuyo().getY();
	if ((x1 + 1 < WIDTH && grid_[x1 + 1][y1].getColor() == PuyoColor::EMPTY)
		&& (x2 + 1 < WIDTH && grid_[x2 + 1][y2].getColor() == PuyoColor::EMPTY)) {
		return true;
	}
	return false;
}

bool	Board::canRotate(const PuyoPair& pair) const {
	int	x = pair.getPrimaryPuyo().getX();
	int	y = pair.getPrimaryPuyo().getY();
	int	rotate = pair.getRotate();
	if ((rotate == 0 && x + 1 < WIDTH && grid_[x + 1][y].getColor() == PuyoColor::EMPTY)
		|| (rotate == 1 && y + 1 < HEIGHT && grid_[x][y + 1].getColor() == PuyoColor::EMPTY)
		|| (rotate == 2 && x - 1 >= 0 && grid_[x - 1][y].getColor() == PuyoColor::EMPTY)
		|| (rotate == 3 && y - 1 >= 0 && grid_[x][y - 1].getColor() == PuyoColor::EMPTY)) {
		return true;
	}
	return false;
}

void	Board::forceDrop(Puyo& puyo, Puyo& otherPuyo) {

	while (canMoveDown(puyo, otherPuyo)) {
		puyo.setY(puyo.getY() + 1); // 落下処理
	}
}

void	Board::fixPuyo(const Puyo& puyo) {
	int	x = puyo.getX();
	int	y = puyo.getY();
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		grid_[x][y] = puyo; // グリッドに固定
	}
}

bool	Board::isGameOver() const {
	if (grid_[3][0].getColor() != PuyoColor::EMPTY) {
		return true;
	}
	return false;
}

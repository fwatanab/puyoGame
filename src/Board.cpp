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

SDL_Rect Board::getSrcRect(PuyoColor color, SpriteSheet& spriteSheet) {
	SDL_Rect	srcRect;

	switch (color) {
		case PuyoColor::RED:
			// 赤ぷよ: 左から0列目、0行目
			srcRect = spriteSheet.getSprite(0 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;

		case PuyoColor::BLUE:
			// 青ぷよ: 左から1列目、0行目
			srcRect = spriteSheet.getSprite(1 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;

		case PuyoColor::GREEN:
			// 緑ぷよ: 左から2列目、0行目
			srcRect = spriteSheet.getSprite(2 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;

		case PuyoColor::YELLOW:
			// 黄ぷよ: 左から3列目、0行目
			srcRect = spriteSheet.getSprite(3 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;

		case PuyoColor::PURPLE:
			// 紫ぷよ: 左から4列目、0行目
			srcRect = spriteSheet.getSprite(4 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;

		case PuyoColor::EMPTY:
			// 空白: 左から7列目、0行目
			srcRect = spriteSheet.getSprite(5 * PUYO_SIZE, 1 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
			break;
	}

	return srcRect;
}

SDL_Rect	Board::getDestRect(int x, int y) {
	SDL_Rect	destRect;

	destRect.x = x * PUYO_SIZE + BLOCK_SIZE; // X座標（列番号 × ぷよのサイズ）
	destRect.y = y * PUYO_SIZE; // Y座標（行番号 × ぷよのサイズ）
	destRect.w = PUYO_SIZE; // ぷよの幅
	destRect.h = PUYO_SIZE; // ぷよの高さ

	return destRect;
}

void	Board::draw(SDL_Renderer* renderer, SpriteSheet& spriteSheet) {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			Puyo&	puyo = grid_[x][y];
			PuyoColor	color = puyo.getColor();
			SDL_Rect	srcRect = getSrcRect(color, spriteSheet);
			SDL_Rect	destRect = getDestRect(x, y);
			// ぷよを描画
			SDL_RenderCopy(renderer, spriteSheet.getTexture(), &srcRect, &destRect);
		}
	}
}

void	Board::drawBlock(SDL_Renderer* renderer, SpriteSheet& spriteSheet) {
	for (int y = 0; y < HEIGHT; ++y) {
		SDL_Rect	srcRect = spriteSheet.getSprite(5 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
		SDL_Rect	destRect;
		destRect.x = 0;
		destRect.y = y * PUYO_SIZE;
		destRect.w = PUYO_SIZE;
		destRect.h = PUYO_SIZE;
		SDL_RenderCopy(renderer, spriteSheet.getTexture(), &srcRect, &destRect);
	}
	for (int y = 0; y < HEIGHT; ++y) {
		SDL_Rect	srcRect = spriteSheet.getSprite(5 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
		SDL_Rect	destRect;
		destRect.x = WIDTH * PUYO_SIZE + BLOCK_SIZE;
		destRect.y = y * PUYO_SIZE;
		destRect.w = PUYO_SIZE;
		destRect.h = PUYO_SIZE;
		SDL_RenderCopy(renderer, spriteSheet.getTexture(), &srcRect, &destRect);
	}
	for (int x = 0; x < WIDTH + 2; ++x) {
		SDL_Rect	srcRect = spriteSheet.getSprite(5 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE);
		SDL_Rect	destRect;
		destRect.x = x * PUYO_SIZE;
		destRect.y = HEIGHT * PUYO_SIZE;
		destRect.w = PUYO_SIZE;
		destRect.h = PUYO_SIZE;
		SDL_RenderCopy(renderer, spriteSheet.getTexture(), &srcRect, &destRect);
	}
}

PuyoColor	Board::getRandomColor() {
	static std::random_device	rd; // ランダムデバイス
	static std::mt19937	gen(rd()); // メルセンヌ・ツイスタ生成器
	static std::uniform_int_distribution<>	dist(0, 4); // 0から3の範囲でランダムな整数

	// インデックスに基づいて色を返す
	return static_cast<PuyoColor>(dist(gen));
}

bool Board::canMoveDown(const PuyoPair& pair) const {
	// ペアのぷよを取得
	const Puyo& p1 = pair.getPrimaryPuyo();
	const Puyo& p2 = pair.getSecondaryPuyo();

	int x1 = p1.getX();
	int y1 = p1.getY();
	int x2 = p2.getX();
	int y2 = p2.getY();

	// 2つのぷよそれぞれの下が空いているか
	// あるいは盤面外に行ってしまわないかを確認
	if (y1 + 1 >= HEIGHT || grid_[x1][y1 + 1].getColor() != PuyoColor::EMPTY) {
		return false;
	}
	if (y2 + 1 >= HEIGHT || grid_[x2][y2 + 1].getColor() != PuyoColor::EMPTY) {
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

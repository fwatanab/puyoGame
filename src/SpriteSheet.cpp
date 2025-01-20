#include "SpriteSheet.hpp"

// 静的メンバの初期化
bool	SpriteSheet::isInitialized_ = false;

SpriteSheet::SpriteSheet() : texture_(nullptr) {
	// SDL_Image の初期化
	if (!isInitialized_) {
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			std::cerr << "SDL_Image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
			throw std::runtime_error("Failed to initialize SDL_Image");
		}
		isInitialized_ = true;
	}
}

SpriteSheet::~SpriteSheet() {
	if (texture_) {
		SDL_DestroyTexture(texture_);
	}
}

bool	SpriteSheet::load(const std::string& path, SDL_Renderer* renderer) {
	// .PNGをロード
	SDL_Surface*	surface = IMG_Load(path.c_str());
	if (!surface) {
		std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
		return false;
	}

	texture_ = SDL_CreateTextureFromSurface(renderer, surface); SDL_FreeSurface(surface);

	if (!texture_) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
		return false;
	}

	initializeSpriteMap();
	return true;
}

SDL_Texture*	SpriteSheet::getTexture() const {
	return texture_;
}

SDL_Rect	SpriteSheet::getSprite(PuyoColor color) const {
	auto it = spriteMap_.find(color);
	if (it != spriteMap_.end()) {
		return it->second;
	}

	// 色が見つからない場合、空のスプライト領域を返す
	return {0, 0, 0, 0};
}

void	SpriteSheet::initializeSpriteMap() {
	const int PUYO_SIZE = 32;

	// 各色のスプライト領域を設定
	spriteMap_[PuyoColor::RED] = {0 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::BLUE] = {1 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::GREEN] = {2 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::YELLOW] = {3 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::PURPLE] = {4 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::WALL] = {5 * PUYO_SIZE, 0 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
	spriteMap_[PuyoColor::EMPTY] = {5 * PUYO_SIZE, 1 * PUYO_SIZE, PUYO_SIZE, PUYO_SIZE};
}


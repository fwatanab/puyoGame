#include <SpriteSheet.hpp>

SpriteSheet::SpriteSheet() {}

SpriteSheet::~SpriteSheet() {
	clear();
}

bool	SpriteSheet::load(const std::string& filePath, SDL_Renderer* renderer) {
	spriteSheet_ = IMG_LoadTexture(renderer, filePath.c_str());
	if (!spriteSheet_) {
		std::cerr << "Failed to load sprite sheet! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	return true;
}

SDL_Rect	SpriteSheet::getSprite(int x, int y, int width, int height) {
	SDL_Rect	spriteRect;

	spriteRect.x = x;
	spriteRect.y = y;
	spriteRect.w = width;
	spriteRect.h = height;

	return spriteRect;
}

void	SpriteSheet::clear() {
	// テクスチャを解放
	if (spriteSheet_) {
		SDL_DestroyTexture(spriteSheet_);
		spriteSheet_ = nullptr;
	}
}

SDL_Texture*	SpriteSheet::getTexture() const {
	return spriteSheet_;
}

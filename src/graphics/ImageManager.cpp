#include "ImageManager.hpp"

ImageManager::ImageManager() {}

ImageManager::~ImageManager() {
	clear();
}

void	ImageManager::initTextures(SDL_Renderer* renderer) {
	// Config ファイルから画像をロード
	loadTexture(renderer, PuyoColor::RED, PUYO_RED_IMAGE);
	loadTexture(renderer, PuyoColor::BLUE, PUYO_BLUE_IMAGE);
	loadTexture(renderer, PuyoColor::GREEN, PUYO_GREEN_IMAGE);
	loadTexture(renderer, PuyoColor::YELLOW, PUYO_YELLOW_IMAGE);
	loadTexture(renderer, PuyoColor::PURPLE, PUYO_PURPLE_IMAGE);
	loadTexture(renderer, PuyoColor::WALL, PUYO_WALL_IMAGE);
}


void	ImageManager::loadTexture(SDL_Renderer* renderer, PuyoColor color, const std::string& filePath) {
	if (textures_.find(color) != textures_.end()) {
		throw std::runtime_error("Texture for this color already exists.");
	}

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		throw std::runtime_error("Failed to load image: " + filePath);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		throw std::runtime_error("Failed to create texture for: " + filePath);
	}

	textures_[color] = texture;
}

SDL_Texture* ImageManager::getTexture(PuyoColor color) const {
    auto it = textures_.find(color);
    if (it == textures_.end()) {
//        throw std::runtime_error("Texture for color not found.");
		return nullptr;
    }
    return it->second;
}

void	ImageManager::unloadTexture(PuyoColor key) {
	std::map<PuyoColor, SDL_Texture*>::iterator	it;
	if (it = textures_.find(key); it != textures_.end()) {
		SDL_DestroyTexture(it->second);
		textures_.erase(it);
	}
}

void	ImageManager::clear() {
	std::map<PuyoColor, SDL_Texture*>::iterator	it;
	for (it = textures_.begin(); it != textures_.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}
	textures_.clear();
}

#include "ImageManager.hpp"

ImageManager::ImageManager() {}

ImageManager::~ImageManager() {
	clearGameTextures();
	clearMenuTextures();
}

void	ImageManager::initTextures(SDL_Renderer* renderer) {
	// ぷよ関連のテクスチャをロード
	loadGameTexture(renderer, GameTexture::BACKGROUND, GAME_BACKGROUND_IMAGE);
	loadGameTexture(renderer, GameTexture::RED_PUYO, PUYO_RED_IMAGE);
	loadGameTexture(renderer, GameTexture::BLUE_PUYO, PUYO_BLUE_IMAGE);
	loadGameTexture(renderer, GameTexture::GREEN_PUYO, PUYO_GREEN_IMAGE);
	loadGameTexture(renderer, GameTexture::YELLOW_PUYO, PUYO_YELLOW_IMAGE);
	loadGameTexture(renderer, GameTexture::PURPLE_PUYO, PUYO_PURPLE_IMAGE);
//	loadGameTexture(renderer, GameTexture::GARBAGE_PUYO, PUYO_GARBAGE_IMAGE);
	loadGameTexture(renderer, GameTexture::WALL, GAME_WALL_IMAGE);
	loadGameTexture(renderer, GameTexture::HUD_SCORE_PANEL, HUD_SCORE_PANEL_IMAGE);
	loadGameTexture(renderer, GameTexture::HUD_NEXT_PANEL, HUD_NEXT_PANEL_IMAGE);

	// メニュー関連テクスチャをロード
	loadMenuTexture(renderer, MenuTexture::BACKGROUND, MENU_BACKGROUND);
	loadMenuTexture(renderer, MenuTexture::FRAME, MENU_FRAME_IMAGE);
}


void	ImageManager::loadGameTexture(SDL_Renderer* renderer, GameTexture type, const std::string& filePath) {
	if (gameTextures_.find(type) != gameTextures_.end()) {
		throw std::runtime_error("Game texture already exists: " + filePath);
	}

	SDL_Surface*	surface = IMG_Load(filePath.c_str());
	if (!surface) {
		throw std::runtime_error("Failed to load image: " + filePath);
	}

	SDL_Texture*	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		throw std::runtime_error("Failed to create texture for: " + filePath);
	}

	gameTextures_[type] = texture;
}

SDL_Texture*	ImageManager::getGameTexture(GameTexture type) const {
	std::map<GameTexture, SDL_Texture*>::const_iterator	it = gameTextures_.find(type);
	if (it == gameTextures_.end()) {
		return nullptr;
	}
	return it->second;
}

void	ImageManager::clearGameTextures() {
	std::map<GameTexture, SDL_Texture*>::iterator	it;
	for (it = gameTextures_.begin(); it != gameTextures_.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}
	gameTextures_.clear();
}

void	ImageManager::loadMenuTexture(SDL_Renderer* renderer, MenuTexture type, const std::string& filePath) {
	if (menuTextures_.find(type) != menuTextures_.end()) {
		throw std::runtime_error("Menu texture already exists: " + filePath);
	}
	SDL_Surface*	surface = IMG_Load(filePath.c_str());
	if (!surface) {
		throw std::runtime_error("Failed to load menu image: " + filePath);
	}

	SDL_Texture*	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		throw std::runtime_error("Failed to create menu texture: " + filePath);
	}

	menuTextures_[type] = texture;
}

SDL_Texture*	ImageManager::getMenuTexture(MenuTexture type) const {
	std::map<MenuTexture, SDL_Texture*>::const_iterator	it = menuTextures_.find(type);
	if (it == menuTextures_.end()) {
		return nullptr;
	}
	return it->second;
}

void	ImageManager::clearMenuTextures() {
	std::map<MenuTexture, SDL_Texture*>::iterator	it;
	for (it = menuTextures_.begin(); it != menuTextures_.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}
	menuTextures_.clear();
}

SDL_Texture*	ImageManager::getTextureForPuyo(PuyoColor color) const {
	switch (color) {
		case PuyoColor::RED:
			return getGameTexture(GameTexture::RED_PUYO);
		case PuyoColor::BLUE:
			return getGameTexture(GameTexture::BLUE_PUYO);
		case PuyoColor::GREEN:
			return getGameTexture(GameTexture::GREEN_PUYO);
		case PuyoColor::YELLOW:
			return getGameTexture(GameTexture::YELLOW_PUYO);
		case PuyoColor::PURPLE:
			return getGameTexture(GameTexture::PURPLE_PUYO);
//		case PuyoColor::GARBAGE:
//			return getGameTexture(GameTexture::GARBAGE_PUYO);
		case PuyoColor::EMPTY:
			return nullptr;
		default:
			throw std::runtime_error("Invalid PuyoColor.");
	}
}

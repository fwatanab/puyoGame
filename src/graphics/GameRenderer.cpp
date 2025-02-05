#include "GameRenderer.hpp"
#include <iostream>

GameRenderer::GameRenderer(const std::string& title) : Renderer(title) {}

void	GameRenderer::renderBoard(const Board& board, const ImageManager& imageManager) {
	// 壁の描画
	for (int y = 0; y < BOARD_HEIGHT + 1; ++y) {
		for (int x = 0; x < BOARD_WIDTH + 2; ++x) {
			SDL_Rect	destRect = getDestRect(x, y);
			SDL_Texture*	texture;
			if (x == 0 || x == BOARD_WIDTH + 1 || y == BOARD_HEIGHT) {
				// 壁の描画
				texture = imageManager.getGameTexture(GameTexture::WALL);
			} else {
				// ボード内のぷよの描画
				const Puyo&	puyo = board.getGrid(x - 1, y);
				texture = imageManager.getTextureForPuyo(puyo.getColor());
			}
			
			// テクスチャが nullptr でない場合にのみ描画を行う
			if (texture) {
				SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
			} else {
				std::cerr << "Warning: Texture not found for rendering at (" << x << ", " << y << ")." << std::endl;
			}
		}
	}
}


void	GameRenderer::renderPuyoPair(const PuyoPair& puyoPair, const ImageManager& imageManager) {
	const Puyo&	primary = puyoPair.getPrimaryPuyo();
	const Puyo&	secondary = puyoPair.getSecondaryPuyo();

	int	primaryX = primary.getX() + 1; // 左の壁を避けるため +1
	int	primaryY = primary.getY();
	int	secondaryX = secondary.getX() + 1; // 左の壁を避けるため +1
	int	secondaryY = secondary.getY();

	SDL_Texture*	texturePrimary = imageManager.getTextureForPuyo(primary.getColor());
	SDL_Rect	destRectPrimary = getDestRect(primaryX, primaryY);
	SDL_RenderCopy(renderer_, texturePrimary, nullptr, &destRectPrimary);

	SDL_Texture*	textureSecondary = imageManager.getTextureForPuyo(secondary.getColor());
	SDL_Rect	destRectSecondary = getDestRect(secondaryX, secondaryY);
	SDL_RenderCopy(renderer_, textureSecondary, nullptr, &destRectSecondary);
}

SDL_Rect	GameRenderer::getDestRect(int x, int y) const {
	SDL_Rect rect;
	rect.x = x * PUYO_SIZE;
	rect.y = y * PUYO_SIZE;
	rect.w = PUYO_SIZE;
	rect.h = PUYO_SIZE;
	return rect;
}

void	GameRenderer::renderNextPuyoPair(const PuyoPair& nextPair, const PuyoPair& nextNextPair, const ImageManager& imageManager) {
	// nextPair の primary と secondary を縦に並べて描画
	SDL_Rect	nextPrimaryRect = getDestRect(BOARD_WIDTH + 2, 2);  // primary は上
	SDL_Rect	nextSecondaryRect = getDestRect(BOARD_WIDTH + 2, 3);  // secondary は下
	
	SDL_Texture*	nextPrimaryTexture = imageManager.getTextureForPuyo(nextPair.getPrimaryPuyo().getColor());
	SDL_Texture*	nextSecondaryTexture = imageManager.getTextureForPuyo(nextPair.getSecondaryPuyo().getColor());
	
	SDL_RenderCopy(renderer_, nextPrimaryTexture, nullptr, &nextPrimaryRect);
	SDL_RenderCopy(renderer_, nextSecondaryTexture, nullptr, &nextSecondaryRect);
	
	// nextNextPair の primary と secondary を縦に並べて描画
	SDL_Rect	nextNextPrimaryRect = getDestRect(BOARD_WIDTH + 2, 5);
	SDL_Rect	nextNextSecondaryRect = getDestRect(BOARD_WIDTH + 2, 6);
	
	SDL_Texture*	nextNextPrimaryTexture = imageManager.getTextureForPuyo(nextNextPair.getPrimaryPuyo().getColor());
	SDL_Texture*	nextNextSecondaryTexture = imageManager.getTextureForPuyo(nextNextPair.getSecondaryPuyo().getColor());
	
	SDL_RenderCopy(renderer_, nextNextPrimaryTexture, nullptr, &nextNextPrimaryRect);
	SDL_RenderCopy(renderer_, nextNextSecondaryTexture, nullptr, &nextNextSecondaryRect);
}

void	GameRenderer::render() {}

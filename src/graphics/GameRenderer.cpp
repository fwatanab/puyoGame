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
				texture = imageManager.getTexture(PuyoColor::WALL);
			} else {
				// ボード内のぷよの描画
				const Puyo&	puyo = board.getGrid(x - 1, y);
				texture = imageManager.getTexture(puyo.getColor());
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

	SDL_Texture*	texturePrimary = imageManager.getTexture(primary.getColor());
	SDL_Rect	destRectPrimary = getDestRect(primaryX, primaryY);
	SDL_RenderCopy(renderer_, texturePrimary, nullptr, &destRectPrimary);

	SDL_Texture*	textureSecondary = imageManager.getTexture(secondary.getColor());
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

void	GameRenderer::render() {}

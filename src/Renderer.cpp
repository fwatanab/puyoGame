#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(const std::string& title) {
	// ソフトウェアレンダリングを指定
	if (SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software") == SDL_FALSE) {
		std::cerr << "Warning: Unable to set SDL_HINT_RENDER_DRIVER to software!" << std::endl;
	}

	// ウィンドウ作成
	if (FULLSCREEN) {
		window_ = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_FULLSCREEN // フルスクリーンモードに変更
		);
	} else {
		window_ = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);
	}

	if (!window_) {
		throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}

	// レンダラ作成
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer_) {
		SDL_DestroyWindow(window_);
		throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

SDL_Rect	Renderer::getDestRect(int x, int y) const {
	SDL_Rect rect;
	rect.x = x * PUYO_SIZE;
	rect.y = y * PUYO_SIZE;
	rect.w = PUYO_SIZE;
	rect.h = PUYO_SIZE;
	return rect;
}


void	Renderer::renderBoard(const Board& board, const ImageManager& imageManager) {
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


void Renderer::renderPuyoPair(const PuyoPair& puyoPair, const ImageManager& imageManager) {
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

SDL_Renderer*	Renderer::getSDLRenderer() const {
	return renderer_;
}

void	Renderer::clear() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer_);
}

void	Renderer::present() {
	SDL_RenderPresent(renderer_);
}


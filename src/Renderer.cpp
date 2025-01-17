#include "Renderer.hpp"

Renderer::Renderer(int width, int height, const std::string& title) {
	// ソフトウェアレンダリングを指定
	if (SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software") == SDL_FALSE) {
		std::cerr << "Warning: Unable to set SDL_HINT_RENDER_DRIVER to software!" << std::endl;
	}

	// ウィンドウ作成
	window_ = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN
	);
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
	rect.x = x * Board::PUYO_SIZE;
	rect.y = y * Board::PUYO_SIZE;
	rect.w = Board::PUYO_SIZE;
	rect.h = Board::PUYO_SIZE;
	return rect;
}

void	Renderer::renderBoard(const Board& board, const SpriteSheet& spriteSheet) {
	for (int y = 0; y < Board::HEIGHT; ++y) {
		for (int x = 0; x < Board::WIDTH; ++x) {
			const Puyo&	puyo = board.getGrid(x, y);
			if (puyo.getColor() != PuyoColor::EMPTY) {
				SDL_Rect srcRect = spriteSheet.getSprite(puyo.getColor());
				SDL_Rect destRect = getDestRect(x, y);
				SDL_RenderCopy(renderer_, spriteSheet.getTexture(), &srcRect, &destRect);
			}
		}
	}
}

void	Renderer::renderPuyoPair(const PuyoPair& puyoPair, const SpriteSheet& spriteSheet) {
	const Puyo&	primary = puyoPair.getPrimaryPuyo();
	const Puyo&	secondary = puyoPair.getSecondaryPuyo();

	SDL_Rect	srcRectPrimary = spriteSheet.getSprite(primary.getColor());
	SDL_Rect	destRectPrimary = getDestRect(primary.getX(), primary.getY());
	SDL_RenderCopy(renderer_, spriteSheet.getTexture(), &srcRectPrimary, &destRectPrimary);

	SDL_Rect	srcRectSecondary = spriteSheet.getSprite(secondary.getColor());
	SDL_Rect	destRectSecondary = getDestRect(secondary.getX(), secondary.getY());
	SDL_RenderCopy(renderer_, spriteSheet.getTexture(), &srcRectSecondary, &destRectSecondary);
}

void	Renderer::renderBlocks(const SpriteSheet& spriteSheet) {
	for (int x = 0; x < Board::WIDTH + 2; ++x) {
		for (int y = 0; y < Board::HEIGHT + 1; ++y) {
			SDL_Rect	srcRect = spriteSheet.getSprite(PuyoColor::EMPTY);
			SDL_Rect	destRect = getDestRect(x, y);
			SDL_RenderCopy(renderer_, spriteSheet.getTexture(), &srcRect, &destRect);
		}
	}
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


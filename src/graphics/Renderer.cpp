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


#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(const std::string& title) {
	// ウィンドウ作成
	Uint32	windowFlags = SDL_WINDOW_SHOWN;
	if (FULLSCREEN) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}
	window_ = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		windowFlags
	);

	if (!window_) {
		throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}

	// レンダラ作成
	Uint32	rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer_ = SDL_CreateRenderer(window_, -1, rendererFlags);
	if (!renderer_) {
		std::cerr << "Warning: Accelerated renderer unavailable, falling back to software. SDL_Error: " << SDL_GetError() << std::endl;
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
	}
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

#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include "Renderer.hpp"
#include "Board.hpp"
#include "ImageManager.hpp"
#include "PuyoPair.hpp"

class	GameRenderer : public Renderer {
	public:
		GameRenderer(const std::string& title);

		void	renderBoard(const Board& board, const ImageManager& imageManager);
		void	renderPuyoPair(const PuyoPair& puyoPair, const ImageManager& imageManager);

		SDL_Rect	getDestRect(int x, int y) const;

		void	renderNextPuyoPair(const PuyoPair& nextPair, const PuyoPair& nextNextPair, const ImageManager& imageManager);

		void	render() override;

};

#endif

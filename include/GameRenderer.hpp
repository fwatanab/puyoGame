#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include "Renderer.hpp"
#include "Board.hpp"
#include "ImageManager.hpp"
#include "PuyoPair.hpp"
#include "TextRenderer.hpp"
#include <string>

class	GameRenderer : public Renderer {
	public:
		GameRenderer(const std::string& title);

		void	renderBoard(const Board& board, const ImageManager& imageManager);
		void	renderPuyoPair(const PuyoPair& puyoPair, const ImageManager& imageManager);
		void	renderSidePanel(const PuyoPair& nextPair, const PuyoPair& nextNextPair, int score, int lastChain, int bestChain, const ImageManager& imageManager);

		SDL_Rect	getDestRect(int x, int y) const;
	private:
		void	renderBackground(const ImageManager& imageManager);
		void	renderBoardBackdrop() const;
		SDL_Rect	getScorePanelRect(SDL_Texture* texture) const;
		SDL_Rect	getNextPanelRect(const SDL_Rect& scorePanel, SDL_Texture* texture) const;
		void	renderNextPreview(const PuyoPair& nextPair, const PuyoPair& nextNextPair, const ImageManager& imageManager, const SDL_Rect& panelRect);
		static	std::string	formatNumber(int value);
		SDL_Point	getBoardOrigin() const;
		int	getBoardWidthPx() const;
		int	getBoardHeightPx() const;
		int	getSidePanelX(int panelWidth) const;

};

#endif

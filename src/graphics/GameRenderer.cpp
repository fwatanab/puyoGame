#include "GameRenderer.hpp"
#include <algorithm>
#include <iostream>

namespace {
const int kPanelSpacing = 32;
const int kSidePanelPadding = 60;
const SDL_Color kLabelColor = {255, 225, 190, 255};
const SDL_Color kValueColor = {255, 255, 255, 255};
const SDL_Color kHighlightColor = {255, 214, 94, 255};
}

// SDL ウィンドウ／レンダラーを初期化してゲーム描画器を構築する。
GameRenderer::GameRenderer(const std::string& title) : Renderer(title) {}

// 背景や壁を含めて盤面全体を描画する。
void	GameRenderer::renderBoard(const Board& board, const ImageManager& imageManager) {
	renderBackground(imageManager);
	renderBoardBackdrop();

	for (int y = 0; y < BOARD_HEIGHT + 1; ++y) {
		for (int x = 0; x < BOARD_WIDTH + 2; ++x) {
			SDL_Rect	destRect = getDestRect(x, y);
			SDL_Texture*	texture = nullptr;
			if (x == 0 || x == BOARD_WIDTH + 1 || y == BOARD_HEIGHT) {
				texture = imageManager.getGameTexture(GameTexture::WALL);
			} else {
				const Puyo&	puyo = board.getGrid(x - 1, y);
				texture = imageManager.getTextureForPuyo(puyo.getColor());
			}

			if (texture) {
				SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
			}
		}
	}
}

// 操作中のぷよペアを描画する。
void	GameRenderer::renderPuyoPair(const PuyoPair& puyoPair, const ImageManager& imageManager) {
	const Puyo&	primary = puyoPair.getPrimaryPuyo();
	const Puyo&	secondary = puyoPair.getSecondaryPuyo();

	int	primaryX = primary.getX() + 1;
	int	primaryY = primary.getY();
	int	secondaryX = secondary.getX() + 1;
	int	secondaryY = secondary.getY();

	SDL_Texture*	texturePrimary = imageManager.getTextureForPuyo(primary.getColor());
	SDL_Rect	destRectPrimary = getDestRect(primaryX, primaryY);
	if (texturePrimary) {
		SDL_RenderCopy(renderer_, texturePrimary, nullptr, &destRectPrimary);
	}

	SDL_Texture*	textureSecondary = imageManager.getTextureForPuyo(secondary.getColor());
	SDL_Rect	destRectSecondary = getDestRect(secondaryX, secondaryY);
	if (textureSecondary) {
		SDL_RenderCopy(renderer_, textureSecondary, nullptr, &destRectSecondary);
	}
}

// スコアや連鎖、NEXT 表示など HUD 一式を描画する。
void	GameRenderer::renderSidePanel(const PuyoPair& nextPair, const PuyoPair& nextNextPair, int score, int lastChain, int bestChain, const ImageManager& imageManager) {
	SDL_Texture*	hudTexture = imageManager.getGameTexture(GameTexture::HUD_SCORE_PANEL);
	SDL_Rect	scoreRect = getScorePanelRect(hudTexture);
	if (hudTexture) {
		SDL_RenderCopy(renderer_, hudTexture, nullptr, &scoreRect);
	} else {
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer_, 20, 20, 40, 230);
		SDL_RenderFillRect(renderer_, &scoreRect);
	}

	TextRenderer::renderText(renderer_, "SCORE", scoreRect.x + 24, scoreRect.y + 24, 4, kLabelColor);
	TextRenderer::renderText(renderer_, formatNumber(score), scoreRect.x + 24, scoreRect.y + 70, 6, kValueColor);

	TextRenderer::renderText(renderer_, "CHAIN", scoreRect.x + 24, scoreRect.y + 140, 4, kLabelColor);
	TextRenderer::renderText(renderer_, formatNumber(std::max(0, lastChain)), scoreRect.x + 24, scoreRect.y + 186, 5, kHighlightColor);

	TextRenderer::renderText(renderer_, "BEST", scoreRect.x + 190, scoreRect.y + 140, 4, kLabelColor);
	TextRenderer::renderText(renderer_, formatNumber(std::max(0, bestChain)), scoreRect.x + 190, scoreRect.y + 186, 5, kValueColor);

	SDL_Texture*	nextTexture = imageManager.getGameTexture(GameTexture::HUD_NEXT_PANEL);
	SDL_Rect	nextRect = getNextPanelRect(scoreRect, nextTexture);
	if (nextTexture) {
		SDL_RenderCopy(renderer_, nextTexture, nullptr, &nextRect);
	} else {
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer_, 25, 45, 70, 220);
		SDL_RenderFillRect(renderer_, &nextRect);
	}

	TextRenderer::renderText(renderer_, "NEXT", nextRect.x + 20, nextRect.y + 18, 4, kLabelColor);
	renderNextPreview(nextPair, nextNextPair, imageManager, nextRect);
}

// 盤面座標を画面上のピクセル矩形に変換する。
SDL_Rect	GameRenderer::getDestRect(int x, int y) const {
	SDL_Rect rect;
	SDL_Point origin = getBoardOrigin();
	rect.x = origin.x + x * PUYO_SIZE;
	rect.y = origin.y + y * PUYO_SIZE;
	rect.w = PUYO_SIZE;
	rect.h = PUYO_SIZE;
	return rect;
}

// 背景テクスチャがあれば画面全体に描画する。
void	GameRenderer::renderBackground(const ImageManager& imageManager) {
	SDL_Texture*	background = imageManager.getGameTexture(GameTexture::BACKGROUND);
	if (!background) {
		return;
	}
	SDL_Rect	destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer_, background, nullptr, &destRect);
}

// 盤面背後に半透明の矩形を置いて視認性を高める。
void	GameRenderer::renderBoardBackdrop() const {
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer_, 10, 15, 45, 160);
	SDL_Point origin = getBoardOrigin();
	SDL_Rect	boardRect = {origin.x, origin.y, getBoardWidthPx(), getBoardHeightPx()};
	SDL_RenderFillRect(renderer_, &boardRect);
}

// パネルのサイズと余白を考慮してスコア領域を算出する。
SDL_Rect	GameRenderer::getScorePanelRect(SDL_Texture* texture) const {
	SDL_Rect rect;
	if (texture && SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == 0) {
		// size derived from texture
	} else {
		rect.w = 360;
		rect.h = 240;
	}
	SDL_Point origin = getBoardOrigin();
	rect.x = getSidePanelX(rect.w);
	rect.y = origin.y;
	if (rect.y < MARGIN_TOP) {
		rect.y = MARGIN_TOP;
	}
	if (rect.y + rect.h > SCREEN_HEIGHT - MARGIN_TOP) {
		rect.y = SCREEN_HEIGHT - rect.h - MARGIN_TOP;
	}
	return rect;
}

// スコアパネルの下に配置する NEXT パネル領域を算出する。
SDL_Rect	GameRenderer::getNextPanelRect(const SDL_Rect& scorePanel, SDL_Texture* texture) const {
	SDL_Rect rect;
	if (texture && SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == 0) {
		// keep texture size
	} else {
		rect.w = 240;
		rect.h = 280;
	}
	rect.y = scorePanel.y + scorePanel.h + kPanelSpacing;
	rect.x = scorePanel.x + (scorePanel.w - rect.w) / 2;
	if (rect.y + rect.h > SCREEN_HEIGHT - MARGIN_TOP) {
		rect.y = SCREEN_HEIGHT - rect.h - MARGIN_TOP;
	}
	if (rect.y < scorePanel.y + scorePanel.h + kPanelSpacing) {
		rect.y = scorePanel.y + scorePanel.h + kPanelSpacing;
	}
	return rect;
}

// NEXT パネル内に次のぷよペアを描画する。
void	GameRenderer::renderNextPreview(const PuyoPair& nextPair, const PuyoPair& nextNextPair, const ImageManager& imageManager, const SDL_Rect& panelRect) {
	const int	previewSize = static_cast<int>(PUYO_SIZE * 0.9f);
	const int	centerX = panelRect.x + panelRect.w / 2;
	const int	startY = panelRect.y + 90;
	const int	spacing = previewSize + 10;

	auto drawSingle = [&](const Puyo& puyo, int yPos) {
		SDL_Texture*	texture = imageManager.getTextureForPuyo(puyo.getColor());
		if (!texture) {
			return;
		}
		SDL_Rect	dest = {centerX - previewSize / 2, yPos - previewSize / 2, previewSize, previewSize};
		SDL_RenderCopy(renderer_, texture, nullptr, &dest);
	};

	auto drawPair = [&](const PuyoPair& pair, int baseY) {
		drawSingle(pair.getPrimaryPuyo(), baseY);
		drawSingle(pair.getSecondaryPuyo(), baseY + spacing);
	};

	drawPair(nextPair, startY);
	drawPair(nextNextPair, startY + (spacing * 2) + 40);
}

// 数値をカンマ付きの文字列へ整形する。
std::string	GameRenderer::formatNumber(int value) {
	if (value <= 0) {
		return "0";
	}
	std::string	digits = std::to_string(value);
	std::string	formatted;
	formatted.reserve(digits.size() + digits.size() / 3);
	int	counter = 0;
	for (std::string::reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it) {
		if (counter == 3) {
			formatted.push_back(',');
			counter = 0;
		}
		formatted.push_back(*it);
		counter++;
	}
	std::reverse(formatted.begin(), formatted.end());
	return formatted;
}

// フルスクリーンかどうかに応じて盤面左上の画面座標を求める。
SDL_Point	GameRenderer::getBoardOrigin() const {
	SDL_Point origin;
	int	boardWidth = getBoardWidthPx();
	int	boardHeight = getBoardHeightPx();
	if (FULLSCREEN) {
		origin.x = std::max(MARGIN_SIDE, (SCREEN_WIDTH - boardWidth) / 2);
		origin.y = std::max(MARGIN_TOP, (SCREEN_HEIGHT - boardHeight) / 2);
	} else {
		origin.x = MARGIN_SIDE;
		origin.y = MARGIN_TOP;
	}
	return origin;
}

// 壁を含む盤面の幅（ピクセル）を返す。
int	GameRenderer::getBoardWidthPx() const {
	return (BOARD_WIDTH + 2) * PUYO_SIZE;
}

// 床を含む盤面の高さ（ピクセル）を返す。
int	GameRenderer::getBoardHeightPx() const {
	return (BOARD_HEIGHT + 1) * PUYO_SIZE;
}

// 盤面と重ならないようサイドパネルの X 座標を計算する。
int	GameRenderer::getSidePanelX(int panelWidth) const {
	SDL_Point origin = getBoardOrigin();
	int	boardRight = origin.x + getBoardWidthPx();
	int	x = boardRight + kSidePanelPadding;
	int	maxRight = SCREEN_WIDTH - MARGIN_SIDE;
	if (x + panelWidth > maxRight) {
		x = maxRight - panelWidth;
	}
	if (x < boardRight + 20) {
		x = boardRight + 20;
	}
	return x;
}

#include "MenuRenderer.hpp"

#include <algorithm>

namespace {
const int kOptionHeight = 80;
const int kOptionWidth = 420;
const int kOptionSpacing = 24;
}

// メニューウィンドウの描画専用レンダラーを構築する。
MenuRenderer::MenuRenderer(const std::string& title) : Renderer(title) {
	highlightColor_ = {MENU_HIGHLIGHT_COLOR_R, MENU_HIGHLIGHT_COLOR_G, MENU_HIGHLIGHT_COLOR_B, 255};
	textColor_ = {240, 240, 240, 255};
}

// メニュー全体を描画する。
void	MenuRenderer::render(const Menu& menu, const ImageManager& imageManager) {
	clear();

	SDL_Texture*	background = imageManager.getMenuTexture(MenuTexture::BACKGROUND);
	if (background) {
		SDL_Rect	destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_RenderCopy(renderer_, background, nullptr, &destRect);
	} else {
		SDL_SetRenderDrawColor(renderer_, 25, 25, 60, 255);
		SDL_RenderClear(renderer_);
	}

	const std::vector<MenuItem>& items = menu.getItems();
	const int	totalHeight = static_cast<int>(items.size()) * kOptionHeight + static_cast<int>(items.size() - 1) * kOptionSpacing;
	const int	startY = std::max(MARGIN_TOP, (SCREEN_HEIGHT - totalHeight) / 2);
	const int	startX = std::max(MARGIN_SIDE, (SCREEN_WIDTH - kOptionWidth) / 2);

	for (size_t i = 0; i < items.size(); ++i) {
		SDL_Rect	optionRect = {
			startX,
			startY + static_cast<int>(i) * (kOptionHeight + kOptionSpacing),
			kOptionWidth,
			kOptionHeight
		};
		renderOption(items[i], optionRect, static_cast<int>(i) == menu.getSelectedIndex(), imageManager);
	}

	present();
}

// 個々のメニュー項目を描画する。
void	MenuRenderer::renderOption(const MenuItem& item, const SDL_Rect& rect, bool isSelected, const ImageManager& imageManager) {
	SDL_Texture*	frame = imageManager.getMenuTexture(MenuTexture::FRAME);
	if (frame) {
		SDL_RenderCopy(renderer_, frame, nullptr, &rect);
	} else {
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer_, 255, 255, 255, isSelected ? 220 : 120);
		SDL_RenderDrawRect(renderer_, &rect);
	}

	if (isSelected) {
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer_, highlightColor_.r, highlightColor_.g, highlightColor_.b, 60);
		SDL_RenderFillRect(renderer_, &rect);
	}

	SDL_Color	color = isSelected ? highlightColor_ : textColor_;
	const int	textScale = isSelected ? 6 : 5;
	const int	textX = rect.x + 40;
	const int	textY = rect.y + rect.h / 2 - (textScale * 3);
	TextRenderer::renderText(renderer_, item.label, textX, textY, textScale, color);
}

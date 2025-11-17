#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Puyo.hpp"
#include "GeneratedConfig.hpp"

// ゲーム用のテクスチャを表す列挙型
enum class	GameTexture {
	BACKGROUND,
	RED_PUYO,
	BLUE_PUYO,
	GREEN_PUYO,
	YELLOW_PUYO,
	PURPLE_PUYO,
	GARBAGE_PUYO,
	WALL,
	HUD_SCORE_PANEL,
	HUD_NEXT_PANEL
};

// メニュー用のテクスチャを表す列挙型
enum class	MenuTexture {
	BACKGROUND,
	FRAME,
	SOLO_MODE,
	DUO_MODE,
	EXIT
};

class	ImageManager {
	public:
		ImageManager();
		~ImageManager();

		// すべてのテクスチャを初期化
		void	initTextures(SDL_Renderer* renderer);
		
		// ゲーム関連のテクスチャ管理
		void	loadGameTexture(SDL_Renderer* renderer, GameTexture type, const std::string& filePath);
		SDL_Texture*	getGameTexture(GameTexture type) const;
		void	clearGameTextures();
		
		// メニュー関連のテクスチャ管理
		void	loadMenuTexture(SDL_Renderer* renderer, MenuTexture type, const std::string& filePath);
		SDL_Texture*	getMenuTexture(MenuTexture type) const;
		void	clearMenuTextures();

		// 変換メソッド
		SDL_Texture*	getTextureForPuyo(PuyoColor color) const;
		SDL_Texture*	getTextureForMenu(MenuOption option) const;

	private:
		std::map<GameTexture, SDL_Texture*>	gameTextures_;
		std::map<MenuTexture, SDL_Texture*>	menuTextures_;
};

#endif

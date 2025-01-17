#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Puyo.hpp" // PuyoColor を利用するため

class	SpriteSheet {
	public:
		SpriteSheet();
		~SpriteSheet();

		// 画像ファイルをロード
		bool	load(const std::string& path, SDL_Renderer* renderer);

		// テクスチャを取得
		SDL_Texture*	getTexture() const;

		// 指定された PuyoColor のスプライト領域を取得
		SDL_Rect	getSprite(PuyoColor color) const;

	private:
		SDL_Texture*	texture_; // スプライトシートのテクスチャ
		static bool	isInitialized_;
		std::unordered_map<PuyoColor, SDL_Rect>	spriteMap_; // 色とスプライト領域の対応表

		// スプライトマップを初期化
		void	initializeSpriteMap();
};

#endif

#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Puyo.hpp"
#include "GeneratedConfig.hpp"

class	ImageManager {
	public:
		ImageManager();
		~ImageManager();

		// 初期化
		void	initTextures(SDL_Renderer* renderer);

		// テクスチャの読み込み
		void	loadTexture(SDL_Renderer* renderer, PuyoColor color, const std::string& filePath);

		// テクスチャを取得する
		SDL_Texture*	getTexture(PuyoColor key) const;

		// テクスチャの削除
		void	unloadTexture(PuyoColor key);

		void	clear();

	private:
		std::map<PuyoColor, SDL_Texture*>	textures_; // テクスチャのマップ
};

#endif

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class	SpriteSheet {
	public:
		SpriteSheet();
		~SpriteSheet();

		// スプライトシートを読み込む
		bool	load(const std::string& filePath, SDL_Renderer* renderer);

		// スプライトシートから特定のスプライトを切り出す
		SDL_Rect	getSprite(int x, int y, int width, int height);

		// スプライトシートのメモリ解放
	void	clear();

		// スプライトシートのテクスチャを取得
		SDL_Texture*	getTexture() const;
	private:
		SDL_Texture*	spriteSheet_;
};

#endif

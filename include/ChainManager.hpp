#ifndef CHAIN_MANAGER_HPP
#define CHAIN_MANAGER_HPP

#include "Board.hpp"
#include "PuyoFinder.hpp"
#include "PuyoClearer.hpp"
#include "Renderer.hpp"
#include <thread> // std::this_thread::sleep_for
//#include "ScoreManager.hpp"
#include <vector>

class	ChainManager {
	public:
//		ChainManager(PuyoFinder& finder, PuyoClearer& clearer, ScoreManager& scorer);
		ChainManager(PuyoFinder& finder, PuyoClearer& clearer, Renderer& renderer);

		// 連鎖の進行を管理
		void	processChains(Board& board, SpriteSheet& spriteSheet);

		// 描画の更新
		void	updateRendering(Board& board, SpriteSheet& spriteSheet);

	private:
		PuyoFinder&	finder_;
		PuyoClearer&	clearer_;
//		ScoreManager&	scorer_;
		Renderer&	renderer_;
};

#endif

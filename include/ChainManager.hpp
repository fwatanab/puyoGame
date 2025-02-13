#ifndef CHAIN_MANAGER_HPP
#define CHAIN_MANAGER_HPP

#include "Board.hpp"
#include "PuyoFinder.hpp"
#include "PuyoClearer.hpp"
#include "GameRenderer.hpp"
#include <thread> // std::this_thread::sleep_for
//#include "ScoreManager.hpp"
#include <vector>

class	ChainManager {
	public:
		ChainManager(PuyoFinder& finder, PuyoClearer& clearer, GameRenderer& renderer);

		// 連鎖の進行を管理
		void	processChains(Board& board, ImageManager& imageManager);

		// 描画の更新
		void	updateRendering(Board& board, ImageManager& imageManager);

	private:
		PuyoFinder&	finder_;
		PuyoClearer&	clearer_;
//		ScoreManager&	scorer_;
		GameRenderer&	renderer_;
};

#endif

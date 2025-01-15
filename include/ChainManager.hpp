#ifndef CHAIN_MANAGER_HPP
#define CHAIN_MANAGER_HPP

#include "Board.hpp"
#include "PuyoFinder.hpp"
#include "PuyoClearer.hpp"
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds
//#include "ScoreManager.hpp"

class	ChainManager {
	public:
//		ChainManager(PuyoFinder& finder, PuyoClearer& clearer, ScoreManager& scorer);
		ChainManager(PuyoFinder& finder, PuyoClearer& clearer);

		// 連鎖の進行を管理
		void	processChains(Board& board);

	private:
		PuyoFinder& finder_;
		PuyoClearer& clearer_;
//		ScoreManager& scorer_;
};

#endif

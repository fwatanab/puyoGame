#include "ChainManager.hpp"
#include <vector>

ChainManager::ChainManager(PuyoFinder& finder, PuyoClearer& clearer) : finder_(finder), clearer_(clearer) {}
//, PuyoClearer& clearer, ScoreManager& scorer)
//	: finder_(finder), clearer_(clearer), scorer_(scorer) {}

void	ChainManager::processChains(Board& board) {
	int	chainCount = 0; // 連鎖回数のカウント

	while (true) {
		// 消去対象のグループを探索
		std::vector<std::vector<Puyo>>	groups = finder_.findGroupsToClear(board);
		if (groups.empty()) {
			break; // 消去対象がなくなったら終了
		}

		// グループを消去
		clearer_.clearPuyos(board, groups);

		// 1秒待機
		std::this_thread::sleep_for(std::chrono::seconds(1));

//		// 得点を計算して加算
//		int	score = scorer_.calculateScore(groups.size(), chainCount);
//		scorer_.addScore(score);

		// 重力を適用
		clearer_.applyGravity(board);

		// 再び1秒待機
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// 連鎖回数を増加
		chainCount++;
	}
}

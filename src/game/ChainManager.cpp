#include "ChainManager.hpp"
#include <chrono>

ChainManager::ChainManager(PuyoFinder& finder, PuyoClearer& clearer, GameRenderer& renderer) : finder_(finder), clearer_(clearer), renderer_(renderer) {}

int	ChainManager::processChains(Board& board, ImageManager& imageManager, ScoreManager& scorer) {
	int	chainCount = 0; // 連鎖回数のカウント

	while (true) {
		// 消去対象のグループを探索
		std::vector<std::vector<Puyo>>	groups = finder_.findGroupsToClear(board);
		if (groups.empty()) {
			break; // 消去対象がなくなったら終了
		}

		// 削除前に画面を更新
		updateRendering(board, imageManager);

		// 1秒待機
		std::this_thread::sleep_for(std::chrono::milliseconds(GRAVITY_SPEED));

		// グループを消去
		clearer_.clearPuyos(board, groups);

		// 消去後に画面を更新
		updateRendering(board, imageManager);

		// 1秒待機
		std::this_thread::sleep_for(std::chrono::milliseconds(CHAIN_SPEED));

		int	totalCleared = 0;
		for (std::vector<std::vector<Puyo>>::const_iterator it = groups.begin(); it != groups.end(); ++it) {
			totalCleared += static_cast<int>(it->size());
		}
		int	score = scorer.calculateScore(totalCleared, chainCount);
		scorer.addScore(score);

		// 重力を適用
		clearer_.applyGravity(board);

		// 落下後に画面を更新
		updateRendering(board, imageManager);

		// 連鎖回数を増加
		chainCount++;
	}
	return chainCount;
}

void	ChainManager::updateRendering(Board& board, ImageManager& imageManager) {
	renderer_.clear();                           // 描画クリア
	renderer_.renderBoard(board, imageManager);   // 盤面描画
	renderer_.present();                         // 描画を反映
}

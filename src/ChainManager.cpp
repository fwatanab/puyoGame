#include "ChainManager.hpp"

ChainManager::ChainManager(PuyoFinder& finder, PuyoClearer& clearer, Renderer& renderer) : finder_(finder), clearer_(clearer), renderer_(renderer) {}

void	ChainManager::processChains(Board& board, SpriteSheet& spriteSheet) {
	int	chainCount = 0; // 連鎖回数のカウント

	while (true) {
		// 消去対象のグループを探索
		std::vector<std::vector<Puyo>>	groups = finder_.findGroupsToClear(board);
		if (groups.empty()) {
			break; // 消去対象がなくなったら終了
		}

		// 削除前に画面を更新
		updateRendering(board, spriteSheet);

		// 1秒待機
		std::this_thread::sleep_for(std::chrono::milliseconds(GRAVITY_SPEED));

		// グループを消去
		clearer_.clearPuyos(board, groups);

		// 消去後に画面を更新
		updateRendering(board, spriteSheet);

		// 1秒待機
		std::this_thread::sleep_for(std::chrono::milliseconds(CHAIN_SPEED));

//		// 得点を計算して加算
//		int	score = scorer_.calculateScore(groups.size(), chainCount);
//		scorer_.addScore(score);

		// 重力を適用
		clearer_.applyGravity(board);

		// 落下後に画面を更新
		updateRendering(board, spriteSheet);

		// 連鎖回数を増加
		chainCount++;
	}
}

void	ChainManager::updateRendering(Board& board, SpriteSheet& spriteSheet) {
	renderer_.clear();                           // 描画クリア
	renderer_.renderBoard(board, spriteSheet);   // 盤面描画
	renderer_.present();                         // 描画を反映
}

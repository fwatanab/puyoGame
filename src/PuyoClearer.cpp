#include "PuyoClearer.hpp"

void PuyoClearer::clearPuyos(Board& board, const std::vector<std::vector<Puyo>>& groups) {
	for (const std::vector<Puyo>& group : groups) {
		for (const Puyo& puyo : group) {
			int	x = puyo.getX();
			int y = puyo.getY();

			// 消去処理（盤面上のぷよを空にする）
			board.getGrid(x, y).setColor(PuyoColor::EMPTY);
		}
	}
}

void PuyoClearer::applyGravity(Board& board) {
	for (int x = 0; x < BOARD_WIDTH; ++x) {
		for (int y = BOARD_HEIGHT - 2; y >= 0; --y) { // 下から上へ探索
			if (board.getGrid(x, y).getColor() != PuyoColor::EMPTY) {
				int	targetY = y;
				while (targetY + 1 < BOARD_HEIGHT && board.getGrid(x, targetY + 1).getColor() == PuyoColor::EMPTY) {
					targetY++;
				}
				
				if (targetY != y) {
					// 落下処理
					board.getGrid(x, targetY).setColor(board.getGrid(x, y).getColor());
					board.getGrid(x, y).setColor(PuyoColor::EMPTY);
				}
			}
		}
	}
}

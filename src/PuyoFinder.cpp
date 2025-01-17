#include "PuyoFinder.hpp"

void	PuyoFinder::dfs(const Board& board, int x, int y, PuyoColor color, std::vector<std::vector<bool>>& visited, std::vector<Puyo>& group) {
	// 範囲外チェック
	if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
		return;
	}
	// 訪問済みまたは色が異なる場合
	if (visited[x][y] || board.getGrid(x, y).getColor() != color) {
		return;
	}
	
	// 訪問済みにマークし、グループに追加
	visited[x][y] = true;
	group.push_back(board.getGrid(x, y));
	
	// 上下左右を探索
	dfs(board, x + 1, y, color, visited, group);
	dfs(board, x - 1, y, color, visited, group);
	dfs(board, x, y + 1, color, visited, group);
	dfs(board, x, y - 1, color, visited, group);
}

std::vector<Puyo>	PuyoFinder::findConnectedPuyos(const Board& board, int startX, int startY) {
	// 訪問フラグと連結したぷよのリストを初期化
	std::vector<std::vector<bool>>	visited(BOARD_WIDTH, std::vector<bool>(BOARD_HEIGHT, false));
	std::vector<Puyo>	connectedGroup;

	// 起点のぷよの色を取得
	PuyoColor	color = board.getGrid(startX, startY).getColor();
	if (color != PuyoColor::EMPTY) {
		dfs(board, startX, startY, color, visited, connectedGroup);
	}

	return connectedGroup;
}

std::vector<std::vector<Puyo>>	PuyoFinder::findGroupsToClear(const Board& board) {
	// 訪問フラグと消去対象のグループを初期化
	std::vector<std::vector<bool>> visited(BOARD_WIDTH, std::vector<bool>(BOARD_HEIGHT, false));
	std::vector<std::vector<Puyo>> groupsToClear;

	for (int x = 0; x < BOARD_WIDTH; ++x) {
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			if (!visited[x][y] && board.getGrid(x, y).getColor() != PuyoColor::EMPTY) {
				// 指定座標から連結したぷよを探索
				std::vector<Puyo> group = findConnectedPuyos(board, x, y);
				if (group.size() >= 4) { // 4つ以上連結している場合
					groupsToClear.push_back(group);
				}
				// 探索済みにマーク
				for (std::vector<Puyo>::const_iterator it = group.begin(); it != group.end(); ++it) {
					visited[it->getX()][it->getY()] = true;
				}
			}
		}
	}

	return groupsToClear;
}

#ifndef PUYOFINDER_HPP
#define PUYOFINDER_HPP

#include <vector>
#include "Puyo.hpp"
#include "Board.hpp"

class	PuyoFinder {
	public:
		// 消去対象のぷよグループを探索
		std::vector<std::vector<Puyo>>	findGroupsToClear(const Board& board);

		std::vector<Puyo>	findConnectedPuyos(const Board& board, int startX, int startY);

	private:
		void	dfs(const Board& board, int x, int y, PuyoColor color, std::vector<std::vector<bool>>& visited, std::vector<Puyo>& group);
};

#endif

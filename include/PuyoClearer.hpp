#ifndef PUYO_CLEARER_HPP
#define PUYO_CLEARER_HPP

#include "Board.hpp"
#include <vector>

class	PuyoClearer {
	public:
		// 消去処理
		void	clearPuyos(Board& board, const std::vector<std::vector<Puyo>>& groups);

		// 重力適用
		void	applyGravity(Board& board);
};

#endif

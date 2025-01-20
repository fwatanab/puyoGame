#ifndef PUYOPAIR_HPP
#define PUYOPAIR_HPP

#include <Puyo.hpp>

// 前方宣言
class	Board;

class	PuyoPair{
	public:
		PuyoPair(PuyoColor color1, PuyoColor color2, int startX = 2, int startY = 0);

		// 移動や回転処理
		void	moveLeft();
		void	moveRight();
		void	moveDown();
		void	rotate();

		// ぷよの色と位置を取得するためのメソッド
		Puyo&	getPrimaryPuyo();    // 下側のぷよ
		const Puyo&	getPrimaryPuyo() const; // constな参照
		Puyo&	getSecondaryPuyo();  // 上側のぷよ
		const Puyo&	getSecondaryPuyo() const;

		int	getRotate() const;

		bool	areBothFixed(const Board& board) const;

	private:
		Puyo	primaryPuyo_; // 下側のぷよ
		Puyo	secondaryPuyo_; // 上側のぷよ
		int	rotationState_; // 回転状態（0:初期, 1:右, 2:下, 3:左）
};

#endif

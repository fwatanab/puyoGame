#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

class	ScoreManager {
	public:
		ScoreManager();

		// 得点計算
		int	calculateScore(int numCleared, int chainCount) const;

		// 現在のスコアを取得
		int	getTotalScore() const;

		// スコアを加算
		void	addScore(int score);

	private:
		int	totalScore_;
		const int	baseScore_ = 10;
};

#endif

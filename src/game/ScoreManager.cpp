#include "ScoreManager.hpp"

ScoreManager::ScoreManager() : totalScore_(0) {}

int ScoreManager::calculateScore(int numCleared, int chainCount) const {
	if (numCleared <= 0) {
		return 0;
	}
	const int comboBonus = chainCount + 1;
	return baseScore_ * numCleared * comboBonus;
}

int ScoreManager::getTotalScore() const {
	return totalScore_;
}

void ScoreManager::addScore(int score) {
	if (score <= 0) {
		return;
	}
	totalScore_ += score;
}

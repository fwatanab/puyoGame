#include "GameManager.hpp"

void	GameManager::startSoloGame() {
	Game	currentGame();
	if (!currentGame.init())
		return;
	currentGame.run();
}

void	GameManager::startDuoGame() {
}

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "Game.hpp"

class	GameManager {
	public:
		void startSoloGame();  // ソロモードの開始
		void startDuoGame();   // デュオモードの開始
	private:
		Game	currentGame; // 現在進行中のゲーム
};

#endif

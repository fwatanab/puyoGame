#include "Game.hpp"
#include <algorithm>

Game::Game() : isRunning_(false), renderer_(nullptr), imageManager_(ImageManager()), board_(nullptr), chainManager_(nullptr), scoreManager_(), lastChainCount_(0), bestChainCount_(0) {
	puyoPairs_.reserve(3);
}

Game::~Game() {
	close();
}

bool	Game::init() {
	try {
		// GameRenderer を初期化
		renderer_ = new GameRenderer("Puyo Game");
		// ImageManager を初期化
		imageManager_.initTextures(renderer_->getSDLRenderer());
		// Board を初期化
		board_ = new Board();
		// PuyoPair を初期化(vector)
		for (int i = 0; i < 3; ++i) {
			puyoPairs_.emplace_back(new PuyoPair(board_->getRandomColor(), board_->getRandomColor()));
		}

		// ChainManager を初期化
		chainManager_ = new ChainManager(finder_, clearer_, *renderer_);
	} catch (const std::runtime_error& e) {
		std::cerr << "Initialization error: " << e.what() << std::endl;
		return false;
	}


	isRunning_ = true;
	return true;
}

void	Game::run() {
	while (isRunning_) {
		handleEvents(); // イベント処理
		update(); // ゲームロジックの更新
		render(); // 描画
	}
}

void	Game::handleEvents() {
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			isRunning_ = false;
		}

		// ペア全体として動けない場合
		if (!board_->canMoveDown(*puyoPairs_.front())) {
			// 片方が固定された場合、もう片方を強制的に落下させる
			if (!board_->canMoveDown(puyoPairs_.front()->getPrimaryPuyo(), puyoPairs_.front()->getSecondaryPuyo())) {
				board_->forceDrop(puyoPairs_.front()->getSecondaryPuyo(), puyoPairs_.front()->getPrimaryPuyo());
			} else if (!board_->canMoveDown(puyoPairs_.front()->getSecondaryPuyo(), puyoPairs_.front()->getPrimaryPuyo())) {
				board_->forceDrop(puyoPairs_.front()->getPrimaryPuyo(), puyoPairs_.front()->getSecondaryPuyo());
			}

			return; // 入力処理を終了
		}

		// 入力処理
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if (board_->canMoveLeft(*puyoPairs_.front())) {
						puyoPairs_.front()->moveLeft(); // 左に移動
					}
					break;
				case SDLK_RIGHT:
					if (board_->canMoveRight(*puyoPairs_.front())) {
						puyoPairs_.front()->moveRight(); // 右に移動
					}
					break;
				case SDLK_DOWN:
					while (board_->canMoveDown(*puyoPairs_.front())) {
						puyoPairs_.front()->moveDown(); // 下に移動
					}
					break;
				case SDLK_UP:
					if (board_->canRotate(*puyoPairs_.front())) {
						puyoPairs_.front()->rotate(); // 回転
					}
					break;
			}
		}
	}
}

void Game::update() {
	static Uint32	lastDropTime = SDL_GetTicks();
	Uint32	currentTime = SDL_GetTicks();

	if (puyoPairs_.front()->areBothFixed(*board_)) {
		// 両方が固定されている場合、盤面に固定し新しいペアを生成
		board_->fixPuyo(puyoPairs_.front()->getPrimaryPuyo());
		board_->fixPuyo(puyoPairs_.front()->getSecondaryPuyo());

		if (!puyoPairs_.empty()) {
			delete puyoPairs_.front(); // 先頭ペアを削除
			puyoPairs_.erase(puyoPairs_.begin()); // ベクタの先頭を削除
			// 新しいペアを追加
			puyoPairs_.emplace_back(new PuyoPair(board_->getRandomColor(), board_->getRandomColor()));
		} else {
			std::cerr << "Error: puyoPairs_ is unexpectedly empty." << std::endl;
		}

		if (board_->isGameOver()) {
			isRunning_ = false;
		}

		// 連鎖処理を実行
		int	chainCount = chainManager_->processChains(*board_, imageManager_, scoreManager_);
		lastChainCount_ = chainCount;
		if (chainCount > bestChainCount_) {
			bestChainCount_ = chainCount;
		}

		lastDropTime = currentTime;
		return;
	}

	if (!board_->canMoveDown(*puyoPairs_.front())) {
		// 片方が固定された場合、もう片方を強制的に落下させる
		if (!board_->canMoveDown(puyoPairs_.front()->getPrimaryPuyo(), puyoPairs_.front()->getSecondaryPuyo())) {
			board_->forceDrop(puyoPairs_.front()->getSecondaryPuyo(), puyoPairs_.front()->getPrimaryPuyo());
		} else if (!board_->canMoveDown(puyoPairs_.front()->getSecondaryPuyo(), puyoPairs_.front()->getPrimaryPuyo())) {
			board_->forceDrop(puyoPairs_.front()->getPrimaryPuyo(), puyoPairs_.front()->getSecondaryPuyo());
		}
	}

	// 一定間隔での自動落下処理
	if (currentTime - lastDropTime >= DROP_INTERVAL) {
		if (board_->canMoveDown(*puyoPairs_.front())) {
			puyoPairs_.front()->moveDown();
		}
		lastDropTime = currentTime;
	}
}

void	Game::render() {
	renderer_->clear();
	renderer_->renderBoard(*board_, imageManager_);
	if (puyoPairs_.size() > 2) {
		renderer_->renderPuyoPair(*puyoPairs_[0], imageManager_);
		renderer_->renderSidePanel(*puyoPairs_[1], *puyoPairs_[2], scoreManager_.getTotalScore(), lastChainCount_, bestChainCount_, imageManager_);
	} else {
		std::cerr << "Error: puyoPairs_ does not have enough elements." << std::endl;
	}
	renderer_->present();
}

void	Game::close() {
	if (renderer_) {
		delete renderer_;
		renderer_ = nullptr;
	}
	if (board_) {
		delete board_;
		board_ = nullptr;
	}
	for (std::vector<PuyoPair*>::iterator	it = puyoPairs_.begin(); it != puyoPairs_.end(); ++it) {
		delete *it;
	}
	puyoPairs_.clear();
	if (chainManager_) {
		delete chainManager_;
		chainManager_ = nullptr;
	}
}

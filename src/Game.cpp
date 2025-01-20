#include "Game.hpp"

Game::Game() : isRunning_(false), spriteSheet_(SpriteSheet()), renderer_(nullptr), board_(nullptr), puyoPair_(nullptr), chainManager_(nullptr) {}

Game::~Game() {
	close();
}

bool	Game::init() {
	try {
		// Renderer を初期化
		renderer_ = new Renderer("Puyo Game");
		// SpriteSheet のロード
		std::string assetPath = std::string(ASSETS_DIR) + "/images/puyo_sozai.png";
		if (!spriteSheet_.load(assetPath.c_str(), renderer_->getSDLRenderer())) {
			std::cerr << "Failed to load sprite sheet! SDL_image Error: " << IMG_GetError() << std::endl;
			return false;
		}
		board_ = new Board();
		puyoPair_ = new PuyoPair(board_->getRandomColor(), board_->getRandomColor()); // 初期のぷよを生成

		// ChainManager のセットアップ
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
		if (!board_->canMoveDown(*puyoPair_)) {
			// 片方が固定された場合、もう片方を強制的に落下させる
			if (!board_->canMoveDown(puyoPair_->getPrimaryPuyo(), puyoPair_->getSecondaryPuyo())) {
				board_->forceDrop(puyoPair_->getSecondaryPuyo(), puyoPair_->getPrimaryPuyo());
			} else if (!board_->canMoveDown(puyoPair_->getSecondaryPuyo(), puyoPair_->getPrimaryPuyo())) {
				board_->forceDrop(puyoPair_->getPrimaryPuyo(), puyoPair_->getSecondaryPuyo());
			}

			return; // 入力処理を終了
		}

		// 入力処理
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if (board_->canMoveLeft(*puyoPair_)) {
						puyoPair_->moveLeft(); // 左に移動
					}
					break;
				case SDLK_RIGHT:
					if (board_->canMoveRight(*puyoPair_)) {
						puyoPair_->moveRight(); // 右に移動
					}
					break;
				case SDLK_DOWN:
					while (board_->canMoveDown(*puyoPair_)) {
						puyoPair_->moveDown(); // 下に移動
					}
					break;
				case SDLK_UP:
					if (board_->canRotate(*puyoPair_)) {
						puyoPair_->rotate(); // 回転
					}
					break;
			}
		}
	}
}

void Game::update() {
	static Uint32	lastDropTime = SDL_GetTicks();
	Uint32	currentTime = SDL_GetTicks();

	if (puyoPair_->areBothFixed(*board_)) {
		// 両方が固定されている場合、盤面に固定し新しいペアを生成
		board_->fixPuyo(puyoPair_->getPrimaryPuyo());
		board_->fixPuyo(puyoPair_->getSecondaryPuyo());
		delete puyoPair_;
		puyoPair_ = new PuyoPair(board_->getRandomColor(), board_->getRandomColor());

		if (board_->isGameOver()) {
			isRunning_ = false;
		}

		// 連鎖処理を実行
		chainManager_->processChains(*board_, spriteSheet_);

		lastDropTime = currentTime;
		return;
	}

	if (!board_->canMoveDown(*puyoPair_)) {
		// 片方が固定された場合、もう片方を強制的に落下させる
		if (!board_->canMoveDown(puyoPair_->getPrimaryPuyo(), puyoPair_->getSecondaryPuyo())) {
			board_->forceDrop(puyoPair_->getSecondaryPuyo(), puyoPair_->getPrimaryPuyo());
		} else if (!board_->canMoveDown(puyoPair_->getSecondaryPuyo(), puyoPair_->getPrimaryPuyo())) {
			board_->forceDrop(puyoPair_->getPrimaryPuyo(), puyoPair_->getSecondaryPuyo());
		}
	}

	// 一定間隔での自動落下処理
	if (currentTime - lastDropTime >= DROP_INTERVAL) {
		if (board_->canMoveDown(*puyoPair_)) {
			puyoPair_->moveDown();
		}
		lastDropTime = currentTime;
	}
}

void	Game::render() {
	renderer_->clear();
	renderer_->renderBoard(*board_, spriteSheet_);
	renderer_->renderPuyoPair(*puyoPair_, spriteSheet_);
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
	if (puyoPair_) {
		delete puyoPair_;
		puyoPair_ = nullptr;
	}
	if (chainManager_) {
		delete chainManager_;
		chainManager_ = nullptr;
	}
	SDL_Quit();
}

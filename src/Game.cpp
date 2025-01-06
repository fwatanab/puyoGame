#include <Game.hpp>

Game::Game() : window_(nullptr), renderer_(nullptr), isRunning_(false), spriteSheet_(SpriteSheet()) {}

Game::~Game() {
	close();
}

bool	Game::init() {
	if (SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software") == SDL_FALSE) {
		std::cerr << "Warning: Unable to set SDL_HINT_RENDER_DRIVER to software!" << std::endl;
		return false;
	}
	window_ = SDL_CreateWindow("puyoGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window_) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer_) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	std::string assetPath = std::string(ASSETS_DIR) + "/images/puyo_sozai.png";
	if (!spriteSheet_.load(assetPath.c_str(), renderer_)) {
		std::cerr << "Failed to load sprite sheet! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	board_ = new Board();
	puyoPair_ = new PuyoPair(board_->getRandomColor(), board_->getRandomColor()); // 初期のぷよを生成
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

		// ペアとして下に動かせるかを判定
		bool isFixed = !board_->canMoveDown(*puyoPair_);
		if (isFixed) {
			// もしペアとして動かせない＝固定状態なので、入力を無効化して終了
			return;
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
						puyoPair_->moveDown(*board_);
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

void	Game::update() {
	static Uint32 lastDropTime = SDL_GetTicks();
	Uint32 currentTime = SDL_GetTicks();

	if (!board_->canMoveDown(*puyoPair_)) {
		board_->fixPuyo(puyoPair_->getPrimaryPuyo());
		board_->fixPuyo(puyoPair_->getSecondaryPuyo());
		delete puyoPair_; // 既存の PuyoPair を削除
		puyoPair_ = new PuyoPair(board_->getRandomColor(), board_->getRandomColor(), 3, 0);

		if (board_->isGameOver()) {
			isRunning_ = false;
		}

		lastDropTime = currentTime;
		return;
	}

	if (currentTime - lastDropTime >= 800) {
		puyoPair_->moveDown(*board_);
		lastDropTime = currentTime;
	}


// 	static Uint32 lastDropTime = SDL_GetTicks(); // 最後の落下時間を記録
// 	Uint32 currentTime = SDL_GetTicks();
// 
// 	// 固定状態をチェック
// 	bool	primaryFixed = !board_->canMoveDown(puyoPair_->getPrimaryPuyo());
// 	bool	secondaryFixed = !board_->canMoveDown(puyoPair_->getSecondaryPuyo());
// 
// 	// 片方が固定された場合
// 	if (primaryFixed && !secondaryFixed) {
// 		puyoPair_->getSecondaryPuyo().setPosition(
// 			puyoPair_->getSecondaryPuyo().getX(),
// 			puyoPair_->getSecondaryPuyo().getY() + 1
// 		);
// 	} else if (!primaryFixed && secondaryFixed) {
// 		puyoPair_->getPrimaryPuyo().setPosition(
// 			puyoPair_->getPrimaryPuyo().getX(),
// 			puyoPair_->getPrimaryPuyo().getY() + 1
// 		);
// 	}
// 	// 両方固定された場合
// 	if (primaryFixed && secondaryFixed) {
// 		board_->fixPuyo(puyoPair_->getPrimaryPuyo());
// 		board_->fixPuyo(puyoPair_->getSecondaryPuyo());
// 		// 新しいペアを生成
// 		puyoPair_ = new PuyoPair(board_->getRandomColor(), board_->getRandomColor(), 3, 0);
// 
// 		// ゲームオーバーをチェック
// 		if (board_->isGameOver()) {
// 			isRunning_ = false;
// 		}
// 
// 		lastDropTime = currentTime; // 固定後はタイマーをリセット
// 		return; // 固定後に移動や入力を無視
// 	}
// 
// 	// 一定間隔で落下処理を実行
// 	if (currentTime - lastDropTime >= 800) {
// 		if (!primaryFixed && board_->canMoveDown(puyoPair_->getPrimaryPuyo())) {
// 			puyoPair_->getPrimaryPuyo().setPosition(
// 				puyoPair_->getPrimaryPuyo().getX(),
// 				puyoPair_->getPrimaryPuyo().getY() + 1
// 			);
// 		}
// 		if (!secondaryFixed && board_->canMoveDown(puyoPair_->getSecondaryPuyo())) {
// 			puyoPair_->getSecondaryPuyo().setPosition(
// 				puyoPair_->getSecondaryPuyo().getX(),
// 				puyoPair_->getSecondaryPuyo().getY() + 1
// 			);
// 		}
// 		lastDropTime = currentTime; // 落下タイマーを更新
// 	}
}

void	Game::render() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer_);

	board_->drawBlock(renderer_, spriteSheet_);
	board_->draw(renderer_, spriteSheet_);

	// primaryPuyo の描画
	SDL_Rect	srcRect1 = board_->getSrcRect(puyoPair_->getPrimaryPuyo().getColor(), spriteSheet_);
	SDL_Rect	destRect1 = board_->getDestRect(puyoPair_->getPrimaryPuyo().getX(), puyoPair_->getPrimaryPuyo().getY());
	SDL_RenderCopy(renderer_, spriteSheet_.getTexture(), &srcRect1, &destRect1);

	// secondaryPuyo の描画
	SDL_Rect	srcRect2 = board_->getSrcRect(puyoPair_->getSecondaryPuyo().getColor(), spriteSheet_);
	SDL_Rect	destRect2 = board_->getDestRect(puyoPair_->getSecondaryPuyo().getX(), puyoPair_->getSecondaryPuyo().getY());
	SDL_RenderCopy(renderer_, spriteSheet_.getTexture(), &srcRect2, &destRect2);

	SDL_RenderPresent(renderer_);
}

void	Game::close() {
	if (renderer_) {
		SDL_DestroyRenderer(renderer_);
	}

	if (window_) {
		SDL_DestroyWindow(window_);
	}

	SDL_Quit();
}

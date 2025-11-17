#ifndef PUYOGAME_HPP
#define PUYOGAME_HPP

class	PuyoGame {
	public:
		PuyoGame();
		~PuyoGame();

		void	run();

	private:
		void	cleanup();

		bool	sdlInitialized_;
		bool	imgInitialized_;
};

#endif

#ifndef PUYO_HPP
#define PUYO_HPP

enum class	PuyoColor {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	WALL,
	EMPTY
};

class	Puyo {
	public:
		Puyo();
		Puyo(PuyoColor color, int x, int y);
		~Puyo();

		PuyoColor	getColor() const;
		void	setColor(PuyoColor color);

		int	getX() const;
		int	getY() const;
		void	setX(int x);
		void	setY(int y);
		void	setPosition(int x, int y);

		bool	isFixed() const;
		void	fix();

	private:
		PuyoColor	color_; // ぷよの色
		int	x_, y_; // ぷよの位置
		bool	fixed_; // ぷよが固定されているかどうか
};

#endif

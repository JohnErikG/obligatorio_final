#pragma once
#include "../utilidades/vector2.h"
#include "../utilidades/color.h"
class pixel
{
private:
	int x, y;
	color color_;

public:
		pixel(int x, int y, color  col) : x(x), y(y), color_(col) {}
		int getX() const { return x; }
		int getY() const { return y; }
		void setX(int newX) { x = newX; }
		void setY(int newY) { y = newY; }
		vector2 getVector2() const { return vector2(x, y); }
	pixel(int x, int y, color color) : x(x), y(y), color_(color) {}
	int getX() const { return x; }
	int getY() const { return y; }
	color getColor() const { return color_; }
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setColor(color c) { color_ = c; }
	vector2 getVector2() const { return vector2(x, y); }
};


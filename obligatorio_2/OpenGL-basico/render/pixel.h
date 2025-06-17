#pragma once
#include "../utilidades/vector2.h"
class pixel
{
	private:
		int x, y;
		int r, g, b;
		
public:
		pixel(int x, int y, int r, int g, int b) : x(x), y(y), r(r), g(g), b(b) {}
		int getX() const { return x; }
		int getY() const { return y; }
		int getR() const { return r; }
		int getG() const { return g; }
		int getB() const { return b; }
		void setX(int newX) { x = newX; }
		void setY(int newY) { y = newY; }
		void setR(int newR) { r = newR; }
		void setG(int newG) { g = newG; }
		void setB(int newB) { b = newB; }
		vector2 getVector2() const { return vector2(x, y); }
};


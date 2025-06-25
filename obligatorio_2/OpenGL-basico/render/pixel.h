#pragma once
#include "../utilidades/vector2.h"
class pixel
{
	private:
		int x, y;
		float  r, g, b;
		float alfa;
		
public:
		pixel(int x, int y, float  r, float g, float b, float alf) : x(x), y(y), r(r), g(g), b(b), alfa(alf) {}
		int getX() const { return x; }
		int getY() const { return y; }
		float getR() const { return r; }
		float getG() const { return g; }
		float getB() const { return b; }
		float getAlfa() const { return alfa; }
		void setX(int newX) { x = newX; }
		void setY(int newY) { y = newY; }
		void setR(int newR) { r = newR; }
		void setG(int newG) { g = newG; }
		void setB(int newB) { b = newB; }
		vector2 getVector2() const { return vector2(x, y); }
};


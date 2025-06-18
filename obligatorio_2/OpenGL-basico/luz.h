#pragma once
#include "utilidades/vector3.h"

class luz
{
private:
	vector3 posicion;
	vector3 color;
	float intensidad;

public:	
	luz(const vector3& pos, const vector3& col, double inten)
		: posicion(pos), color(col), intensidad(inten) {
	}
	vector3 getPosicion() const { return posicion; }
	vector3 getColor() const { return color; }
	float getIntensidad() const { return intensidad; }
	~luz() = default;
};


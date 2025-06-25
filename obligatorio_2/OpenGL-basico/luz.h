 #pragma once
#include "utilidades/vector3.h"
#include "objetos/objeto.h"
#include <vector>
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
	bool iluminacion(vector3& interseccion, vector3& normal, std::vector<objeto*> objetos, objeto* actual, float& inte);	~luz() = default;
};


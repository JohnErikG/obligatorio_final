 #pragma once
#include "utilidades/vector3.h"
#include "objetos/objeto.h"
#include <vector>
#include "utilidades/color.h"
class luz
{
private:
	vector3 posicion;
	vector3 colo;
	float intensidad;

public:	
	luz(const vector3& pos, const vector3& col, double inten)
		: posicion(pos), colo(col), intensidad(inten) {
	}
	vector3 getPosicion() const { return posicion; }
	color getColor() const { color(colo.get_x(), colo.get_y(), colo.get_z(), intensidad); }
	float getIntensidad() const { return intensidad; }
	bool iluminacion(vector3& interseccion, vector3& normal, std::vector<objeto*> objetos, objeto* actual, float& inte);	~luz() = default;
};


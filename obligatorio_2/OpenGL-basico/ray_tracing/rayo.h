#pragma once
#include "../utilidades/vector3.h"
class rayo
{
private:
	vector3 origen;
	vector3 direccion;
public:
	rayo() {
		origen = vector3(0, 0, 0);
		direccion = vector3(0, 0, 0);
	}
	rayo(vector3 o, vector3 d) : origen(o), direccion(d) {}
	vector3 getOrigen() const { return origen; }
	vector3 getDireccion() const { return direccion; }
	void setOrigen(const vector3& o) { origen = o; }
	void setDireccion(const vector3& d) { direccion = d; }

};


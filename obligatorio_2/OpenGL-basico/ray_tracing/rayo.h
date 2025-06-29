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
	vector3 getOrigen() const;
	vector3 getDireccion() const;
	void setOrigen(const vector3 o);
	void setDireccion(const vector3 d);
	vector3 get_rayo_vector() const;
	rayo reflejar(const vector3& interseccion, const vector3& normal) const;
	rayo refractar(const vector3& interseccion, const ::vector3& normal, float indice_refraccion) const;

};


#pragma once
#include "objeto.h"
#include "../utilidades/vector3.h"
#include <iostream>

class pared : public objeto {
	vector3 normal;
	float a, b, c, d;
	vector3 punto1, punto2;
	float altura, ancho;
public:
	pared(vector3 pos, vector3 normal_, vector3 color, float alfa,float bri, float refle, float transluc, float indiRef, float h, float w) : objeto(pos, color, alfa, refle, transluc, indiRef, bri) {
		altura = h;
		ancho = w;
		normal = normal_.normalize();
		a = normal.get_x();
		b = normal.get_y();
		c = normal.get_z();
		d = -(a * pos.get_x() + b * pos.get_y() + c * pos.get_z());
		vector3 arbitrario = vector3(0, 0, 1);
		if (normal == vector3(0, 0, 1) || normal == vector3(0, 0, -1)) {
			arbitrario = vector3(1, 0, 0);
		}
		punto1 = (normal * arbitrario).normalize();
		punto2 = (punto1 * normal).normalize();
	}
	bool intereseccion(rayo& origen, vector3& punto, vector3& normal) override ;
	
	~pared() override ;
};
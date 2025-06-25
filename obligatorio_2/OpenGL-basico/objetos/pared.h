#pragma once
#include "../utilidades/vector3.h"
#include "objeto.h"
class pared : public objeto {
	vector3 normal;
	float a, b, c, d;
	vector3 punto1, punto2;
	float altura, ancho;
public:
	pared (vector3 pos , vector3 normal_, float alfa, float refle , float transluc , float indiRef, float h, float w) : objeto(pos, color , alfa,refle, transluc , indiRef) {
		altura = h;
		ancho = w;
		normal = normal_.normalize();
		a = normal.get_x();
		b = normal.get_y();
		c = normal.get_z();
		d = -(a * punto1.get_x() + b * punto1.get_y() + c * punto1.get_z());
		vector3 arbitrario = vector3(0, 0, 1);
		if (a == 0 && b==0 && (c==1 || c==-1)) {
			arbitrario = vector3(0, 1, 0);
		}
		punto1 = (normal*arbitrario).normalize();
		punto2 = (punto1 * normal).normalize();
	}
	bool interseccion(vector3& origen, vector3& punto, vector3 normal);
	
	~pared() override ;
};
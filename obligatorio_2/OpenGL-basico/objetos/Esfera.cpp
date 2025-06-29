#include "esfera.h"
#include <iostream>


bool esfera::intereseccion(rayo& ra, vector3& punto, vector3& normal)
{
	vector3 r = ra.getOrigen() - getpos();
	vector3 RN = ra.getDireccion().normalize();
	float a = RN.dot_product(RN); 
	float b = 2.0 * r.dot_product(RN);
	float c = r.dot_product(r) - radio * radio;
	float discriminante = b * b - 4.0 * a * c;
	if (discriminante < 0.0) {
		return false; //no hay intereseccion
	 }
	float raiz = sqrt(discriminante);
	float r1 = (-b - raiz) / (2.0 * a);
	float r2 = (-b + raiz) / (2.0 * a);
	if (r1 < 0 && r2 < 0) {
		return false; //no hay intereseccion
	}
	float t;
	if (r1 > 0 && r2 > 0) {
		t = std::min(r1,r2);
	}
	 else {
		t = std::max(r1, r2);
	}
	punto = ra.getOrigen() + RN * t;
	normal = (punto - getpos()).normalize();
	return true; //hay intereseccion
}


esfera::~esfera()
{
}

#include "cilindro.h"
#include "iostream"
bool cilindro::calcular_interseccion(rayo& ra, vector3& punto, vector3& normal) {
	vector3  dir = ra.getDireccion();
	vector3  origen = ra.getOrigen() - getpos();
	float a = dir.get_x()* dir.get_x() + dir.get_z() * dir.get_z(); 
	float b = 2 * (dir.get_x() * origen.get_x() + dir.get_z() * origen.get_z()); 
	float c = origen.get_x() * origen.get_x() + origen.get_z() * origen.get_z() - std::pow(radio, 2); 
	float dis = b * b - 4 * a * c; 
	if (dis < 0) {
		return false; 
	}
	float sd = sqrt(dis);
	float t1 = (-b - sd) / (2 * a); 
	float t2 = (-b + sd) / (2 * a); 
	if (t1 >= t2) {
		std::swap(t1, t2); 
	}
	vector3 p1 = ra.getOrigen() + dir*t1; 
	if (t1 >= 0) {
		p1 = ra.getOrigen() + dir*t1; 
		if (p1.get_y() >= getpos().get_y() && p1.get_y() <= getpos().get_y() + altura) {
			punto = p1;
			vector3 puntoLocal = p1 - getpos();
			normal = vector3(puntoLocal.get_x(), 0, puntoLocal.get_z()).normalize(); 
			return true;
		}
	}
	if (p1.get_y() > pos.get_y() + altura) {
		if (top.calcular_interseccion(ra, punto, normal)) {
			return std::pow((punto.get_x() - pos.get_x()), 2) + std::pow((punto.get_z() - pos.get_z()), 2) <= std::pow(radio, 2);
		}
	}

	if (p1.get_y()< pos.get_y())
	{
		if (base.calcular_interseccion(ra, punto, normal))
		{
			return std::pow((punto.get_x() - pos.get_x()), 2) + std::pow((punto.get_z() - pos.get_z()), 2) <= std::pow(radio, 2);
		}
	}
	return false; 
}
cilindro::~cilindro() {}


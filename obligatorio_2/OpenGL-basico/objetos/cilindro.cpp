#include "cilindro.h"
#include "iostream"
bool cilindro::intereseccion(rayo& ra, vector3& punto, vector3& normal) {
	vector3  dir = ra.getDireccion();
	vector3  origen = ra.getOrigen() - getpos();
	float a = dir.get_x()* dir.get_x() + dir.get_z() * dir.get_z(); // Coeficiente cuadrático
	float b = 2 * (dir.get_x() * origen.get_x() + dir.get_z() * origen.get_z()); // Coeficiente lineal
	float c = origen.get_x() * origen.get_x() + origen.get_z() * origen.get_z() - std::pow(radio, 2); // Término independiente
	float discriminante = b * b - 4 * a * c; // Discriminante de la ecuación cuadrática
	if (discriminante < 0) {
		return false; // No hay intersección
	}
	float sd = sqrt(discriminante);
	float t1 = (-b - sd) / (2 * a); // Primer punto de intersección
	float t2 = (-b + sd) / (2 * a); // Segundo punto de intersección
	if (t1 >= t2) {
		std::swap(t1, t2); // Aseguramos que t1 sea el menor
	}
	vector3 p1 = ra.getOrigen() + dir*t1; // Punto de intersección más cercano
	if (t1 >= 0) {
		p1 = ra.getOrigen() + dir*t1; // Punto de intersección más cercano
		if (p1.get_y() >= getpos().get_y() && p1.get_y() <= getpos().get_y() + altura) {
			punto = p1;
			vector3 puntoLocal = p1 - getpos(); // Punto en coordenadas locales
			normal = vector3(puntoLocal.get_x(), 0, puntoLocal.get_z()).normalize(); // Normal del cilindro
			return true;
		}
	}
	if (p1.get_y() > pos.get_y() + altura) {
		if (top.intereseccion(ra, punto, normal)) {
			return std::pow((punto.get_x() - pos.get_x()), 2) + std::pow((punto.get_z() - pos.get_z()), 2) <= std::pow(radio, 2);
		}
	}

	if (p1.get_y()< pos.get_y())
	{
		if (base.intereseccion(ra, punto, normal))
		{
			return std::pow((punto.get_x() - pos.get_x()), 2) + std::pow((punto.get_z() - pos.get_z()), 2) <= std::pow(radio, 2);
		}
	}
	return false; 
}
cilindro::~cilindro() {}


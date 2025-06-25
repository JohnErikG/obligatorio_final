#include "cilindro.h"
#include "iostream"
bool intereseccion(rayo& ra, vector3& punto, vector3& normal) {
	vector3  dir = ra.getDireccion();
	vector3  origen = ra.getOrigen() - getpos();
	float a = dir.get_x()* dir.get_x() + dir.get_z() * dir.get_z(); // Coeficiente cuadrático
	float b = 2 * (dir.get_x() * origen.get_x() + dir.get_z() * origen.get_z()); // Coeficiente lineal
	float c = origen.get_x() * origen.get_x() + origen.get_z() * origen.get_z() - std::pow(radio, 2); // Término independiente
	return true; 
}



#include "pared.h"

bool pared::calcular_interseccion(rayo& r, vector3& punto, vector3& nor)  {

	vector3 rN = r.getDireccion().normalize();
	float d = rN.get_x() * normal.get_x() + rN.get_y() * normal.get_y() + rN.get_z() * normal.get_z(); 
	if (fabs(d) < 1e-6) { return false; } 

	vector3 aux = getpos() - r.getOrigen();
	float t = normal.dot_product(aux) / d;
	

 if (t > 0.0) {
		vector3 p = r.getOrigen() + rN * t; 
		vector3 paux = p - getpos(); 
		float u = 0;
		float v = 0;
		if (nor == vector3(1, 0, 0) || nor == vector3(-1, 0, 0)) { 
			u = (paux.get_y() * punto1.get_z() - paux.get_z() * punto1.get_y()) / (punto2.get_y() * punto1.get_z() - punto2.get_z() * punto1.get_y());
			v = (paux.get_z() * punto2.get_y() - paux.get_y() * punto2.get_z()) / (punto2.get_y() * punto1.get_z() - punto2.get_z() * punto1.get_y());
		}
		else if (nor == vector3(0, 1, 0) || nor == vector3(0, -1, 0))
		{
			u = (paux.get_x() * punto1.get_z() - paux.get_z() * punto1.get_x()) / (punto2.get_x() * punto1.get_z() - punto2.get_z() * punto1.get_x());
			v = (paux.get_z() * punto2.get_x() - paux.get_x() * punto2.get_z()) / (punto2.get_x() * punto1.get_z() - punto2.get_z() * punto1.get_x());
		}
		else if (nor == vector3(0, 0, 1) || nor == vector3(0, 0, -1))
		{
			u = (paux.get_x() * punto1.get_y() - paux.get_y() * punto1.get_x()) / (punto2.get_x() * punto1.get_y() - punto2.get_y() * punto1.get_x());
			v = (paux.get_y() * punto2.get_x() - paux.get_x() * punto2.get_y()) / (punto2.get_x() * punto1.get_y() - punto2.get_y() * punto1.get_x());
		}
		
		if (fabs(u) <= ancho && fabs(v) <= altura)
		{
			punto.set_x(p.get_x());
			punto.set_y(p.get_y());
			punto.set_z(p.get_z());
			vector3 aux_norm = normal.normalize(); 
			nor.set_x(aux_norm.get_x());
			nor.set_y(aux_norm.get_y());
			nor.set_z(aux_norm.get_z());
			return true;
		}
	}
 return false;
}

pared::~pared()
{
}

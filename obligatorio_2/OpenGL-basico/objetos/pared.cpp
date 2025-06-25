#include "pared.h"

bool pared::intereseccion(rayo& r, vector3& punto, vector3& nor)  {

	vector3 rN = r.getDireccion().normalize();
	float d = nor.dot_product(rN);
	if (fabs(d) < 1e-6) { return false; } // rayo paralelo al plano
	vector3 aux = getpos() - r.getOrigen();
	float t = aux.dot_product(nor) / d;
	float u, v;
	if (t < 0) { return false; } // rayo no intersecta el plano
	else if (t > 0.0) {
		vector3 p = r.getOrigen() + rN * t; // punto de intersección
		vector3 paux = p - getpos(); // vector desde el centro de la pared al punto de intersección
		if ((nor.get_x() == 1 || nor.get_x() == -1) && nor.get_y() == 0 && nor.get_z() == 0) { // pared vertical
			u = (paux.get_y() * punto1.get_z() - paux.get_z() * punto1.get_y()) / (punto2.get_y() * punto1.get_z() - punto2.get_z() * punto1.get_y());
			v = (paux.get_z() * punto2.get_y() - paux.get_y() * punto2.get_z()) / (punto2.get_y() * punto1.get_z() - punto2.get_z() * punto1.get_y());
		}
		else if (nor.get_x() == 0 && (nor.get_y() == -1 || nor.get_y() == 1) && nor.get_z() == 0)
		{
			u = (paux.get_x() * punto1.get_z() - paux.get_z() * punto1.get_x()) / (punto2.get_x() * punto1.get_z() - punto2.get_z() * punto1.get_x());
			v = (paux.get_z() * punto2.get_x() - paux.get_x() * punto2.get_z()) / (punto2.get_x() * punto1.get_z() - punto2.get_z() * punto1.get_x());
		}
		else if (nor.get_x() == 0 && nor.get_y() == 0 && (nor.get_z() == -1 || nor.get_z() == 1))
		{
			u = (paux.get_x() * punto1.get_y() - paux.get_y() * punto1.get_x()) / (punto2.get_x() * punto1.get_y() - punto2.get_y() * punto1.get_x());
			v = (paux.get_y() * punto2.get_x() - paux.get_x() * punto2.get_y()) / (punto2.get_x() * punto1.get_y() - punto2.get_y() * punto1.get_x());
		}

		if (fabs(u) <= ancho && fabs(v) <= altura)
		{
			punto.set_x(p.get_x());
			punto.set_y(p.get_y());
			punto.set_z(p.get_z());
			vector3 aux_norm = nor.normalize(); // Normal del plano = normal en el punto de intersección
			normal.set_x(aux_norm.get_x());
			normal.set_y(aux_norm.get_y());
			normal.set_z(aux_norm.get_z());
			return true;
		}
	}
	return false;
}

pared::~pared()
{
}

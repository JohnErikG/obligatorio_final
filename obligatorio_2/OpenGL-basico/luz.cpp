#include "luz.h"
#include "ray_tracing/rayo.h"
#include <iostream>
bool luz::iluminacion(vector3& interseccion, vector3& normal, std::vector<objeto*> objetos, objeto* actual, float& inte)
{
	inte = 0.0f;
	vector3 ra = (this->posicion - interseccion).normalize();
	float p = normal.dot_product(ra);
	if (p >= 0.0f) {
		inte = getIntensidad() * p;
		rayo sombra = rayo(interseccion + ra*0.0001, ra);
		for (objeto* obj : objetos) {
			vector3 inter = vector3(0, 0, 0);
			vector3 barido = vector3(0, 0, 0);
			if (obj->intereseccion(sombra,inter, barido)) {
				float inter_dist = (inter - interseccion).getNorm();
				float luz_dist = (this->posicion - interseccion).getNorm();
				if (inter_dist > luz_dist) {
					continue; // Hay un objeto entre la luz y el punto de intersección
				}
				inte = std::max(0.0f, inte -(1-  obj->gettransparaencia()));
				return false; // No hay sombra, se ilumina
			}
		}
	}
	return true;
}

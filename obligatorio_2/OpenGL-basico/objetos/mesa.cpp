#include "mesa.h"
#include "mesa.h"

mesa mesa::crearMesa( vector3 pos, vector3 color, float alfa,float bri,  float refle, float translucido, float indiceRef, float alto , float ancho, float prof)
{
	vector3 v0(pos.get_x(), pos.get_y(), pos.get_z());
	vector3 v1(pos.get_x()+ ancho, pos.get_y(), pos.get_z());
	vector3 v2(pos.get_x()+ ancho, pos.get_y() + alto, pos.get_z());
	vector3 v3(pos.get_x(), pos.get_y()+alto, pos.get_z());
	vector3 v4(pos.get_x(), pos.get_y(), pos.get_z()+prof);
	vector3 v5(pos.get_x()+ancho, pos.get_y(), pos.get_z()+prof);
	vector3 v6(pos.get_x()+ancho, pos.get_y()+ alto, pos.get_z()+prof);
	vector3 v7(pos.get_x(), pos.get_y()+ alto, pos.get_z()+prof);

	std::vector<vector3> vertices = { v0, v1, v2, v3, v4, v5, v6, v7 };
	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0, 
		1, 5, 6, 6, 2, 1, 
		4, 5, 6, 6, 7, 4, 
		0, 3, 7, 7, 4, 0, 
		0, 1, 5, 5, 4, 0, 
		2, 3, 7, 7, 6, 2 
	};

    return mesa(vertices , indices ,pos,  color, alfa, bri, refle , translucido, indiceRef);
}

bool mesa::interTri(const vector3& v0, const vector3& v1, const vector3& v2, rayo& rayo, vector3& point, vector3& normal)
{
	
	vector3 edge1 = v1 - v0;
	vector3 edge2 = v2 - v0;


	normal = edge1.cross_product(edge2).normalize();

	vector3 h = rayo.getDireccion().cross_product(edge2);
	double dis = edge1.dot_product(h);

	if (dis > -1e-6 && dis < 1e-6)
		return false;

	double f = 1.0 / dis;
	vector3 s = rayo.getOrigen() - v0;
	double u = f * s.dot_product(h);

	if (u < 0.0 || u > 1.0)
		return false;

	vector3 q = s.cross_product(edge1);
	double v = f * rayo.getDireccion().dot_product(q);

	if (v < 0.0 || u + v > 1.0)
		return false;

	double t = f * edge2.dot_product(q);

	if (t < 1e-6)
		return false;

	point = rayo.getOrigen() + rayo.getDireccion() * t;

	return true;
}

mesa::~mesa()
{
}

bool mesa::calcular_interseccion(rayo& rayo, vector3& punto, vector3& normal){
	bool hit = false;
	float closest_t = std::numeric_limits<float>::max();
	for (size_t i = 0; i < indice.size(); i += 3) // Iteramos sobre los índices de los triángulos
	{
		const vector3& v0 = vertices[indice[i]];
		const vector3& v1 = vertices[indice[i + 1]];
		const vector3& v2 = vertices[indice[i + 2]];

		vector3 temp_point, temp_normal;
		// Variables temporales para  el punto y la normal de intersección del triángulo

		if (interTri(v0, v1, v2, rayo, temp_point, temp_normal))
		{
			hit = true;
			double t = (temp_point - rayo.getOrigen()).get_length();
			if (t < closest_t)
				//  Actualiza el punto de intersección, la normal y la distancia a la más cercana encontrada 
			{
				closest_t = t;
				punto = temp_point;
				normal = temp_normal;
			}
		}
	}

	return hit;
	
}



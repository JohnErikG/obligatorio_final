#pragma once
#include "objeto.h"
#include <vector>
using namespace std;
class mesa : public objeto
{
private:
	vector<vector3> vertices;
	vector <unsigned int> indice;
public :
	mesa(vector<vector3> ver, vector<unsigned int> ind, vector3 pos, vector3 color, float alfa,float bri, float refle, float translucido, float inidceREf)
		: objeto(pos, color, alfa, bri, refle, translucido, inidceREf), vertices(ver), indice(ind)
	{
	}
	static mesa crearMesa( vector3 pos, vector3 color, float alfa,float bri, float refle, float translucido, float inidceREf, float alto, float ancho , float prof);
	bool interTri(const vector3& v0, const vector3& v1, const vector3& v2, rayo& rayo, vector3& point,
		vector3& normal);
	bool intereseccion(rayo& rayo, vector3& punto, vector3& normal)override;
	~mesa() override;
};


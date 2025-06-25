#include "mesa.h"

mesa mesa::crearMesa( vector3 pos, vector3 color, float alfa, float refle, float translucido, float indiceRef, float alto , float ancho, float prof)
{
	//pos vertice sup izquierdo de la mesa 
	vector3 v0(pos.get_x(), pos.get_y(), pos.get_z());
	vector3 v1(pos.get_x(), pos.get_y() - alto, pos.get_z());
	vector3 v2(pos.get_x()+ ancho, pos.get_y() - alto, pos.get_z());
	vector3 v3(pos.get_x()+ancho, pos.get_y(), pos.get_z());
	vector3 v4(pos.get_x()+ancho, pos.get_y(), pos.get_z()-prof);
	vector3 v5(pos.get_x(), pos.get_y(), pos.get_z()- prof);
	vector3 v6(pos.get_x(), pos.get_y()- alto, pos.get_z()-prof);
	vector3 v7(pos.get_x()+ ancho, pos.get_y()- alto, pos.get_z()-prof);

	std::vector<vector3> vertices = { v0, v1, v2, v3, v4, v5, v6, v7 };
	//lista para cuadrilatero  
	std::vector<unsigned int> indices = {0, 1, 2 ,3,//cara frontal
										0, 3,4,5,//cara superior
										0,5,6, 1,//cara izquierda
										1, 6, 7,2,//cara inferior
										2,7,4,3,//cara derecha
										4,7,6,5//cara trasera
										}; 
    return mesa(vertices , indices ,pos,  color, alfa , refle , translucido, indiceRef);
}

bool mesa::interseccion(vector3& origen, vector3& punto, vector3 normal)
{
	return false;
}



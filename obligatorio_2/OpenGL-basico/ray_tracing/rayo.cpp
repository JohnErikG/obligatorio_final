#include "rayo.h"

vector3 rayo::getOrigen() const
{
    return origen;
}

vector3 rayo::getDireccion() const
{
    return direccion;
}

vector3 rayo::get_rayo_vector() const
{
    return direccion - origen;
}

void rayo::setOrigen(vector3 o)
{
    origen = o;
}

void rayo::setDireccion(vector3 dir)
{
    direccion = dir;
}

rayo rayo::reflejar(const vector3& interseccion, const vector3& normal) const
{
    const vector3 dir_vista = get_rayo_vector();
    const vector3 normal_int = normal;
    vector3 dir_reflejada = dir_vista -  normal_int * dir_vista.dot_product(normal_int) * 2 ;

    return rayo(interseccion + dir_reflejada * 0.00001, dir_reflejada);
}

rayo rayo::refractar(const vector3& interseccion, const vector3& normal,
    double indice_refraccion) const
{
    const vector3 rayo_incidente = this->getDireccion().normalize();
    const vector3 normal_int = normal.normalize();

    const double n1 = 1.0; 
    const double n2 = indice_refraccion;

    double cos_i = -rayo_incidente.dot_product(normal_int);
    double sin_t2 = (n1 / n2) * (n1 / n2) * (1.0 - cos_i * cos_i);

    if (sin_t2 > 1.0)
    {
        return rayo(interseccion, this->getDireccion());
    }

    double cos_t = std::sqrt(1.0 - sin_t2);
    vector3 direccion_refractada = (rayo_incidente * (n1 / n2) + normal_int * (cos_t - cos_i * (n1 / n2))).normalize();

    return rayo (interseccion + direccion_refractada * 0.001, direccion_refractada);
}

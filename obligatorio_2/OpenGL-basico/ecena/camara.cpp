#include "camara.h"

vector3 camara::get_position() const
{
    return pos;
}


void camara::crear_rayo(float u, float v, rayo& ray)
{

    vector3 pixel = centro + (U * u);
    pixel = pixel + (V * v);

    ray.setOrigen(pos);
    ray.setDireccion(pixel);
}

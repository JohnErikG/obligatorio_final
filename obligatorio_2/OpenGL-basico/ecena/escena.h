#pragma once
#include "camara.h"
#include "../objetos/objeto.h"
#include "../render/imagen.h"
#include "../luz.h"
#include "SDL.h"
#include "../esenas/parceo.h"
class escena
{
    color color_fondo_, ambiente_;
    int ancho_, alto_;
    camara* camara_;
    std::vector<objeto*> Objetos;
    std::vector<luz*> lights_;
    imagen final_;
    imagen aux_relfexion_;
    imagen aux_refraccion_;
    int iteraciones_ = 0;
    bool terminado_ = false;

    bool cast_rayo(rayo& rayo_casteado,
        const objeto* objeto_actual,
        objeto*& objeto_cercano,
        vector3& punto_interseccion,
        vector3& normal_interseccion) const;

    static int max_depth_;

public:
    escena(const char* archivo_escena);
    void Render( int progreso);
    bool termino();
    imagen get_imagen_final();
    imagen get_imagen_reflexion();
    imagen get_imagen_refraccion();
    int get_iter();
    int get_ancho();
    int get_alto();
    color get_color_fondo();
    color calcular_color(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano,
        int nivel);
    color whitted_ray_tracing(rayo& rayo, float& aux_reflectividad, float& aux_refractividad, int nivel);
    color calcular_difuso(rayo& rayo_camara, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano,
        luz* luz);
    color calcular_especular(rayo& rayo, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz*
        luz);
    color calcular_reflexion(const rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano, int nivel);
    color calcular_translucidez(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano, int nivel);
    color calcular_difuso_especular(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano);
};
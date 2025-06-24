﻿#pragma once

#include "camara.h"
#include "../ray-tracing/object.h"
#include "../render/imagen.h"
#include "../luz.h"
#include "SDL.h"

class escena
{
    color color_fondo_, ambiente_;
    double near_, far_;
    int ancho_, alto_;
    camara* camara_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;
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
    void Render(SDL_Renderer* renderer, int progreso);
    bool termino();
    imagen get_imagen_final();
    imagen get_imagen_reflexion();
    imagen get_imagen_refraccion();
    int get_iter();
    int get_ancho();
    int get_alto();
    double get_far();
    double get_near();
    color get_color_fondo();
    color calcular_color(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano,
        int nivel);
    color whitted_ray_tracing(rayo& rayo, double& aux_reflectividad, double& aux_refractividad, int nivel);
    color calcular_difuso(rayo& rayo_camara, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano,
        luz* luz) const;
    color calcular_especular(rayo& rayo, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz*
        luz);
    color calcular_reflexion(const rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano, int nivel);
    color calcular_translucidez(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano, int nivel);
    color calcular_difuso_especular(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion,
        objeto* objeto_cercano);
};
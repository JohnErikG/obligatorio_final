#include "escena.h"
#include <iostream>
#include<String>
int escena::max_depth_ = 10;
bool escena::cast_rayo(rayo& rayo_casteado, const objeto* objeto_actual, objeto*& objeto_cercano, vector3& punto_interseccion, vector3& normal_interseccion) const
{
    float min_dist = 1e6;
    bool intersection_found = false;

    for (const auto& current_object : objects_)
    {
        if (current_object != objeto_actual)
        {
            vector3 intersection_point, intersection_normal;
            bool valid_int = current_object->calcular_interseccion(rayo_casteado, intersection_point, intersection_normal);

            if (valid_int)
            {
                float dist = (intersection_point - rayo_casteado.getOrigen()).getNorm();

                if (dist <= min_dist)
                {
                    min_dist = dist;
                    objeto_cercano = current_object;
                    punto_interseccion = intersection_point;
                    normal_interseccion = intersection_normal;
                    intersection_found = true;
                }
            }
        }
    }

    return intersection_found;
}

escena::escena(const char* archivo_escena):final_(0,0, std::vector<pixel>(), normal),
aux_relfexion_(0,0, std::vector<pixel>(),reflexion ),
aux_refraccion_(0,0, std::vector<pixel>(), refraccion)
{
    near_ = 0.1;
    far_ = 1000;

    tinyxml2::XMLDocument doc;
    auto res = doc.LoadFile(archivo_escena);
    auto esena1 = doc.FirstChildElement("document")->FirstChildElement("scene");


    ancho_ = parceo::parceoInt(esena1, "width");
    alto_ = parceo::parceoInt(esena1, "height");

    final_ = imagen::vacia(ancho_, alto_, normal);
    aux_relfexion_ = imagen::vacia(ancho_, alto_, reflexion);
    aux_refraccion_ = imagen::vacia(ancho_, alto_, refraccion);


    tinyxml2::XMLNode* nodo = esena1->FirstChild();
    do
    {
        const auto element = nodo->ToElement();

        const auto element_type = std::string(element->Name());
        
        if (element_type == "shape") { objects_.push_back(parceo::parseObjeto(element)); }
        else if (element_type == "luz") { lights_.push_back(parceo::parsL(element)); }
        else if (element_type == "camera") { camara_ = parceo::parseCamara(element, ancho_, alto_); }
        else if (element_type == "background") {color_fondo_ = parceo::parseColor(element); }
        else if (element_type == "ambient") { ambiente_ = parceo::parseColor(element); }
        else { break; }

        nodo = nodo->NextSibling();
    } while (nodo != nullptr);


}
bool escena::termino()
{
    return terminado_;
}

imagen escena::get_imagen_final()
{
    return final_;
}

imagen escena::get_imagen_reflexion()
{
    return aux_relfexion_;
}

imagen escena::get_imagen_refraccion()
{
    return aux_refraccion_;
}

int escena::get_iter()
{
    return iteraciones_;
}

int escena::get_ancho()
{
    return ancho_;
}

int escena::get_alto()
{
    return alto_;
}

float escena::get_far()
{
    return far_;
}

float escena::get_near()
{
    return near_;
}

color escena::get_color_fondo()
{
    return color_fondo_;
}



void escena::Render(int progreso)
{
    if (iteraciones_ >= ancho_)
    {
        terminado_ = true;
    }
    if (!terminado_)
    {

        rayo ra = rayo(camara_->get_position(), vector3(0, 0, 0 ));

        float x_factor = 2.0 / (float)ancho_;
        float y_factor = 2.0 / (float)alto_;
        int n = 2; 
        float Tcelda = 1.0 / (float)n;

        int x = iteraciones_; 
        int fin = (x + progreso > ancho_) ? ancho_ : x + progreso;

        for ( x; x < fin; x++)
        {
            for (int y = 0; y < alto_; y++)
            {
                color final_color = color(0,0,0); 
                float final_reflectividad = 0.0;
                float final_refractividad = 0.0;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        float sample_x = (float)x + (i + 0.5) * Tcelda;
                        float sample_y = (float)y + (j + 0.5) * Tcelda;

                        float norm_x = sample_x * x_factor - 1.0;
                        float norm_y = sample_y * y_factor - 1.0;

                        camara_->crear_rayo(norm_x, norm_y, ra);

                        float aux_reflectividad = 0.0;
                        float aux_refractividad = 0.0;

                        color sample_color =
                            whitted_ray_tracing(ra, aux_reflectividad, aux_refractividad, max_depth_);


                        final_color += sample_color;
                        final_reflectividad += aux_reflectividad;
                        final_refractividad += aux_refractividad;
                    }
                }
                iteraciones_ = x + 1;

                // Promediamos el color final dividiendo por el número de muestras
                final_color = final_color / (n * n);
                final_reflectividad = final_reflectividad / (n * n);
                final_refractividad = final_refractividad / (n * n);

                // Guardamos el píxel con el color final calculado
                pixel px = pixel(x, y, final_color);
                pixel px_reflectividad = pixel(x, y, color(255 * final_reflectividad, 255 * final_reflectividad,
                    255 * final_reflectividad));
                pixel px_refractividad = pixel(x, y, color(255 * final_refractividad, 255 * final_refractividad,
                    255 * final_refractividad));
                final_.agregarP(px);
                aux_relfexion_.agregarP(px_reflectividad);
                aux_refraccion_.agregarP(px_refractividad);
            }
        }
    }
}
color escena::whitted_ray_tracing(rayo& ra, float& aux_reflectividad, float& aux_refractividad, int nivel)
{

    if (nivel == 0) { return color(0,0, 0); }

    objeto* objeto_cercano = nullptr;
    vector3 intersection_point = vector3(0, 0, 0);
    vector3 intersection_normal = vector3(0, 0, 0);

    color px_color = get_color_fondo(); 

    cast_rayo(ra, nullptr, objeto_cercano, intersection_point, intersection_normal);

    aux_reflectividad = 0.0;
    aux_refractividad = 0.0;
    if (objeto_cercano != nullptr)
    {
        px_color = calcular_color(ra, intersection_point, intersection_normal, objeto_cercano, nivel - 1);
        aux_reflectividad = objeto_cercano->getreflectividad();
        aux_refractividad = 1 / objeto_cercano->getindiceRefraccion();
    }
    return px_color;
}

color escena::calcular_color(rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0) { return color(0,0,0); }

    const color diffuse_specular_color = ambiente_ + calcular_difuso_especular(
        ra, punto_interseccion, normal_interseccion,
        objeto_cercano);
    color reflection_color = color(0,0,0);
    color translucent_color = color(0,0,0);
    if (objeto_cercano->getreflectividad() > 0.0)
    {
        reflection_color = calcular_reflexion(ra, punto_interseccion, normal_interseccion, objeto_cercano, nivel - 1);
    }
    if (objeto_cercano->gettransparaencia() > 0.0)
    {
        translucent_color = calcular_translucidez(ra, punto_interseccion, normal_interseccion, objeto_cercano,
            nivel - 1);
    }

    color final_color = (diffuse_specular_color) * (1 - objeto_cercano->getreflectividad())
        + reflection_color * objeto_cercano->getreflectividad();
    final_color = final_color + translucent_color * objeto_cercano->gettransparaencia();
    return final_color;
    
}



color escena::calcular_difuso(rayo& rayo_camara, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz* luz)
{
    color calc_color = color(0,0,0);

    const vector3 light_direction = (luz->getPosicion() - punto_interseccion).normalize();
    rayo sombra(punto_interseccion + light_direction * 0.001, light_direction); 

    const float prod = normal_interseccion.dot_product(light_direction);
    
    if (prod < 0.0) 
    {
        return calc_color;
    }

    float light_attenuation = 1.0; 
    color light_color_attenuation = color(0,0,0); 

    objeto* closest_object = nullptr;
    vector3 nuevoPunto, nuevaNormal;

    while (cast_rayo(sombra, objeto_cercano, closest_object, nuevoPunto, nuevaNormal))
    {
        const float intersection_distance = (nuevoPunto - punto_interseccion).getNorm();
        const float light_distance = (luz->getPosicion() - punto_interseccion).getNorm();
        if (closest_object->gettransparaencia() < 1.0)
        {
            if (intersection_distance < light_distance)
            {
                if (closest_object->gettransparaencia() > 0.0)
                {
                    light_attenuation *= closest_object->gettransparaencia();
                    light_color_attenuation = light_color_attenuation.combinar(closest_object->getColor(),
                                                closest_object->gettransparaencia());

                    sombra = rayo(nuevoPunto + light_direction * 0.001, light_direction);
                }
                else
                {
                    return color(0, 0, 0);
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            sombra = rayo(nuevoPunto + light_direction * 0.001, light_direction);
        }
    }

    const float intensity = prod * luz->getIntensidad();

    calc_color = objeto_cercano->getColor().combinar(light_color_attenuation, light_attenuation) * intensity;

    return calc_color;
}

color escena::calcular_especular(rayo& rayo, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz* luz)
{
    vector3 light_direction = (luz->getPosicion() - punto_interseccion).normalize();
    vector3 view_direction = (rayo.getOrigen() - punto_interseccion).normalize();
    vector3 reflection_direction = (-light_direction + normal_interseccion*(2.0 * normal_interseccion.dot_product(light_direction))).normalize();

    float reflection_view_dot = reflection_direction.dot_product(view_direction);

    if (reflection_view_dot < 0.0)
    {
        return color(0,0,0);
    }

    float shininess = objeto_cercano->getbrillo();
    float specular_intensity = pow(reflection_view_dot, shininess) * luz->getIntensidad();

    color specular_color = luz->getColor() * specular_intensity;

    return specular_color;
}

color escena::calcular_reflexion( const rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0 || objeto_cercano->getreflectividad() <= 0.0) { color(0,0,0); }

    rayo raR = ra.reflejar(punto_interseccion, normal_interseccion);
    float trash1, trash2;
    return whitted_ray_tracing(raR, trash1, trash2, nivel - 1);



}

color escena::calcular_translucidez(rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    color translucency_color = color(0,0,0);

    if (objeto_cercano->gettransparaencia() > 0.0)
    {

        vector3 rayo_vista = ra.getDireccion().normalize();
        vector3 normal = normal_interseccion.normalize();

        float n1, n2; 
        float cos_theta1 = (-rayo_vista).dot_product(normal);

        if (cos_theta1 > 0.0)
        {
            n1 = 1.0; 
            n2 = objeto_cercano->getindiceRefraccion(); 
        }
        else
        {
            n1 = objeto_cercano->getindiceRefraccion(); 
            n2 = 1.0;
            normal = -normal; 
            cos_theta1 = -cos_theta1;
        }

        float ratio = n1 / n2;
        float sin_theta1_squared = 1.0 - cos_theta1 * cos_theta1;
        float sin_theta2_squared = ratio * ratio * sin_theta1_squared;

        if (sin_theta2_squared <= 1.0)
        {
            float cos_theta2 = sqrt(1.0 - sin_theta2_squared);
            vector3 refracted_direction = rayo_vista * ratio + normal * (ratio * cos_theta1 - cos_theta2);
            rayo refracted_ray(punto_interseccion + refracted_direction * 0.0001, refracted_direction);
            float trash1, trash2;
            translucency_color = whitted_ray_tracing(refracted_ray, trash1, trash2, nivel - 1);
        }
    }

    return translucency_color;
}

color escena::calcular_difuso_especular(rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano)
{


color diffuse_color = color(0,0,0);
color specular_color = color(0,0,0);

for (luz* luz : lights_)
{
    diffuse_color = diffuse_color + calcular_difuso(ra, punto_interseccion, normal_interseccion,
        objeto_cercano, luz);
    if (objeto_cercano->getbrillo() > 0.0)
    {
        specular_color = specular_color + calcular_especular(ra, punto_interseccion, normal_interseccion,
            objeto_cercano, luz);
    }
}

return diffuse_color + specular_color;
}

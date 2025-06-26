#include "escena.h"
#include <iostream>
#include<String>
int escena::max_depth_ = 1000;
bool escena::cast_rayo(rayo& rayo_casteado, const objeto* objeto_actual, objeto*& objeto_cercano, vector3& punto_interseccion, vector3& normal_interseccion) const
{
    double min_dist = 1e6;
    bool intersection_found = false;

    for (const auto& current_object : objects_)
    {
        if (current_object != objeto_actual)
        {
            vector3 intersection_point, intersection_normal;
            bool valid_int = current_object->intereseccion(rayo_casteado, intersection_point, intersection_normal);

            if (valid_int)
            {
                double dist = (intersection_point - rayo_casteado.getOrigen()).getNorm();

                if (dist < min_dist)
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
    if (res != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error("Failed to load file " + std::string(archivo_escena) + ": " + std::to_string(res));
    }

    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);

    auto dom_scene = doc.FirstChildElement("document")->FirstChildElement("scene");
    if (!dom_scene)
    {
        throw std::runtime_error("'scene' element not found");
    }

    ancho_ = parceo::parceoInt(dom_scene, "width");
    alto_ = parceo::parceoInt(dom_scene, "height");

    final_ = imagen::vacia(ancho_, alto_, normal);
    aux_relfexion_ = imagen::vacia(ancho_, alto_, reflexion);
    aux_refraccion_ = imagen::vacia(ancho_, alto_, refraccion);

    if (dom_scene->NoChildren())
    {
        throw std::runtime_error("No objects found in scene");
    }

    tinyxml2::XMLNode* node = dom_scene->FirstChild();
    do
    {
        const auto element = node->ToElement();

        const auto element_type = std::string(element->Name());
        
        if (element_type == "shape") { objects_.push_back(parceo::parseObjeto(element)); }
        else if (element_type == "luz") { lights_.push_back(parceo::parsL(element)); }
        else if (element_type == "camera") { camara_ = parceo::parseCamara(element, ancho_, alto_); }
        else if (element_type == "background") {color_fondo_ = parceo::parseColor(element); }
        else if (element_type == "ambient") { ambiente_ = parceo::parseColor(element); }
        else { throw std::runtime_error("Unknown element type: " + element_type); }

        node = node->NextSibling();
    } while (node != nullptr);

    std::cout << "Scene loaded" << '\n' << "- Shapes: " << objects_.size() << '\n' << "- Lights: " << lights_.size()
        <<
        '\n';
}



void escena::Render(SDL_Renderer* renderer, int progreso)
{
    if (iteraciones_ >= ancho_)
    {
        terminado_ = true;
    }
    if (!terminado_)
    {
        /* Creamos el rayo que sale de la camara, el cual usaremos para el trazado de rayos */
        rayo ra = rayo(camara_->get_position(), vector3(0, 0, 0 ));
        std::cout << camara_->get_position().get_x() << "\n";
        double x_factor = 2.0 / (double)ancho_;
        double y_factor = 2.0 / (double)alto_;
        int n = 2; // Número de celdas por lado, para un total de n*n rayos por píxel
        double cell_size = 1.0 / (double)n;

        /* Calculamos todos los píxeles */

        int x = iteraciones_; // el pixel siguiente a donde me quedé la última vez. 
        int fin;
        if (x + progreso > ancho_)
        {
            fin = ancho_;
        }
        else
        {
            fin = x + progreso;
        }
        for (x; x < fin; x++)
        {
            for (int y = 0; y < alto_; y++)
            {
                color final_color = { 0, 0, 0 }; // Color inicial del píxel
                double final_reflectividad = 0.0;
                // => En estas variables cargaremos el valor de los coeficientes de reflexion y refraccion en el pixel x, y
                double final_refractividad = 0.0;
                /* Para cada celda dentro del píxel */
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        // Desplazamiento dentro del píxel
                        double sample_x = (double)x + (i + 0.5) * cell_size;
                        double sample_y = (double)y + (j + 0.5) * cell_size;

                        // Normalizamos el pixel por el que pasará el rayo
                        double norm_x = sample_x * x_factor - 1.0;
                        double norm_y = sample_y * y_factor - 1.0;

                        // Casteamos el rayo para que pase por el píxel normalizado (x, y)
                        camara_->generate_ray(norm_x, norm_y, ra);

                        double aux_reflectividad = 0.0;
                        double aux_refractividad = 0.0;

                        // Calculamos el color del rayo
                        color sample_color =
                            whitted_ray_tracing(ra, aux_reflectividad, aux_refractividad, max_depth_);

                        // Sumamos el color de la muestra al color final del píxel
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

double escena::get_far()
{
    return far_;
}

double escena::get_near()
{
    return near_;
}

color escena::get_color_fondo()
{
    return color_fondo_;
}

color escena::calcular_color(rayo& rayo, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0) { return { 0, 0, 0 }; }

    const color diffuse_specular_color = ambiente_ + calcular_difuso_especular(
        rayo, punto_interseccion, normal_interseccion,
        objeto_cercano);
    color reflection_color = { 0, 0, 0 };
    color translucent_color = { 0, 0, 0 };
    if (objeto_cercano->getreflectividad() > 0.0)
    {
        reflection_color = calcular_reflexion(rayo, punto_interseccion, normal_interseccion, objeto_cercano, nivel - 1);
    }
    if (objeto_cercano->gettransparaencia() > 0.0)
    {
        translucent_color = calcular_translucidez(rayo, punto_interseccion, normal_interseccion, objeto_cercano,
            nivel - 1);
    }

    color final_color = (diffuse_specular_color) * (1 - objeto_cercano->getreflectividad())
        + reflection_color * objeto_cercano->getreflectividad();
    final_color = final_color + translucent_color * objeto_cercano->gettransparaencia();
    return final_color;
    
}

color escena::whitted_ray_tracing(rayo& rayo, double& aux_reflectividad, double& aux_refractividad, int nivel)
{
    if (nivel == 0) { return { 0, 0, 0 }; }

    objeto* objeto_cercano = nullptr;
	vector3 intersection_point = vector3(0, 0, 0);
    vector3 intersection_normal = vector3(0, 0, 0);
    //=> Variable en la que cargaremos la normal del objeto en el punto de interseccion

    color px_color = get_color_fondo(); //=> Variable en la que cargaremos el color del pixel

    cast_rayo(rayo, nullptr, objeto_cercano, intersection_point, intersection_normal);

    aux_reflectividad = 0.0;
    aux_refractividad = 0.0;
    /* Calcularemos cuanta luz recibe el punto de interseccion */
    if (objeto_cercano != nullptr)
    {
        px_color = calcular_color(rayo, intersection_point, intersection_normal, objeto_cercano, nivel - 1);
        aux_reflectividad = objeto_cercano->getreflectividad();
        aux_refractividad = 1 / objeto_cercano->getindiceRefraccion();
    }
    return px_color;
}

color escena::calcular_difuso(rayo& rayo_camara, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz* luz)
{
    color calc_color = { 0, 0, 0 };

    const vector3 light_direction = (luz->getPosicion() - punto_interseccion).normalize();
    rayo shadow_ray(punto_interseccion + light_direction * 0.001, light_direction); // Avoid self-intersection

    const double prod = normal_interseccion.dot_product(light_direction);
    std::cout << prod << "\n\n";
    if (prod < 0.0) // Solo considerar si la luz incide en la superficie
    {
        return calc_color;
    }

    double light_attenuation = 1.0; // Atenuación de la luz
    color light_color_attenuation = { 0, 0, 0 }; // Atenuación por color de la luz

   objeto* closest_object = nullptr;
    vector3 new_intersection_point, new_intersection_normal;

    while (cast_rayo(shadow_ray, objeto_cercano, closest_object, new_intersection_point, new_intersection_normal))
    {
        const double intersection_distance = (new_intersection_point - punto_interseccion).getNorm();
        const double light_distance = (luz->getPosicion() - punto_interseccion).getNorm();
        if (closest_object->gettransparaencia() < 1.0)
        {
            if (intersection_distance < light_distance)
            {
                if (closest_object->gettransparaencia() > 0.0)
                {
                    light_attenuation *= closest_object->gettransparaencia();
                    light_color_attenuation = light_color_attenuation.combinar(closest_object->getColor(),
                        closest_object->gettransparaencia());
                    // Continuar el rayo de sombra
                    shadow_ray = rayo(new_intersection_point + light_direction * 0.001, light_direction);
                }
                else
                {
                    // El objeto es opaco, bloquear la luz completamente
                    return { 0, 0, 0 };
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            shadow_ray = rayo(new_intersection_point + light_direction * 0.001, light_direction);
        }
    }

    const double intensity = prod * luz->getIntensidad();

    // Calcular color difuso y especular si no está en la sombra completa
    calc_color = objeto_cercano->getColor().combinar(light_color_attenuation, light_attenuation) * intensity;

    // Añadir el color calculado al color difuso
    return calc_color;
}

color escena::calcular_especular(rayo& rayo, const vector3& punto_interseccion, const vector3& normal_interseccion, const objeto* objeto_cercano, luz* luz)
{
    vector3 light_direction = (luz->getPosicion() - punto_interseccion).normalize();
    vector3 view_direction = (rayo.getOrigen() - punto_interseccion).normalize();
    vector3 reflection_direction = (-light_direction + normal_interseccion*(2.0 * normal_interseccion.dot_product(light_direction))).normalize();

    double reflection_view_dot = reflection_direction.dot_product(view_direction);

    if (reflection_view_dot < 0.0)
    {
        return { 0, 0, 0 };
    }

    double shininess = objeto_cercano->getbrillo();
    double specular_intensity = pow(reflection_view_dot, shininess) * luz->getIntensidad();

    color specular_color = luz->getColor() * specular_intensity;

    return specular_color;
}

color escena::calcular_reflexion( rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0 || objeto_cercano->getreflectividad() <= 0.0) { return { 0, 0, 0 }; }

    rayo reflected_ray = ra.reflejar(punto_interseccion, normal_interseccion);
    double trash1, trash2;
    return whitted_ray_tracing(reflected_ray, trash1, trash2, nivel - 1);



}

color escena::calcular_translucidez(rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano, int nivel)
{
    color translucency_color = { 0, 0, 0 };

    if (objeto_cercano->gettransparaencia() > 0.0)
    {
        vector3 rayo_vista = ra.getDireccion().normalize();
        vector3 normal = normal_interseccion.normalize();

        double n1, n2; // Índices de refracción
        double cos_theta1 = (-rayo_vista).dot_product(normal);

        if (cos_theta1 > 0.0)
        {
            // Rayo entrando al objeto
            n1 = 1.0; // Índice de refracción del aire
            n2 = objeto_cercano->getindiceRefraccion(); // Índice de refracción del objeto
        }
        else
        {
            // Rayo saliendo del objeto
            n1 = objeto_cercano->getindiceRefraccion(); // Índice de refracción del objeto
            n2 = 1.0; // Índice de refracción del aire
            normal = -normal; // Invertimos la normal para calcular correctamente
            cos_theta1 = -cos_theta1;
        }

        double ratio = n1 / n2;
        double sin_theta1_squared = 1.0 - cos_theta1 * cos_theta1;
        double sin_theta2_squared = ratio * ratio * sin_theta1_squared;

        if (sin_theta2_squared <= 1.0)
        {
            double cos_theta2 = sqrt(1.0 - sin_theta2_squared);
            vector3 refracted_direction = rayo_vista * ratio + normal * (ratio * cos_theta1 - cos_theta2);
            rayo refracted_ray(punto_interseccion + refracted_direction * 0.0001, refracted_direction);
            double trash1, trash2;
            translucency_color = whitted_ray_tracing(refracted_ray, trash1, trash2, nivel - 1);
        }
    }

    return translucency_color;
}

color escena::calcular_difuso_especular(rayo& ra, vector3 punto_interseccion, vector3 normal_interseccion, objeto* objeto_cercano)
{


color diffuse_color = { 0, 0, 0 };
color specular_color = { 0, 0, 0 };

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

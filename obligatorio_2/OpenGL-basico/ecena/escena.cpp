#include "escena.h"
#include <iostream>
#include<String>
int escena::max_depth_ = 10;
bool escena::cast_rayo(rayo& rayo_casteado, const objeto* objeto_actual, objeto*& objeto_cercano, vector3& Punto_Inter, vector3& Normal_inter) const
{
    float min_dist = 1e6;
    bool EncontreInter = false;

    for (const auto& objAct : Objetos)
    {
        if (objAct != objeto_actual)
        {
            vector3 PuntoInt, NormalInter;
            bool valid_int = objAct->calcular_interseccion(rayo_casteado, PuntoInt, NormalInter);

            if (valid_int)
            {
                float dist = (PuntoInt - rayo_casteado.getOrigen()).getNorm();

                if (dist <= min_dist)
                {
                    min_dist = dist;
                    objeto_cercano = objAct;
                    Punto_Inter = PuntoInt;
                    Normal_inter = NormalInter;
                    EncontreInter = true;
                }
            }
        }
    }

    return EncontreInter;
}

escena::escena(const char* archivo_escena):final_(0,0, std::vector<pixel>(), normal),
aux_relfexion_(0,0, std::vector<pixel>(),reflexion ),
aux_refraccion_(0,0, std::vector<pixel>(), refraccion)
{
    tinyxml2::XMLDocument doc;
    auto res = doc.LoadFile(archivo_escena);
    auto esena1 = doc.FirstChildElement("document")->FirstChildElement("scene");
    alto_ = parceo::parceoInt(esena1, "height");
    ancho_ = parceo::parceoInt(esena1, "width");

    final_ = imagen::vacia(ancho_, alto_, normal);
    aux_relfexion_ = imagen::vacia(ancho_, alto_, reflexion);
    aux_refraccion_ = imagen::vacia(ancho_, alto_, refraccion);
    tinyxml2::XMLNode* nodo = esena1->FirstChild();
    do
    {
        const auto element = nodo->ToElement();
        const auto element_type = std::string(element->Name());
        
        if (element_type == "shape") { Objetos.push_back(parceo::parseObjeto(element)); }
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

                final_color = final_color / (n * n);
                final_reflectividad = final_reflectividad / (n * n);
                final_refractividad = final_refractividad / (n * n);

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
    vector3 PuntoInt = vector3(0, 0, 0);
    vector3 NormalInter = vector3(0, 0, 0);

    color px_color = get_color_fondo(); 

    cast_rayo(ra, nullptr, objeto_cercano, PuntoInt, NormalInter);

    aux_reflectividad = 0.0;
    aux_refractividad = 0.0;
    if (objeto_cercano != nullptr)
    {
        px_color = calcular_color(ra, PuntoInt, NormalInter, objeto_cercano, nivel - 1);
        aux_reflectividad = objeto_cercano->getreflectividad();
        aux_refractividad = objeto_cercano->getindiceRefraccion();
    }
    return px_color;
}

color escena::calcular_color(rayo& ra, vector3 Punto_Inter, vector3 Normal_inter, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0)  return color(0,0,0); 

    const color CDifEsp = ambiente_ + calcular_difuso_especular(
        ra, Punto_Inter, Normal_inter,
        objeto_cercano);
    color Creflexion = color(0,0,0);
    color Ctransparencia = color(0,0,0);
    if (objeto_cercano->getreflectividad() > 0.0)
    {
        Creflexion = calcular_reflexion(ra, Punto_Inter, Normal_inter, objeto_cercano, nivel - 1);
    }
    if (objeto_cercano->gettransparaencia() > 0.0)
    {
        Ctransparencia = calcular_translucidez(ra, Punto_Inter, Normal_inter, objeto_cercano,
            nivel - 1);
    }

    color final_color = (CDifEsp) * (1 - objeto_cercano->getreflectividad())
        + Creflexion * objeto_cercano->getreflectividad();
    final_color = final_color + Ctransparencia * objeto_cercano->gettransparaencia();
    return final_color;
    
}



color escena::calcular_difuso(rayo& rayo_camara, const vector3& Punto_Inter, const vector3& Normal_inter, const objeto* objeto_cercano, luz* luz)
{
    color calc_color = color(0,0,0);

    const vector3 luzDir = (luz->getPosicion() - Punto_Inter).normalize();
    rayo sombra(Punto_Inter + luzDir * 0.001, luzDir); 

    const float prod = Normal_inter.dot_product(luzDir);
    
    if (prod < 0.0) 
    {
        return calc_color;
    }

    float LuzAtenua = 1.0; 
    color colorLuzAtenua = color(0,0,0); 

    objeto* objCercano = nullptr;
    vector3 nuevoPunto, nuevaNormal;

    while (cast_rayo(sombra, objeto_cercano, objCercano, nuevoPunto, nuevaNormal))
    {
        const float DistInter = (nuevoPunto - Punto_Inter).getNorm();
        const float luzDist = (luz->getPosicion() - Punto_Inter).getNorm();
        if (objCercano->gettransparaencia() < 1.0)
        {
            if (DistInter < luzDist)
            {
                if (objCercano->gettransparaencia() > 0.0)
                {
                    LuzAtenua *= objCercano->gettransparaencia();
                    colorLuzAtenua = colorLuzAtenua.combinar(objCercano->getColor(),
                                                objCercano->gettransparaencia());

                    sombra = rayo(nuevoPunto + luzDir * 0.001, luzDir);
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
            sombra = rayo(nuevoPunto + luzDir * 0.001, luzDir);
        }
    }

    const float inten = prod * luz->getIntensidad();

    calc_color = objeto_cercano->getColor().combinar(colorLuzAtenua, LuzAtenua) * inten;

    return calc_color;
}

color escena::calcular_especular(rayo& rayo, const vector3& Punto_Inter, const vector3& Normal_inter, const objeto* objeto_cercano, luz* luz)
{
    vector3 luzDir = (luz->getPosicion() - Punto_Inter).normalize();
    vector3 vistaDir = (rayo.getOrigen() - Punto_Inter).normalize();
    vector3 dirRefleccion = (-luzDir + Normal_inter*(2.0 * Normal_inter.dot_product(luzDir))).normalize();

    float vistaReflexionDot = dirRefleccion.dot_product(vistaDir);

    if (vistaReflexionDot < 0.0) return color(0,0,0);
    

    float brillo = objeto_cercano->getbrillo();
    float intencidadEspecular = pow(vistaReflexionDot, brillo) * luz->getIntensidad();

    color colorEspecular = luz->getColor() * intencidadEspecular;

    return colorEspecular;
}

color escena::calcular_reflexion( const rayo& ra, vector3 Punto_Inter, vector3 Normal_inter, objeto* objeto_cercano, int nivel)
{
    if (nivel == 0 || objeto_cercano->getreflectividad() <= 0.0) { color(0,0,0); }

    rayo raR = ra.reflejar(Punto_Inter, Normal_inter);
    float T1, T2;
    return whitted_ray_tracing(raR, T1, T2, nivel - 1);



}

color escena::calcular_translucidez(rayo& ra, vector3 Punto_Inter, vector3 Normal_inter, objeto* objeto_cercano, int nivel)
{
    color Ctransp = color(0,0,0);

    if (objeto_cercano->gettransparaencia() > 0.0)
    {

        vector3 rayo_vista = ra.getDireccion().normalize();
        vector3 normal = Normal_inter.normalize();

        float n1, n2; 
        float cos_t1 = (-rayo_vista).dot_product(normal);

        if (cos_t1 > 0.0)
        {
            n1 = 1.0; 
            n2 = objeto_cercano->getindiceRefraccion(); 
        }
        else
        {
            n1 = objeto_cercano->getindiceRefraccion(); 
            n2 = 1.0;
            normal = -normal; 
            cos_t1 = -cos_t1;
        }

        float ratio = n1 / n2;
        float sin_theta1_squared = 1.0 - cos_t1 * cos_t1;
        float sinThetaCuadrado = ratio * ratio * sin_theta1_squared;

        if (sinThetaCuadrado <= 1.0)
        {
            float cos_t2 = sqrt(1.0 - sinThetaCuadrado);
            vector3 dirRefraccion = rayo_vista * ratio + normal * (ratio * cos_t1 - cos_t2);
            rayo Rrefractado(Punto_Inter + dirRefraccion * 0.0001, dirRefraccion);
            float T1, T2;
            Ctransp = whitted_ray_tracing(Rrefractado, T1, T2, nivel - 1);
        }
    }

    return Ctransp;
}

color escena::calcular_difuso_especular(rayo& ra, vector3 Punto_Inter, vector3 Normal_inter, objeto* objeto_cercano)
{


color Cdif = color(0,0,0);
color colorEspecular = color(0,0,0);

for (luz* luz : lights_)
{
    Cdif = Cdif + calcular_difuso(ra, Punto_Inter, Normal_inter,
        objeto_cercano, luz);
    if (objeto_cercano->getbrillo() > 0.0)
    {
        colorEspecular = colorEspecular + calcular_especular(ra, Punto_Inter, Normal_inter,
            objeto_cercano, luz);
    }
}

return Cdif + colorEspecular;
}

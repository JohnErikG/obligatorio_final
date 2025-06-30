#include "renderr.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "FreeImage.h"
#include "imagen.h"
#include"../utilidades/color.h"


int renderr::id = 0;
std::string horaDia()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;
    const auto res = localtime_s(&local_time, &current_time);
    std::ostringstream aaa;
    aaa << std::put_time(&local_time, "%Y%m%d_%H%M%S");
    return aaa.str();
}
void renderr::guardado(imagen& img)
{
    if (id < 3)
    {
        id++;
        auto current_time = horaDia();
        const auto ancho = img.getAncho();
        const auto alto = img.getAlto();

        // Create an empty 24-bit RGB image
        FIBITMAP* bitmap = FreeImage_Allocate(ancho, alto, 24);


        const auto pixels = img.getPixeles();
        for (pixel pixel : pixels)
        {

            FreeImage_SetPixelColor(bitmap, pixel.getX(), pixel.getY(), &(pixel.getColor().to_rgb()));
        }
		std::string filDir = "../imagenes/";

        auto file_name = img.getTipo().append(current_time.append(".png").c_str());
		std::string filepath = filDir.append(file_name);
        // Save the image as a PNG file
        FreeImage_Save(FIF_PNG, bitmap, filepath.c_str(), 0);

        FreeImage_Unload(bitmap);
    }
}


void renderr::algoritmo(imagen& img, int max_x, SDL_Renderer* render)
{
    std::vector<uint32_t> pixel_data(img.getAncho() * img.getAlto());
    for (int x = 0; x < max_x; x++)
    {
        for (int y = 0; y < img.getAlto(); y++)
        {
            pixel& p = img.getpixel(x, img.getAlto() - y);
            color& c = p.getColor();
            uint32_t rgba = (static_cast<uint8_t>(c.get_rojo()) << 24) |
                (static_cast<uint8_t>(c.get_verde()) << 16) |
                (static_cast<uint8_t>(c.get_azul()) << 8) |
                static_cast<uint8_t>(c.get_alpha());
            pixel_data[y * img.getAncho() + x] = rgba;
        }
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        pixel_data.data(),
        img.getAncho(),
        img.getAlto(),
        32, // bits per pixel
        img.getAncho() * sizeof(uint32_t), // pitch: bytes per row
        0xFF000000, // Red mask
        0x00FF0000, // Green mask
        0x0000FF00, // Blue mask
        0x000000FF  // Alpha mask
    );


    SDL_Texture* textura = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(render);
    SDL_RenderCopy(render, textura, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_DestroyTexture(textura);

}



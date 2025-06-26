#include "renderr.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "FreeImage.h"
#include "imagen.h"
#include"../utilidades/color.h"


int renderr::id = 0;
std::string get_current_timestamp()
{
    const auto now = std::chrono::system_clock::now();

    const std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    std::tm local_time;
    const auto res = localtime_s(&local_time, &current_time);

    if (res != 0)
    {
        std::cerr << "Failed to convert time" << '\n';
        throw std::runtime_error("Failed to convert time");
    }

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y%m%d_%H%M%S");

    return oss.str();
}
void renderr::guardado(imagen& img)
{
    if (id < 3)
    {
        id++;
        auto current_time = get_current_timestamp();
        const auto width = img.getAncho();
        const auto height = img.getAlto();

        // Create an empty 24-bit RGB image
        FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);


        const auto pixels = img.getPixeles();
        for (pixel pixel : pixels)
        {

            FreeImage_SetPixelColor(bitmap, pixel.getX(), pixel.getY(), &(pixel.getColor().to_rgb()));
        }
        auto file_name = img.getTipo().append(current_time.append(".png").c_str());

        // Save the image as a PNG file
        FreeImage_Save(FIF_PNG, bitmap, file_name.c_str(), 0);

        FreeImage_Unload(bitmap);
    }
}
	//float ww = img->getAncho();
	//float hh = img->getAlto(); 
	//std::vector<BYTE> pixels(3 * ww * hh);

	//glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glReadPixels(0, 0, ww, hh, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());
	//FIBITMAP* bitmapp = FreeImage_ConvertFromRawBits(
	//	pixels.data(),
	//	ww, hh,
	//	3 * ww,              // pitch
	//	24,                 // bits por píxel
	//	0x00FF0000,         // máscara rojo
	//	0x0000FF00,         // máscara verde
	//	0x000000FF,         // máscara azul
	//	false               // no flip vertical
	//);
	//FreeImage_Save(FIF_PNG, bitmapp, "../imagenes/output4.png", 0);
	//FreeImage_Unload(bitmapp);



void renderr::algoritmo(imagen& img, int maxX, SDL_Renderer* ren)
{

    // Crear un buffer para los datos de los píxeles en formato RGBA
    std::vector<uint32_t> pixel_data(img.getAncho() * img.getAlto());
    for (int x = 0; x < maxX; x++)
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

        // Crear la superficie SDL desde el buffer de píxeles
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


        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);


        SDL_RenderClear(ren);

        SDL_RenderCopy(ren, texture, NULL, NULL) ;

        SDL_RenderPresent(ren);

        SDL_DestroyTexture(texture);
    }
}



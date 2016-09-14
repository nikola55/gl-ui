#include <stdexcept>
#include "image_io.h"

#include <SDL2/SDL_image.h>

using std::runtime_error;
using ui::byte;
using ui::image;

image native::loadFromFile(const std::string &path) {
    SDL_Surface * sdl_image = IMG_Load(path.c_str());
    if(sdl_image == 0) {
        throw runtime_error("cannot load image from "+path);
    }
    byte bitsPerPixel = byte(sdl_image->format->BitsPerPixel);
    byte* pixels = static_cast<byte*>(sdl_image->pixels);
    uint width = sdl_image->w;
    uint height = sdl_image->h;
    image img(width, height, bitsPerPixel, pixels, true);
    sdl_image->pixels = 0;
    SDL_FreeSurface(sdl_image);
    return img;
}

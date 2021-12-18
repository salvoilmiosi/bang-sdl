#include "user_info.h"

#include "scenes/game/sizes.h"

#include <cstring>

constexpr std::byte profile_pic_magic_num = static_cast<std::byte>(0x8f);

std::vector<std::byte> encode_profile_image(sdl::surface image) {
    std::vector<std::byte> image_data;
    sdl::rect rect = image.get_rect();
    int scale = 1;
    if (rect.w > rect.h) {
        if (rect.w > sizes::propic_size) {
            image = sdl::scale_surface(image, rect.w / sizes::propic_size);
        }
    } else {
        if (rect.h > sizes::propic_size) {
            image = sdl::scale_surface(image, rect.h / sizes::propic_size);
        }
    }
    const auto w = image.get_rect().w;
    const auto h = image.get_rect().h;
    const auto bpp = image.get()->format->BytesPerPixel;
    const auto nbytes = w * h * bpp;
    image_data.reserve(4 + nbytes);
    image_data.push_back(profile_pic_magic_num);
    image_data.push_back(static_cast<std::byte>(w));
    image_data.push_back(static_cast<std::byte>(h));
    image_data.push_back(static_cast<std::byte>(bpp));
    image_data.insert(image_data.end(),
        static_cast<std::byte *>(image.get()->pixels),
        static_cast<std::byte *>(image.get()->pixels) + nbytes);
    return image_data;
}

sdl::surface decode_profile_image(const std::vector<std::byte> &data) {
    if (data.size() > 4) {
        std::byte m = data[0];
        if (m == profile_pic_magic_num) {
            int w = static_cast<int>(data[1]);
            int h = static_cast<int>(data[2]);
            int bpp = static_cast<int>(data[3]);
            if (data.size() >= 4 + w * h * bpp) {
                SDL_Surface *surf = SDL_CreateRGBSurface(0, w, h, 8 * bpp, sdl::rmask, sdl::gmask, sdl::bmask, sdl::amask);
                SDL_LockSurface(surf);
                std::memcpy(surf->pixels, data.data() + 4, w * h * bpp);
                SDL_UnlockSurface(surf);
                return surf;
            }
        }
    }
    return {};
}
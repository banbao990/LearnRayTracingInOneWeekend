#include <external/stb_image.h>
#include <toyrender/texture/image_texture.h>

#include <toyrender/util/rtweekend.hpp>

image_texture::image_texture()
    : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

image_texture::image_texture(const char* filename) {
    int components_per_pixel = bytes_per_pixel;
    data = stbi_load(filename, &width, &height, &components_per_pixel,
                     components_per_pixel);
    if (!data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename
                  << "'.\n"
                  << std::flush;
        width = height = 0;
    }
    bytes_per_scanline = bytes_per_pixel * width;
}

image_texture::~image_texture() { stbi_image_free(data); }

color image_texture::value(double u, double v, const point3& p) const {
    // 如果没有把图片数据读取进来, 则使用某个颜色作为暗示(大红色)
    if (!data) {
        return color(1.0, 0, 0);
    }

    u = clamp(u, 0, 1.0);
    v = 1.0 - clamp(v, 0, 1.0);  // 上下旋转(stb_image 向下为正)

    int i = static_cast<int>(u * width);
    int j = static_cast<int>(v * height);

    if (i >= width) {
        i = width - 1;
    }
    if (j >= height) {
        j = height - 1;
    }

    double color_scale = 1 / 255.0;
    auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;
    return color(pixel[0], pixel[1], pixel[2]) * color_scale;
}
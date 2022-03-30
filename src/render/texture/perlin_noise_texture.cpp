#include <toyrender/texture/perlin_noise_texture.h>

#include <cmath>

perlin_noise_texture::perlin_noise_texture(double _scale) : scale(_scale) {}
perlin_noise_texture::~perlin_noise_texture() {}

color perlin_noise_texture::value(double u, double v, const point3 &p) const {
  // 常规方式
  // return color((noise.noise(p * scale) + 1.0) * 0.5);

  // 另一种去除负值的方式
  // return color(fabs(noise.noise(p * scale)));

  // turbulence 湍流
  // return color(noise.turb(p * scale));

  // 大理石样的纹理
  return color(0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p))));
}

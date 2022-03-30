#ifndef PERLIN_NOISE_TEXTURE_H
#define PERLIN_NOISE_TEXTURE_H

#include "perlin.h"
#include "texture.h"

class perlin_noise_texture : public texture {
private:
  perlin noise;
  double scale;

public:
  perlin_noise_texture(double _scale = 1.0);
  ~perlin_noise_texture();

  virtual color value(double u, double v, const point3 &p) const override;
};

#endif
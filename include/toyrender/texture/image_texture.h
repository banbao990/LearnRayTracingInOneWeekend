#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"

// 图片纹理
class image_texture : public texture {
private:
  unsigned char *data;
  int height, width;
  int bytes_per_scanline;

public:
  const static int bytes_per_pixel = 3;

  image_texture();
  image_texture(const char *filename);
  ~image_texture();
  virtual color value(double u, double v, const point3 &p) const override;
};

#endif
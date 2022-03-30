#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include <memory>

#include "../common/color.h"
#include "solid_color.h"
#include "texture.h"

using std::make_shared;
using std::shared_ptr;

// 棋盘样纹理
class checker_texture : public texture {
private:
  shared_ptr<texture> odd, even;

public:
  // 默认黑白
  checker_texture();
  checker_texture(color _odd, color _even);
  checker_texture(shared_ptr<texture> _odd, shared_ptr<texture> _even);
  ~checker_texture();

  virtual color value(double u, double v, const point3 &p) const override;
};

#endif
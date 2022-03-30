#ifndef TEXTURE_H
#define TEXTURE_H

#include "../common/color.h"
#include "../common/vec3.h"

// 抽象纹理类
class texture {
public:
  // 根据纹理坐标 (u,v) 返回纹理值(rgb)
  virtual color value(double u, double v, const point3 &p) const = 0;
};

#endif
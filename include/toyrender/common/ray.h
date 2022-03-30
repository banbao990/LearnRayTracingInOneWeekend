#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// 光线
class ray {
private:
  point3 origin;
  vec3 direction;
  double time; // 用于运动模糊

public:
  ray();
  ray(const point3 _origin, const vec3 _direction, const double _time = 0);
  ~ray();

  vec3 get_origin() const;
  // 注意是没有单位化的
  vec3 get_direction() const;
  // 单位化的
  vec3 get_direction_unit() const;
  vec3 at(double t) const;
  double get_time() const;
};

#endif
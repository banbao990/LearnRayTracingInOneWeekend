#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

// 光线
class ray {
   private:
    point3 origin;
    vec3 direction;

   public:
    ray();
    ray(const point3& _origin, const vec3& _direction);
    ~ray();

    vec3 get_origin() const;
    // 注意是没有单位化的
    vec3 get_direction() const;
    // 单位化的
    vec3 get_direction_unit() const;
    vec3 at(double t) const;
};

#endif
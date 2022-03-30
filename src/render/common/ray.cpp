#include <toyrender/common/ray.h>

ray::ray() {}

ray::ray(const point3 _origin, const vec3 _direction, const double _time)
    : origin(_origin), direction(_direction), time(_time) {}
// : origin(_origin), direction(_direction.unit_vector()) {} // 单位化

ray::~ray() {}

vec3 ray::get_origin() const { return origin; }
vec3 ray::get_direction() const { return direction; }
vec3 ray::get_direction_unit() const { return direction.unit_vector(); }

vec3 ray::at(double t) const { return origin + t * direction; }

double ray::get_time() const { return time; }
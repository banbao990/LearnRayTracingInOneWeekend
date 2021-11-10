#include <ray.hpp>

ray::ray() {}

ray::ray(const point3& _origin, const vec3& _direction)
    : origin(_origin), direction(_direction) {}
// : origin(_origin), direction(_direction.unit_vector()) {}

ray::~ray() {}

vec3 ray::get_origin() const { return origin; }
vec3 ray::get_direction() const { return direction; }
vec3 ray::get_direction_unit() const { return direction.unit_vector(); }

vec3 ray::at(double t) const { return origin + t * direction; }

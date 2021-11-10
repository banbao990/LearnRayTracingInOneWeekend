#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include "vec3.hpp"

class camera {
   private:
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;

   public:
    camera();
    camera(point3 _origin);
    ~camera();
    ray get_ray(double u, double v) const;
};

#endif
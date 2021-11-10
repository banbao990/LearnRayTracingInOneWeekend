#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "material.hpp"
#include "ray.hpp"
#include "rtweekend.hpp"
#include "vec3.hpp"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat_ptr;

    void set_face_normal(const ray& r, const vec3& outward_normal);
};

#endif
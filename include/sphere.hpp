#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "rtweekend.hpp"
#include "vec3.hpp"

class sphere : public hittable {
   private:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

   public:
    sphere();
    sphere(double _radius);
    sphere(point3 _center, double _radius, shared_ptr<material> _mat_ptr);
    ~sphere();

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    vec3 get_center() const;
    double get_radius() const;
};

#endif